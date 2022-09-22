#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

struct f{
    int x, y, size; // x, y 좌표, 사이즈
};

struct p{
    f fish;
    int dist; // 상어까지의 거리
    int idx;
};

struct pp{
    int x, y, dist;
};

struct s{
    int x, y; // 상어 위치 좌표
    int size;
    int tmp, total; // 먹은 물고기 수 기록
};

struct compare{
    bool operator()(const p& p1, const p& p2){
        return p1.dist > p2.dist; // 오름차순 정렬
    }
};

int N; int res_time = 0;
int a[21][21] = {0, }; int ch[21][21] = {0, };
vector<f> fish;
s shark;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int bfs(int f_x, int f_y) {
    // 상어 위치에서 해당 x, y 좌표까지의 최단거리 구하기
    // 거리값을 Return
    queue<pp> q; // <상어위치, 이동시간>
    memset(ch, 0, sizeof(ch)); // ch 배열 초기화

    ch[shark.x][shark.y] = 1;
    q.push({shark.x, shark.y, 0});

    while(!q.empty()){
        pp tmp = q.front(); q.pop();

        if(tmp.x == f_x && tmp.y == f_y) return tmp.dist;

        for(int i=0; i<4; i++){
            int n_x = tmp.x + dx[i];
            int n_y = tmp.y + dy[i];

            if(n_x >=0 && n_x < N && n_y >=0 && n_y < N
            && a[n_x][n_y] <= shark.size && ch[n_x][n_y] == 0){
                ch[n_x][n_y] = 1;
                q.push({n_x, n_y, tmp.dist + 1});
            }
        }
    }

    return -1; // 가는 경로가 없다면 -> -1 반환
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // 입력
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> a[i][j];

            if(a[i][j] == 9){
                shark.x = i, shark.y = j, shark.size = 2, shark.tmp = 0, shark.total = 0, a[i][j] = 0;
            }
            else if(a[i][j] >= 1 && a[i][j] <= 6) fish.push_back({i, j, a[i][j]});
        }
    }
    // 입력 끝

    int i_size = fish.size();
    for(int i=0; i<i_size; i++){ // 물고기 개수만큼 반복문 돌리기
        // 현재 상어 위치에서 각 물고기 까지의 최단 거리 구하기(bfs 함수 이용) 그리고 우선순위 큐에 넣기
        priority_queue<p, vector<p>, compare> pq;

        for(int j=0; j<fish.size(); j++){
            if(fish[j].size >= shark.size) continue; // 크기가 상어 이상이면 -> x

            int dist = bfs(fish[j].x, fish[j].y);
            if(dist != -1) pq.push({fish[j], dist, j}); // 이동할 수 있는 경우에만 넣기
        }

        if(pq.empty()) break;

        // 우선순위 큐의 가장 첫 원소가 먹을 수 있는 최단거리의 물고기임
        p tmp = pq.top(); pq.pop();

        res_time += tmp.dist;

        // 상어 관련 정보 업데이트
        shark.total++;
        shark.tmp++;

        if(shark.tmp == shark.size){
            shark.size++;
            shark.tmp = 0;
        }

        a[tmp.fish.x][tmp.fish.y] = 0; // 물고기 먹은거 표시
        shark.x = tmp.fish.x, shark.y = tmp.fish.y; // 상어 위치 갱신
        fish.erase(fish.begin() + tmp.idx); // 해당 먹은 물고기는 지워주기

        while(!pq.empty()) pq.pop(); // 우선순위 큐 비우기
    }
    // for문 끝

    cout << res_time << endl;
    return 0;
}