#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;


// 최소 거리를 저장할 변수
int min_distance = numeric_limits<int>::max();
// 최소 거리 조합
vector<int> minPath;


// 위치 정보 저장을 위한 구조체
struct Vertex {
    int idx;
    int x;
    int y;

    Vertex(int idx_, int x_, int y_) : idx(idx_), x(x_), y(y_) {};
};


// 두 점 사이의 거리 구하는 함수
int getDistance(Vertex a, Vertex b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}


// 방문 가능한 순서인지 확인합니다.
bool isValidOrder(vector<int> path, int idx) {
    // 사이즈 == 1 인 경우는 시작인 경우이므로 인덱스가 홀수이면 무조건 방문 가능
    if (path.size() == 1) return idx % 2 != 0;

    // 인덱스가 홀수면 항상 방문 가능
    if (idx % 2 == 1) return true;

    // 인덱스가 짝수이면 바로 직전 인덱스를 방문해야만 방문 가능
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == idx - 1) return true;
    }

    // 아니면 방문 불가
    return false;
}


// depth-first-search를 이용한 트리 탐색
void dfs(vector<Vertex>& vertices, vector<vector<int> >& distance, vector<int>& path, int total, int visited, int count) {
    // 가방의 크기 = 2 이므로 2 이상의 경우 종료
    if (count > 2) return;
    // 백트래킹 - 현재 최소값보다 높은 가중치인 경우 바로 종료
    if (total > min_distance) return;
    // 모든 정점 방문이 완료된 경우
    if (path.size() == vertices.size()) {
        // 현재 최소보다 작으면 업데이트
        if (total < min_distance) {
            min_distance = total;
            minPath = path;
        }
        return;
    }

    // 다음 노드 방문
    // 사전순 방문을 위해 인덱스가 가장 작은 노드부터 방문해야 하므로
    // 짝수번 인덱스를 역순으로 먼저 탐색
    for (int i = vertices.size() - 1; i > 1; i -= 2) {
        // 유효한 순서이면서 방문하지 않은 노드인 경우 방문
        if (isValidOrder(path, i) && !(visited & (1 << i))) {
            int newTotal = total + distance[path.back()][i];
            int newCount = count;

            path.push_back(i);

            if (i % 2 == 1) newCount++;
            else newCount--;

            dfs(vertices, distance, path, newTotal, visited | (1 << i), newCount);
            path.pop_back();
        }
    }
    // 인덱스가 양수인 부분을 오름차순으로 방문
    for (int i = 1; i < vertices.size(); i += 2) {
        if (isValidOrder(path, i) && !(visited & (1 << i))) {
            int newTotal = total + distance[path.back()][i];
            int newCount = count;

            path.push_back(i);

            if (i % 2 == 1) newCount++;
            else newCount--;

            dfs(vertices, distance, path, newTotal, visited | (1 << i), newCount);
            path.pop_back();
        }
    }
}


// 메인 함수
int main() {
    // 배달 개수 입력
    int n;
    cin >> n;

    int fromX, fromY, toX, toY;
    // 배달 1개당 2개의 노드 방문이 생기고 시작 노드 1개 만큼 공간 생성
    int MAX_SIZE = 2 * n + 1;
    // 거리 저장을 위한 백터 선언
    vector<vector<int> > distance(MAX_SIZE, vector<int>(MAX_SIZE, 0));

    // 시작 노드 설정
    Vertex start_vertex = Vertex(0, 500, 500);
    vector<Vertex> vertices;
    vertices.push_back(start_vertex);

    // 배달지 정보 입력
    for (int i = 0; i < 2 * n; i += 2) {
        cin >> fromX >> fromY >> toX >> toY;
        Vertex from = Vertex(i, fromX, fromY);
        Vertex to = Vertex(i + 1, toX, toY);
        vertices.push_back(from);
        vertices.push_back(to);
    }

    // Calculate Manhattan distance between vertices
    for (int x = 0; x < MAX_SIZE; x++) {
        for (int y = 0; y < MAX_SIZE; y++) {
            distance[x][y] = getDistance(vertices[x], vertices[y]);
        }
    }

    // 방문 정보 저장을 위한 백터 생성
    vector<int> path;
    path.push_back(0);
    // 방문 시작
    dfs(vertices, distance, path, 0, 1, 0);

    // 결과 출력
    for (int i = 1; i < minPath.size(); i++) {
        if (minPath[i] == 1) cout << "1 ";
        else if (minPath[i] == 2) cout << "-1 ";
        else if (minPath[i] % 2 == 0) cout << -1 * int(minPath[i] / 2) << " ";
        else cout << int(minPath[i] / 2) + 1 << " ";
    }
    cout << endl;
    cout << min_distance << endl;

    return 0;
}
