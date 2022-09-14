#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int N, M;
int map[1001][1001] = {0, };
int ch[1001][1001] = {0, };

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int bfs(int x, int y){
    queue<pair<int, int> > q;
    ch[x][y] = 1;
    q.push({x, y});
    int res = 1;

    while(!q.empty()){
        int ex_x = q.front().first; int ex_y = q.front().second; q.pop();

        for(int i=0; i<4; i++){
            int next_x = ex_x + dx[i];
            int next_y = ex_y + dy[i];

            if(next_x >=0 && next_x < N && next_y >= 0 && next_y < M && map[next_x][next_y] == 0 && ch[next_x][next_y]==0){
                ch[next_x][next_y] = 1;
                q.push({next_x, next_y});
                res++;
            }
        }
    }

    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    string input;
    for(int i=0; i<N; i++){
        cin >> input;
        for(int j=0; j<M; j++){
            map[i][j] = input[j] - '0';
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map[i][j] == 1){
                memset(ch, 0, sizeof(ch)); // ch 배열 초기화
                cout << bfs(i, j);
            }
            else cout << 0;
        }
        cout << "\n";
    }

    return 0;
}