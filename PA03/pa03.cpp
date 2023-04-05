#include <iostream>
#include <vector>
using namespace std;


// 두 숫자가 3자리 이하의 숫자인지 핀별합니다.
bool checkRange(int a, int b) {
    return (a <= 999 && b <= 999);
}

// 0부터 9까지의 숫자가 중복으로 사용되었는지 체크합니다.
bool checkDigit(vector<int>& checkers, int a) {
    // 한자리 숫자는 0이 두개 있어야 하므로 불가능 합니다.
    if (a < 10) return false;
    // 두자리 숫자라면, 맨 처음에는 항상 0이 와야 하기 때문에 이를 먼저 체크합니다.
    if (a > 10 && a < 100) {
        if (checkers[0] == 1) return false;
        // 중복이 아니라면, 0을 이미 사용한 것 처리릃 합니다.
        else checkers[0] = 1;
    }

    // a를 복사해둡니다.
    int ca = a;
    // 검사 결과를 위한 boolean 변수 입니다.
    bool check = true;
    // 0이 아니면 나눗셈을 진행합니다.
    while (ca != 0 && check) {
        // 마지막 자리 숫자를 구합니다.
        int current = ca % 10;
        // 마지막 자리 숫자가 아직 사용안된 숫자라면
        if (checkers[current] == 0) {
            // 사용합니다.
            checkers[current] = 1;
            // 다음 자리 검사를 위해 10으로 나눠줍니다.
            ca /= 10;
        }
        // 사용된 숫자라면, 루프를 탈출합니다.
        else check = false;
    }
    // 검사 결과를 반환합니다.
    return check;
}

// 두 수가 가능한 조합인지 검사합니다.
bool isValidCombination(int a, int b) {
    vector<int> checkers (10, 0);
    return (checkRange(a, b) && checkDigit(checkers, a) && checkDigit(checkers, b));
}

// 자릿수의 합을 구합니다.
int getDigitSum(int a, int b) {
    int sum = 0;
    int ca = a, cb = b;
    // 두 수의 각 자리수의 합을 구합니다.
    while (ca != 0) {
        sum += (ca % 10);
        ca /= 10;
    }
    while (cb != 0) {
        sum += (cb % 10);
        cb /= 10;
    }
    return sum;
}

void output(int max_a, int max_b, int max_sum) {

}

// 문제를 해결하는 함수입니다.
void solution(int n) {
    int max_a = -1;
    int max_b = -1;
    int max_sum = 0;
    // 두자리 숫자부터 검사합니다.
    for (int i = 12; n - i > 0; i++) {
        int a = n - i;
        // 가능한 타입이면
        if (isValidCombination(a, i)) {
            int temp_sum = getDigitSum(a, i);
            // 저장된 최대 합보다 크면 스왑
            if (max_sum < temp_sum) {
                max_a = a;
                max_b = i;
                max_sum = temp_sum;
            }
        }
    }

    // 가능한 수 조합이 없다면 -1 출력
    if (max_a == -1) {
        cout << "-1" << "\n";
    }
    // 아니라면 3자리에 맞추어 두 수 출력
    else {
        int a = min(max_a, max_b);
        int b = max(max_a, max_b);
        if (a < 100) {
            cout << "0";
        }
        cout << a << " ";
        if (b < 100) {
            cout << "0";
        }
        cout << b << " ";
        cout << max_sum << "\n";
    }
}

// 메인 함수입니다.
int main(void) {
    int n;
    cin >> n;
    solution(n);
    return 0;
}