#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstring>
#include <set>
#include <climits>
using namespace std;

typedef long long ll;

// 방향 -> (시작방향: ->) , 시계증가방향으로
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct p {
    int x, y;
};

struct snack {
    deque<p> dq;
    int dir;
};

int apple[101][101] = {0, };
int b[101][101] = {0, };
unordered_map<int, char> um;
snack s;
int N, K, L;

int moving(int time) {
    // step1. 먼저 몸길이를 늘려 머리를 다음칸에 위치
    int nX = s.dq.front().x + dx[s.dir];
    int nY = s.dq.front().y + dy[s.dir];

    if(!(nX >= 0 && nX < N && nY >= 0 && nY < N) || (b[nX][nY]) == 1) return 0;

    p pp; pp.x = nX; pp.y = nY;
    s.dq.push_front(pp);
    b[nX][nY] = 1;

    // step2. 이동한 칸에 사과가 있는지 확인
    if(apple[nX][nY] == 1) {
        // 사과가 있으면
        apple[nX][nY] = 0; // 사과 없애기
        // 꼬리는 움직이지 않는다
    }
    else {
        // 사과가 없으면 -> 이전 꼬리가 위치한 칸을 비워준다
        p pp; pp = s.dq.back();
        b[pp.x][pp.y] = 0; // 이전 꼬리가 위치한 칸 비우기
        s.dq.pop_back(); // 꼬리 하나 없애기
    }

    // 맨 마지막 -> 방향 전환
    if(um.find(time) != um.end()) { // 방향전환이 있으면 -> 방향전환 하기
        if(um[time] == 'L') { // 반시계 회전
            s.dir--;
            if(s.dir < 0) s.dir = 3;
        }
        else { // 시계 회전
            s.dir++;
            if(s.dir > 3) s.dir = 0;
        }
    }

    return 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N; // 보드의 크기
    cin >> K; // 사과의 수

    for(int i=0; i<K; i++) {
        int t1, t2; cin >> t1 >> t2;
        apple[t1-1][t2-1] = 1;
    }

    cin >> L; // 뱀의 방향 변환 횟수
    for(int i=0; i<L; i++) {
        int t; char c;
        cin >> t >> c;
        um.insert(make_pair(t, c));
    }

    p pp; pp.x = 0; pp.y = 0;
    b[0][0] = 1;
    s.dq.push_front(pp);
    s.dir = 0;

    int cnt = 1;

    while(1) {
        if(moving(cnt) == 0) {
            cout << cnt << endl;
            exit(0);
        }
        else cnt++;
    }

    return 0;
}