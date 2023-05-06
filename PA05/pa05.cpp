#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// 입력받는 함수입니다.
void input(vector<int>& frame, int n) {
    for (int i = 0; i < n; i++) {
        cin >> frame[i];
    }
}

// 해당 프레임이 순서대로 정렬된 프레임인지 확인합니다.
bool check(vector<int>& frame) {
    for (int i = 0; i < frame.size(); i++) {
        if (frame[i] != i + 1) return false;
    }
    return true;
}

// 프레임에서 해당 숫자의 인덱스를 구합니다. (부호 무관하게 해당 숫자와 동일한 곳의 위치를 반환)
int find_index(vector<int> frame, int num) {
    for (int i = 0; i < frame.size(); i++) {
        if (num == frame[i] || num == -frame[i]) return i;
    }
    return 0;
}

// 붕어빵 틀을 뒤집습니다.
vector<int> reverse_frame(vector<int> frame, int start) {
    for (int i = start; i < frame.size(); i++) {
        //순서가 틀렸다면
        if (frame[i] != i + 1) {
            // 인덱스 찾기
            int temp = find_index(frame, i + 1);
            // 이후에 존재하면
            if (temp > i) {
                // 뒤집기
                reverse(frame.begin() + i, frame.begin() + temp + 1);
                // 뒤집은 구간 부호 반전
                for (int j = i; j < temp + 1; j++) {
                    frame[j] *= -1;
                }
                // 뒤집은 프레임 반환
                return frame;
            }
            // 이전에 존재하면
            else if (temp < i) {
                // 뒤집기
                reverse(frame.begin() + temp, frame.begin() + i + 1);
                // 뒤집은 구간 부호 반전
                for (int j = temp; j < i + 1; j++) {
                    frame[j] *= -1;
                }
                // 뒤집은 프레임 반환
                return frame;
            }
            // 그 외의 경우 = 해당 자리이면서 부호만 반전
            else {
                frame[temp] *= -1;
                return frame;
            }
        }
    }
    return frame;
}

// 풀이 함수입니다.
void solve(vector<int>& frame, int n) {
    vector<int> temp;
    bool flag = false;

    // 뒤집을 필요가 없을 경우
    if (check(frame)) { 
        cout << "zero" << endl;
        flag = true;
    }
    // 아니라면
    else {
        // 프레임 순차적으로 읽기
        for (int i = 0; i < frame.size(); i++) {
            // 프레임 반전
            temp = reverse_frame(frame, i);
            // 1회 반전 후 체크
            if (check(temp)) {
                // 정렬이 완료된 경우 출력
                cout << "one" << endl;
                flag = true;
                break;
            }
            // 아니라면
            else {
                // 다시 뒤집기
                temp = reverse_frame(temp, 0);
                // 정렬이 완료된 경우 출력
                if (check(temp)) {
                    cout << "two" << endl;
                    flag = true;
                    break;
                }
            }
        }
    }
    // 2번 뒤집고도 정렬이 완료되지 않은 경우 출력
    if (flag == false) cout << "over" << endl;
}

int main(void) {
    int n;
    cin >> n;

    // 프레임 입력받기
    vector<vector<int>> frames(5, vector<int> (n, 0));
    for (int i = 0; i < 5; i++) {
        input(frames[i], n);
    }

    // 입력받은 프레임 풀기
    for (int i = 0; i < 5; i++) {
        solve(frames[i], n);
    }

    return 0;
}