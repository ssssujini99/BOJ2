#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <set>
using namespace std;

// 벽 3개 고르기 -> 0 중에서 3개 고르기 (조합)
// 해당 벽을 세운 것을 기준으로 BFS 돌리기
// 0의 개수 세기

struct p{
    int x, y;
};

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int a[8][8] = {0, }; // original
int aa[8][8] = {0, }; // copy
vector<p> virus; // virus 좌표들
int N, M;

void bfs(){
    queue<p> q;

    for(int i=0; i<virus.size(); i++){
        q.push(virus[i]);
    }

    while(!q.empty()){
        p point = q.front(); q.pop();
        int x = point.x; int y = point.y;

        for(int i=0; i<4; i++){
            int n_x = x + dx[i];
            int n_y = y + dy[i];

            if(n_x >= 0 && n_x < N && n_y >= 0 && n_y < M && aa[n_x][n_y] == 0){
                // 범위 만족 && 해당 aa 좌표가 빈 칸 일때
                aa[n_x][n_y] = 2; // 바이러스 퍼지는 거 체크
                q.push({n_x, n_y}); // 큐에 넣기
            }
        }
    }
}

int count_zero(){
    int cnt = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(aa[i][j] == 0) cnt++;
        }
    }

    return cnt;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<p> zero; vector<int> tmp; int res = 0;
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> a[i][j];

            if(a[i][j] == 0){
                zero.push_back({i, j});
            }
            else if(a[i][j] == 2){
                virus.push_back({i, j});
            }
            else{

            }
        }
    }

    for(int i=0; i<3; i++) tmp.push_back(1);
    for(int i=0; i<zero.size()-3; i++) tmp.push_back(0);

    sort(tmp.begin(), tmp.end());

    // 조합 시작
    do{
        copy(&a[0][0], &a[0][0]+64, &aa[0][0]); // aa에 a 복사해주기

        for(int i=0; i<tmp.size(); i++){
            if(tmp[i] == 1){
                // 해당 i 번째를 택한거임
                aa[zero[i].x][zero[i].y] = 1; // 벽으로 만들어주기
            }
        }

        // BFS 수행
        bfs();
        // 0 계산 (안전 영역 크기 계산) + res 갱신
        res = max(res, count_zero());
    } while (next_permutation(tmp.begin(), tmp.end()));
    // 조합 끝

    cout << res << endl;
    return 0;
}