#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
using namespace std;


// 입력받기 위한 변수 선언
int m, n;
int sx, sy, ex, ey;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// best-first-search 에서 정보 저장을 위한 노드 선언
struct Node {
    int x;
    int y;
    int g;
    int h;
    // Node* from;
};

// priority_queue 우선순위 설정을 위한 구조체
struct compare {
    bool operator() (Node* a, Node* b) {
        return (a->g + a->h) > (b->g + b->h);
    }
};

// 장애물 공간을 0으로 바꾸기 위한 함수
void blocking(vector<vector<int>>& map, int sx, int sy, int ex, int ey) {
    // 작은 좌표를 시작점으로, 큰 좌표를 종료점을 설정
    int ssx = min(sx, ex), ssy = min(sy, ey);
    int eex = max(sx, ex), eey = max(sy, ey);

    // 해당 공간 안의 영역을 0으로 채우기
    for (int x = ssx; x <= eex; x++) {
        for (int y = ssy; y <= eey; y++) {
            map[x][y] = 0;
        }
    }
}

// 유클리안 거리 계산을 위한 함수
int getEuclideanDistance(int x1, int y1, int x2, int y2) {
    int ddx = pow(x2 - x1, 2), ddy = pow(y2 - y1, 2);
    return sqrt(ddx + ddy);
}

int main(void) {
    // 지도 크기 입력
    cin >> m >> n;
    // 지도 크기에 맞는 배열과 방문 노드 표시를 위한 배열 선언
    vector<vector<int>> map(n + 1, vector<int> (m + 1, 1));
    vector<vector<int>> visited(n + 1, vector<int> (m + 1, 0));
    
    // 블럭 개수 입력
    int block_count;
    cin >> block_count;

    // 블럭 처리
    int input_type, ix, iy;
    for (int i = 0; i < block_count; i++) {
        cin >> input_type >> ix >> iy;
        map[ix][iy] = 0;
    }

    // 시작점, 종료점 입력
    string itype;
    cin >> itype >> sx >> sy;
    cin >> itype >> ex >> ey;

    // 장애물 개수 입력
    int obstacle_count;
    cin >> itype >> obstacle_count;

    // 장애물 처리
    int osx, osy, oex, oey;
    for (int i = 0; i < obstacle_count; i++) {
        cin >> osx >> osy >> oex >> oey;
        blocking(map, osx, osy, oex, oey);
    }

    // best-first-search 를 위한 priority_queue 선언
    priority_queue<Node*, vector<Node*>, compare> bfs;
    // 시작 노드 추가
    Node* start_node = new Node;
    start_node->x = sx;
    start_node->y = sy;
    start_node->g = 0;
    start_node->h = 0;
    // start_node->from = nullptr;

    bfs.push(start_node);
    visited[sx][sy] = 1;

    // priority_queue가 비거나 종점을 찾을 때까지 반복
    while (!bfs.empty()) {
        // 우선순위가 가장 높은 노드 선택
        Node* current = bfs.top(); bfs.pop();
        // 4방위 반복을 위한 반복문
        for (int i = 0; i < 4; i++) {
            // 방문 예정인 노드의 좌표
            int next_x = current->x + dx[i];
            int next_y = current->y + dy[i];

            // 만약 해당 노드가 지도 밖이거나, 방문 불가인 곳이거나, 방문한 노드면 건너뛰기
            if (next_x < 0 || next_x > m || next_y < 0 || next_y > n || 
                map[next_x][next_y] == 0 || visited[next_x][next_y] == 1) continue;

            // 방문할 노드가 종료점이면 해당 노드의 가중치 출력 후 종료
            if (next_x == ex && next_y == ey) {
                // Node* iters = current;
                // while (iters->from != nullptr) {
                //     cout << "(" << iters->x << ", " << iters->y << "), ";
                //     iters = iters->from;
                // }
                cout << (current->g + 1 + getEuclideanDistance(next_x, next_y, ex, ey)) * 3 << endl;
                return 0;
            }

            // 방문할 노드 정보 생성
            Node* nd = new Node;
            nd->x = next_x;
            nd->y = next_y;
            nd->g = current->g + 1;
            nd->h = getEuclideanDistance(next_x, next_y, ex, ey);
            // nd->from = current;

            // 큐에 추가 및 방문 표시
            bfs.push(nd);
            visited[nd->x][nd->y] = 1;
        }
    }

    return 0;
}