#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


// pattern과 text를 입력받기 위한 함수입니다.
void input(int lines, string& str) {
    string tmp;
    for (int i = 0; i < lines; i++) {
        cin >> tmp;
        str += tmp;
    }
}


// Rabin-Karp 알고리즘입니다.
int RabinKarp(string& text, string& pattern, int d, int q) {
    int count = 0;

    int n = int(text.length());
    int m = int(pattern.length());
    int h = 1, p = 0, b = 0;

    // 초기 p, b 값을 구합니다.
    for (int i = 0; i < m; i++) {
        p = (d * p + int(pattern[i] - 'A')) % q;
        b = (d * b + int(text[i] - 'A')) % q;
        if (i != 0) h = (h * d) % q;
    }

    // text를 스캔합니다.
    for (int i = 0; i < n - m + 1; i++) {
        // b값 업데이트
        if (i != 0) {
            b = (d * (b - h * int(text[i - 1] - 'A')) + int(text[i + m - 1] - 'A')) % q;
            if (b < 0) b += q;
        }

        // 비교시작 전 비교 횟수 증가
        count++;
        //패턴과 텍스트의 가중치 비교
        if (p == b) {
            bool check = true;
            for (int j = 0; j < m; j++) {
                // 비교횟수 증가
                count++;
                // 패턴과 불일치 하면 종료
                if (pattern[j] != text[i + j]) {
                    check = false;
                    break;
                }
            }
            //일치하면 count 반환
            if (check) {
                return count;
            }
        }
    }
    return -1;
}


// KMP 알고리즘 사용을 위해 SP 테이블을 생성하는 함수입니다.
void preprocessing(string& pattern, vector<int>& sp, int m) {
    int k = -1;
    sp[0] = -1;

    for (int j = 1; j < m; j++) {
        while (k >= 0 && pattern[j] != pattern[k + 1]) k = sp[k];
        if (pattern[j] == pattern[k + 1]) k++;
        sp[j] = k;
    }
}

// KMP 알고리즘입니다.
int KMP(string& text, string& pattern) {
    int count = 0;
    int n = int(text.length());
    int m = int(pattern.length());

    vector<int> sp (m, 0);
    preprocessing(pattern, sp, m);
    int j = -1;

    for (int i = 0; i < n; i++) {
        // 텍스트의 현재 위치와 패턴을 비교합니다.
        while (j >= 0 && text[i] != pattern[j + 1]) {
            j = sp[j];
            count++;
        }
        count++;
        if (pattern[j + 1] == text[i]) j++;
        // 미스매칭이 없다면, count를 반환합니다.
        if (j == m - 1) {
            return count;
        }
    }
    return -1;
}


// BM 알고리즘을 위한 jump 테이블을 생성합니다.
void computeSkip(string& pattern, vector<int>& jump) {
    int m = pattern.length();
    for (int i = 0; i < 256; i++)
        jump[i] = -1;

    for (int i = 0; i < m; i++)
        jump[pattern[i]] = i;
}

// BM 알고리즘
int BoyerMoore(string& text, string& pattern) {
    int count = 0;
    int n = int(text.length());
    int m = int(pattern.length());
    int i = 0;

    vector<int> jump (256, m);
    computeSkip(pattern, jump);

    // 텍스트를 읽습니다.
    while (i <= n - m) {
        int j = m - 1;
        count++;
        // j값을 오른쪽 끝부터 탐색합니다.
        // 패턴과 텍스트가 일치할 때까지 반복합니다.
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
            count++;
        }
        // 0번 인덱스까지 비교하여 일치하면 count를 반환합니다.
        if (j < 0) {
            count--;
            return count;
        }
        // jump 테이블에 맞게 다음 위치로 점프합니다.
        i += max(1, j - jump[text[i + j]]);
    }

    return -1;
}


// 결과를 출력합니다.
void print(int a, int b, int c) {
    vector< pair<int, int> > pr;
    pr.push_back(make_pair(a, 1));
    pr.push_back(make_pair(b, 2));
    pr.push_back(make_pair(c, 3));
    if (a == b) pr[0].second = pr[1].second = 0;
    if (a == c) pr[0].second = pr[2].second = 0;
    if (b == c) pr[1].second = pr[2].second = 0;
    sort(pr.begin(), pr.end());
    cout << pr[0].second << " " << pr[1].second << " " << pr[2].second << endl;
}


int main(void) {
    int pattern_lines, text_lines;
    string pattern, text;

    cin >> pattern_lines;
    input(pattern_lines, pattern);
    
    cin >> text_lines;
    input(text_lines, text);

    int rabin_karp_count = RabinKarp(text, pattern, 2, 30011);
    int kmp_count = KMP(text, pattern);
    int boyer_moore_count = BoyerMoore(text, pattern);

    print(rabin_karp_count, kmp_count, boyer_moore_count);
    
    return 0;
}