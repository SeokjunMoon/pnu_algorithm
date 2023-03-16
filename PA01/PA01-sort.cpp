#include <iostream>
#include <vector>
using namespace std;


// 입력으로 받을 정보들을 저장할 전역 변수입니다.
int type, n, k;
// 입력받은 배열의 원소들을 저장할 벡터입니다.
vector<int> inputs;
// quick sort의 경우, pivot의 인덱스를 위한 변수입니다.
int pivot_count = 0;
// quick sort에서 pivot의 수보다 k가 클 경우를 잡기 위한 변수입니다.
bool finded = false;


// 입력을 받을 함수입니다.
void input() {
    cin >> type >> k;
    cin >> n;
    int temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        inputs.push_back(temp);
    }
}

// 삽입정렬 입니다.
void insertion() {
    int count = 0;
    // 2번째 원소의 인덱스는 1이므로 1부터 배열을 순회합니다.
    for (int i = 1; i < n; i++) {
        // 정렬하고자 하는 수 입니다.
        int key = inputs[i];
        // 정렬하고자 하는 수 이전을 탐색하기 위한 iterator 입니다.
        int j = i - 1;
        // 인덱스가 0 이상이고, 정렬하고자 하는 수보다 큰 경우
        // 해당 원소를 1칸 다음으로 이동시킵니다.
        // 그리고 j를 감소시켜 배열을 탐색합니다.
        // 이 때 원소 비교가 일어나므로 count를 1씩 더합니다.
        while(j >= 0 && inputs[j] > key) {
            inputs[j + 1] = inputs[j];
            count++;
            j--;
        }
        // while문은 들어가야할 자리보다 1 감소한 인덱스에서 종료됩니다.
        // 따라서 j + 1 번째에 해당 원소를 집어넣습니다.
        inputs[j + 1] = key;
        // 맨 앞에 들어가는게 아니라면, 해당 원소는 들어가야할 자리 앞에 원소와도
        // 1회 비교합니다. 따라서 이 경우에 count를 1 증가시켜야 합니다.
        if (j + 1 != 0) count++;
        // 문제에서 요구하는 k번째일 경우, 정렬을 종료합니다.
        if (i == k) break;
    }
    // 원소를 출력합니다.
    if (n >= k) cout << count << "\n";
}

// 선택정렬 입니다.
void selection(int iter) {
    // 인덱스 범위 밖이면 종료합니다.
    if (iter >= n) return;
    // k번째 수의 정렬이 끝나면, 배열 상태를 출력합니다.
    if (iter == k) {
        for (int i = 0; i < n; i++) {
            cout << inputs[i] << "\n";
        }
        return;
    }
    // 해당 인덱스 이 후의 배열 중에서 최소값을 찾는 과정입니다.
    int min_index = iter;
    for (int i = iter + 1; i < n; i++) {
        if (inputs[i] < inputs[min_index]) {
            min_index = i;
        }
    }
    // 최소값과 현재 위치의 원소를 교환합니다.
    swap(inputs[iter], inputs[min_index]);
    // 다음 원소에 대해서 동일한 과정을 반복합니다.
    selection(iter + 1);
}

// 힙정렬 입니다.
// 힙을 재구축하는 함수입니다.
void updateHeap(int root, int size) {
    // min tree의 root 인덱스는 1부터 시작입니다. 따라서
    // 현재 노드의 왼쪽 자식은 현재 인덱스의 2배입니다.
    int left = root * 2;
    // 현재 노드의 오른쪽 자식은 현재 인덱스의 2배 + 1 입니다.
    int right = root * 2 + 1;
    // iterator 입니다.
    int smallest = root;

    // 왼쪽 자식이 현재 노드보다 작거나 같으면 왼쪽으로 이동합니다.
    if (left <= size && inputs[left] <= inputs[smallest]) {
        smallest = left;
    }
    // 오른쪽 자식이 현재 노드보다 작거나 같으면 오른쪽으로 이동합니다.
    if (right <= size && inputs[right] <= inputs[smallest]) {
        smallest = right;
    }
    // 만약 이동이 발생한다면 해당 원소를 바꾸고 이동한 인덱스에서 다시 재구축을 실행합니다.
    if (smallest != root) {
        swap(inputs[root], inputs[smallest]);
        updateHeap(smallest, size);
    }
}

// 힙정렬 메인코드 입니다.
void heap() {
    // 시작 인덱스가 1인 경우 전체적인 노드 인덱스 탐색이 편합니다.
    // 자식은 2배, 2배+1 로 나누어 떨어집니다.
    inputs.insert(inputs.begin(), 0);

    // internal 노드의 시작은 전체 원소의 개수의 절반입니다.
    // 루트 노드까지 입력받은 배열을 재구축합니다.
    for (int i = n / 2; i >= 1; i--) {
        updateHeap(i, n);
    }
    
    // 재구축이 완료된 후, k개의 원소를 힙에서 제거해야 합니다.
    for (int i = 0; i < k; i++) {
        // 힙이 비어있으면 종료입니다.
        if (inputs.empty()) break;
        // 루트 노드와 맨 마지막 노드를 바꿉니다.
        inputs[1] = inputs[inputs.size() - 1];
        // 마지막 원소를 삭제합니다.
        inputs.pop_back();
        // 개수가 1 줄어들었으므로 n을 1 감소시킵니다.
        n--;
        // 힙을 재구축합니다.
        updateHeap(1, n);
    }

    // k개의 원소를 삭제한 후 힙의 상태를 출력합니다.
    for (int i = 1; i <= n; i++) {
        cout << inputs[i] << "\n";
    }
}


// 퀵정렬 입니다.
// [low, high] 구간을 분할한 후에 pivot이 들어간 인덱스를 반환합니다.
int partition(int low, int high) {
    // 왼쪽 iterator의 시작은 low 입니다.
    int left = low;
    // 오른쪽 iterator의 시작은 high 입니다.
    int right = high;
    // pivot은 해당 구간의 첫번째 원소입니다.
    int pivot = inputs[low];

    // 두 iterator의 교차가 일어나기 전까지 반복합니다.
    while (left < right) {
        // 왼쪽에서 탐색하는 경우는 pivot보다 큰 원소를 잡아냅니다.
        while (left <= high && inputs[left] <= pivot) left++;
        // 오른쪽에서 탐색하는 경우는 pivot보다 작은 원소를 잡아냅니다.
        while (right > low && inputs[right] > pivot) right--;
        // 교차가 일어나지 않았다면, 두 원소를 교환합니다.
        if (left < right) swap(inputs[left], inputs[right]);
    }
    // 분할이 완료되었습니다.
    // 교차가 진행되었기 때문에 pivot보다 작은 배열 중에서 가장 오른쪽 인덱스는
    // 오른쪽 iterator의 인덱스입니다.
    // 따라서 두 원소를 교환해줍니다.
    swap(inputs[low], inputs[right]);

    // pivot이 들어간 인덱스를 반환합니다.
    return right;
}

// 퀵정렬 메인 함수입니다.
// [low, hight] 구간에서 분할 후 정렬합니다.
void quick(int low, int high) {
    // 정렬 구간의 교차가 일어난 경우, 정렬을 종료합니다.
    if (low >= high) return;

    // 입력으로 들어온 구간을 분할한 후 pivot의 위치를 저장합니다.
    int pivot = partition(low, high);
    // pivot의 인덱스를 1 증가시킵니다.
    pivot_count++;

    // k번째 pivot이었다면, 배열 상태를 출력합니다.
    if (pivot_count == k) {
        finded = true;
        for (int i = 0; i < n; i++) {
            cout << inputs[i] << "\n";
        }
    }

    // 아닐 경우, pivot을 기준으로 구간을 분할하고 정렬을 시행합니다.
    quick(low, pivot - 1);
    quick(pivot + 1, high);
}

// 입력을 받고 케이스에 따라 정렬을 진행하기 위한 함수입니다.
void solve() {
    // 입력을 받습니다.
    input();
    // 입력에서 정렬 type에 따라 정렬 방법을 선택합니다.
    // 선택된 정렬 방법으로 정렬을 시행합니다.
    switch(type) {
        case 1:
            insertion(); 
            break;
        case 2:
            selection(0); 
            break;
        case 3:
            heap();
            break;
        case 4:
            quick(0, n - 1);
            // pivot의 수 보다 k가 작을 경우 정렬된 배열을 출력합니다.
            if (!finded) {
                for (int i = 0; i < n; i++) {
                    cout << inputs[i] << "\n";
                }
            }
            break;
    }
}

int main(void) {
    solve();
    return 0;
}