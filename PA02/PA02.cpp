#include <iostream>
#include <vector>
using namespace std;


// 스케쥴표에서 소음 발생 정도를 업데이트 합니다.
void update(vector<int>& table, int start, int end, int noise) {
    for (int i = start; i < end; i++) {
        table[i] += noise;
    }
}

// 각 하청업체의 작업 일정을 입력받습니다.
void task_input(vector<int>& table) {
    int company_task, start, end, noise;
    // 작업 개수를 입력받습니다.
    cin >> company_task;
    for (int j = 0; j < company_task; j++) {
        // 작업 일정 정보를 입력받습니다.
        cin >> start >> end >> noise;
        // 입력받은 정보를 바탕으로 스케쥴표를 업데이트 합니다.
        update(table, start, end, noise);
    }
}

// 스케쥴표에서 연구량의 최댓값을 구합니다.
int getMax(vector<int> table) {
    // 누적합을 저장할 배열을 선언합니다.
    vector<int> cache (table.size(), 0);
    // 첫번째는 스케줄표의 첫 시간대의 연구량과 같습니다.
    cache[0] = table[0];
    // 배열을 순회하면서 누적합을 구합니다.
    // 부분 구간의 최댓값이므로 음수가될 경우엔 해당 지점에서부터 다시 시작합니다.
    for (int i = 1; i < table.size(); i++) {
        cache[i] = max(0, cache[i - 1]) + table[i];
    }

    // 계산한 구간합 중에서 최댓값을 구합니다.
    int result = cache[0];
    for (auto element : cache) {
        if (result < element) result = element;
    }

    // 최댓값을 반환합니다.
    return result;
}

// 프로그램 메인함수 입니다.
int main(void) {
    int task, time;
    // 기본 연구량과 시간대를 입력받습니다.
    cin >> task >> time;
    // 입력받은 시간대 만큼의 배열을 생성하고
    // 각 원소를 기본 연구량으로 초기화합니다.
    vector<int> table (time, task);

    // 하청업체 수를 입력받습니다.
    int company_count;
    cin >> company_count;

    // 각 하청업체별 작업 일정을 입력받습니다.
    int company_task, start, end, noise;
    for (int i = 0; i < company_count; i++) {
        task_input(table);
    }

    // 연구량의 최댓값을 구하여 출력합니다.
    cout << getMax(table) << endl;
    return 0;
}