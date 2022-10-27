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
using namespace std;

int dx[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dy[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

struct rec {
    int x, y; // 좌표
    int d; // 방향
};

map <int, rec> m;
int a[4][4] = {0, }; // 물고기번호: 1~16, 상어: -1, 빈칸: 0
rec shark; // 상어 좌표
int res = 0; int tmp_res = 0; // 상어가 먹은 물고기 번호 누적

void eat_fish(int x, int y){
    // 상어가 x, y 좌표에 있는 물고기 먹기
    a[shark.x][shark.y] = 0; // 원래 상어의 위치는 빈칸으로
    tmp_res += a[x][y]; // 결과값 갱신
    shark.x = x, shark.y = y, shark.d = m[a[x][y]].d; // 상어 위치 갱신
    m[-1].d = shark.d;
    m.erase(a[x][y]); // 먹힌 물고기 삭제
    a[x][y] = -1; // 상어 위치 표기
}

void move_fish(){
    for(auto iter = m.begin(); iter != m.end(); iter++){
        if(iter->first <= 0) continue;
        int num = iter->first; rec r = iter->second;
        int xx = r.x ; int yy = r.y; int dd = r.d;

        // 물고기가 이동할 좌표 찾기
        int n_x = -1, n_y = -1;

        for(int i=0; i<8; i++){
            n_x = xx + dx[dd];
            n_y = yy + dy[dd];

            if(n_x >= 0 && n_x < 4 && n_y >=0 && n_y < 4 && a[n_x][n_y] != -1) break;
            dd++;
            if(dd == 9) dd = 1;
        }

        if(n_x != -1 && n_y != -1){
            // 해당 위치의 물고기와 좌표 바꾸기 xx, yy <-> n_x, n_y
            int tmp_num = a[n_x][n_y];
            m[num].x = n_x; m[num].y = n_y; m[num].d = dd; // 방향이 바꾸면 방향갱신도 필요
            m[tmp_num].x = xx ; m[tmp_num].y = yy;
            a[n_x][n_y] = num; a[xx][yy] = tmp_num;
        }
    }
}


void backtracking(){
    if(tmp_res > res) res = tmp_res; // 결과 갱신시키기

    // First step: 물고기 이동시키기
    move_fish();

    // Second step: 상어 이동시키기
    for(int i=1; i<4; i++){ // 상어가 이동할 수 있는 경우는 최대 3가지 (같은 라인에서)
        int s_x = shark.x, s_y = shark.y, s_d = shark.d;
        int n_x, n_y, n_d;
        n_x = shark.x + i * dx[shark.d];
        n_y = shark.y + i * dy[shark.d];
        n_d = shark.d;

        if(!(n_x >=0 && n_x < 4 && n_y >=0 && n_y < 4)) break; // 범위 벗어나면 -> out

        if(a[n_x][n_y] > 0){ // 유망하다면
            // 상태변화 // 재귀호출 -> 상어 이동 후 물고기 먹기 // 상태복구

            // 이전 상태 기록
            int eaten_fish = a[n_x][n_y];
            map<int, rec> m_tmp = m;
            int a_tmp[4][4]; copy(&a[0][0], &a[0][0] + 16, &a_tmp[0][0]);
            rec shark_tmp = shark;

            // 상태 변화
            eat_fish(n_x, n_y); // 상어가 물고기 먹기

            // 재귀 호출
            backtracking();

            // 상태 복구
            swap(m, m_tmp);
            swap(a, a_tmp);
            swap(shark, shark_tmp);
            tmp_res -= eaten_fish;
        }

    } // for문 끝
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            int f, d; cin >> f >> d;
            rec r = {i, j, d};
            m[f] = r;
            a[i][j] = f;
        }
    }

    // 청소년 상어는 (0, 0)에 있는 물고기를 먹고, (0, 0)에 들어감
    tmp_res += a[0][0];
    shark.x = 0, shark.y = 0; shark.d = m[a[0][0]].d;
    m[-1] = {0, 0, m[a[0][0]].d};
    m.erase(a[0][0]);
    a[0][0] = -1;

    // 백트래킹 이용하기
    backtracking();

    // 결과
    cout << res << endl;

    return 0;
}