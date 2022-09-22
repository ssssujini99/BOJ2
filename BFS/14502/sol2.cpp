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
    int x, y;
};

int a[8][8] = {0, };
int a_copy[8][8] = {0, };
int ch[8][8] = {0, };
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int res = 0;
vector<p> v; // 바이러스 기록
vector<p> zero; // 빈칸 기록
vector<int> comb;
int N, M;

void bfs(){
    queue<p> q;
    for(int i=0; i<v.size(); i++){
        q.push({v[i].x, v[i].y});
    }

    while(!q.empty()){
        p tmp = q.front(); q.pop();

        for(int i=0; i<4; i++){
            int n_x = tmp.x + dx[i];
            int n_y = tmp.y + dy[i];

            if(n_x >=0 && n_x < N && n_y >= 0 && n_y < M && a_copy[n_x][n_y]==0){
                a_copy[n_x][n_y] = 2; // 바이러스 퍼지기
                q.push({n_x, n_y});
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> a[i][j];

            if(a[i][j] == 2) v.push_back({i, j}); // 바이러스 기록
            else if(a[i][j] == 0) zero.push_back({i, j}); // 빈칸 기록
        }
    }

    // 조합 돌릴 준비
    for(int i=0; i<3; i++) comb.push_back(1);
    for(int i=0; i<zero.size()-3; i++) comb.push_back(0);
    sort(comb.begin(), comb.end()); // 조합 돌리기 전 정렬시키기

    do{
        // 배열 복사
        copy(&a[0][0], &a[0][0]+64, &a_copy[0][0]); // 2차원 배열 복사

        // 벽 3개 세우기
        for(int i=0; i<comb.size(); i++){
            if(comb[i] == 1){
                a_copy[zero[i].x][zero[i].y] = 1; // 벽 3개 세우기
            }
        }

        // 바이러스 퍼뜨리기
        bfs();

        // 안전영역 구하기
        int safe_place = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(a_copy[i][j] == 0) safe_place++;
            }
        }
        // 답 갱신
        res = max(res, safe_place);
    } while (next_permutation(comb.begin(), comb.end()));
    // 조합 끝

    cout << res << endl;
    return 0;
}