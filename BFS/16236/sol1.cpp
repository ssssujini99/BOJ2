#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

struct p{
    int x, y, t;
};

struct s{
    int x, y, idx, time;
};

struct compare{
    bool operator()(const s& s1, const s& s2){
        return s1.time > s2.time;
    }
};

// 방향좌표
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int N;
vector<p> fish;
int a[21][21] = {0, }; // 좌표 배열 : 0(빈칸) / 1~6(물고기) / 9(상어)
int ch[21][21] = {0, };
p shark; // 상어 위치
int shark_size = 2; int fish_tmp=0; int eaten_fish = 0; int res_time = 0;

int bfs(int tar_x, int tar_y){

    queue<p> q;
    memset(ch, 0, sizeof(ch));

    ch[shark.x][shark.y] = 1;
    q.push({shark.x, shark.y, 0});

    while(!q.empty()){
        p tmp = q.front(); q.pop();

        if(tmp.x == tar_x && tmp.y == tar_y){
            return tmp.t; // 걸린 시간 반환
        }

        for(int i=0; i<4; i++){
            int n_x = tmp.x + dx[i]; int n_y = tmp.y + dy[i];

            if(n_x >=0 && n_x < N && n_y >=0 && n_y < N && ch[n_x][n_y] == 0 && a[n_x][n_y] <= shark_size){
                // 범위 만족 && 이동할 수 있는 칸
                ch[n_x][n_y] = 1;
                q.push({n_x, n_y, tmp.t + 1});
            }
        }
    }

    while(!q.empty()) q.pop();
    return -1; // 이동할 수 없는 경우 -> 0 반환
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N; // 공간의 크기

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> a[i][j];
            if(a[i][j] == 9) shark.x = i, shark.y = j, a[i][j] = 0; // 상어 정보 기록

            if(a[i][j] >= 1 && a[i][j] <= 6) fish.push_back({i, j}); // 물고기 기록
        }
    }

    if(fish.size() == 0){ // 예외처리
        cout << 0;
        exit(0);
    }

    int i_size = fish.size();
    priority_queue<s, vector<s>, compare> pq;

    for(int i=0; i<i_size; i++){

        for(int j=0; j<fish.size(); j++){
            if(a[fish[j].x][fish[j].y] >= shark_size) continue;

            s s_tmp;
            s_tmp.x = fish[j].x, s_tmp.y = fish[j].y, s_tmp.idx = j, s_tmp.time = bfs(fish[j].x, fish[j].y);

            if(s_tmp.time != -1) pq.push(s_tmp);
        }

        if(pq.empty()) break;

        res_time += pq.top().time;
        fish.erase(fish.begin() + pq.top().idx);

        // 상어 위치 갱신
        shark.x = pq.top().x; shark.y = pq.top().y;
        eaten_fish++;
        fish_tmp++;

        if(fish_tmp == shark_size){
            shark_size ++;
            fish_tmp = 0;
        }

        while(!pq.empty()) pq.pop();
    }

    cout << res_time << endl;
    return 0;
}