#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INT_MAX 2147483647


void input(vector<vector<long long>>& W, int N) {
    long long from, to, weight;
    for (int i = 0; i < N; i++) {
        cin >> from >> to >> weight;
        W[from][to] = weight;
        W[to][from] = weight;
    }
}

void calculation(vector<vector<long long>>& W, vector<vector<long long>>& D, vector<vector<long long>>& P, int N) {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                long long temp = D[i][k] + D[k][j];
                if (temp < D[i][j]) {
                    P[i][j] = k;
                    D[i][j] = temp;
                }
            }
        }
    }
}

void visit(vector<vector<long long>>& W, vector<vector<long long>>& P, int start, int end, vector<int>& points) {
    if (P[start][end] != 0) {
        visit(W, P, start, P[start][end], points);
        points.push_back(P[start][end]);
        visit(W, P, P[start][end], end, points);
    }
}

int getWeight(vector<vector<long long>>& W, vector<int>& points) {
    if (points.size() == 0) return 0;
    long long sum = 0;
    for (int i = 1; i < points.size(); i++) {
        sum += W[points[i - 1]][points[i]];
    }
    return sum;
}

int getTime(vector<vector<long long>>& W, vector<vector<long long>>& P, int c1, int c2, int point) {
    vector<int> c1p;
    c1p.push_back(c1);
    visit(W, P, c1, point, c1p);
    c1p.push_back(point);

    vector<int> c2p;
    c2p.push_back(c2);
    visit(W, P, c2, point, c2p);
    c2p.push_back(point);

    return min(getWeight(W, c1p), getWeight(W, c2p));
}

void solution(vector<vector<long long>>& W, vector<vector<long long>>& P, int N, int c1, int c2) {
    vector<pair<int, int>> times;
    for (int i = 1; i <= N; i++) {
        if (i != c1 && i != c2) {
            times.push_back({getTime(W, P, c1, c2, i), i});
        }
    }

    sort(times.begin(), times.end());
    for (int i = 0; i < times.size(); i++) {
        cout << times[i].second << "\n";
    }
}

int main(void) {
    int N, c1, c2;
    cin >> N >> c1 >> c2;
    vector<vector<long long>> W (N + 1, vector<long long> (N + 1, INT_MAX));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) W[i][j] = 0;
        }
    }
    input(W, N - 1);

    vector<vector<long long>> D;
    vector<vector<long long>> P (N + 1, vector<long long> (N + 1, 0));
    D.assign(W.begin(), W.end());
    
    calculation(W, D, P, N);
    solution(W, P, N, c1, c2);

    return 0;
}