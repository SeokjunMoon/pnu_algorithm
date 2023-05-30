#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int minPrice = numeric_limits<int>::max();
vector<int> minCombination;

// 영양소 정보를 저장할 구조체
struct Node {
    int mp;
    int mf;
    int ms;
    int mv;
    int price;
};


// 조합의 모든 영양소의 총합을 구합니다.
int getSum(vector<Node> nodes, vector<int> combination) {
    int sum = 0;
    for (int i = 0; i < combination.size(); i++) {
        sum += nodes[combination[i]].mp + nodes[combination[i]].mf + nodes[combination[i]].ms + nodes[combination[i]].mv;
    }
    return sum;
}


// dfs 호출 함수입니다.
void findMinPriceCombination(const vector<Node>& nodes, vector<int>& comb,
                             int index, int mp, int mf, int ms, int mv,
                             int max_p, int max_f, int max_s, int max_v,
                             int currentPrice) {
    
    // 최소값보다 현재 price가 더 크면 탐색 종료
    if (currentPrice > minPrice) return;
    
    // 영양소 충족 시
    if (mp <= 0 && mf <= 0 && ms <= 0 && mv <= 0) {
        // 최소값보다 작거나, 최소값과 같고 영양소의 총합이 더 크면 값 저장
        if (currentPrice < minPrice || 
            (currentPrice == minPrice && getSum(nodes, minCombination) < getSum(nodes, comb))) {
            minPrice = currentPrice;
            minCombination = comb;
        }
        return;
    }

    // 인덱스를 벗어나면 종료
    if (index >= nodes.size()) {
        return;
    }

    // 앞으로 더할 수 있는 모든 영양소를 더해도 기준치 미달이면 종료
    if (mp - max_p > 0 || mf - max_f > 0 || ms - max_s > 0 || mv - max_v > 0) {
        return;
    }

    // 다음 인덱스 추가
    comb.push_back(index);
    // 다음 영양소 업데이트
    int nextMp = mp - nodes[index].mp;
    int nextMf = mf - nodes[index].mf;
    int nextMs = ms - nodes[index].ms;
    int nextMv = mv - nodes[index].mv;
    int nextPrice = currentPrice + nodes[index].price;
    // 다음 노드 탐색
    findMinPriceCombination(nodes, comb, index + 1, nextMp, nextMf, nextMs, nextMv,
                            max_p - nodes[index].mp, max_f - nodes[index].mf, max_s - nodes[index].ms, max_v - nodes[index].mv,
                            nextPrice);
    
    // 안넣는 경우
    comb.pop_back();

    // 다음 노드 탐색
    findMinPriceCombination(nodes, comb, index + 1, mp, mf, ms, mv,
                            max_p - nodes[index].mp, max_f - nodes[index].mf, max_s - nodes[index].ms, max_v - nodes[index].mv,
                            currentPrice);
}


int main() {
    // 입력받기
    int n;
    cin >> n;

    int lp, lf, ls, lv, prc;
    int max_p = 0, max_f = 0, max_s = 0, max_v = 0;
    cin >> lp >> lf >> ls >> lv;
    
    int mp = lp;
    int mf = lf;
    int ms = ls;
    int mv = lv;

    vector<Node> nodes;
    for (int i = 0; i < n; i++) {
        cin >> lp >> lf >> ls >> lv >> prc;
        Node temp = {lp, lf, ls, lv, prc};
        max_p += lp;
        max_f += lf;
        max_s += ls;
        max_v += lv;
        nodes.push_back(temp);
    }

    // 모든 영양소의 합이 기준치 미달이면 바로 종료
    if (max_p < mp || max_f < mf || max_s < ms || max_v < mv) {
        cout << "0 " << endl;
        return 0;
    }

    // 모든 영양소를 더해야 기준치일 경우 모든 노드 출력 후 종료
    if (max_p == mp || max_f == mf || max_s == ms || max_v == mv) {
        for (int i = 0; i < nodes.size(); i++) {
            cout << i + 1 << " ";
        }
        cout << endl;
        return 0;
    }

    // 탐색 시작
    vector<int> combination;
    findMinPriceCombination(nodes, combination, 0, mp, mf, ms, mv,
                            max_p, max_f, max_s, max_v,
                            0);

    // 탐색 후 조합이 없으면 빈 배열 출력
    if (minCombination.empty()) {
        cout << "0 " << endl;
    }
    // 아니면 조합 출력
    else {
        sort(minCombination.begin(), minCombination.end());
        for (int i = 0; i < minCombination.size(); i++) {
            cout << minCombination[i] + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
