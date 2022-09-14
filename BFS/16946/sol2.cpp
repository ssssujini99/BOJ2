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

int N, M;
int map[1001][1001] = {0, };
int map2[1001][1001] = {0, };
int ch[1001][1001] = {0, };

unordered_map<int, int> group_um;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int bfs(int x, int y, int group){
    queue<pair<int, int> > q;
    ch[x][y] = group;
    q.push({x, y});
    int res = 1;

    while(!q.empty()){
        int ex_x = q.front().first; int ex_y = q.front().second; q.pop();

        for(int i=0; i<4; i++){
            int next_x = ex_x + dx[i];
            int next_y = ex_y + dy[i];

            if(next_x >=0 && next_x < N && next_y >= 0 && next_y < M && map[next_x][next_y] == 0 && ch[next_x][next_y]==0){
                ch[next_x][next_y] = group;
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

    // grouping 해주기
    int group = 1; int cnt;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map[i][j] == 0 && ch[i][j] == 0){
                cnt = bfs(i, j, group);
                group_um[group] = cnt;
                group++;
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map[i][j] == 1){ // 벽인 경우에 대해서만
                set<int> s;
                // i, j를 기준으로 상, 하, 좌, 우 그룹 검토
                for(int k=0; k<4; k++){
                    int xx = i + dx[k];
                    int yy = j + dy[k];

                    if(xx >= 0 && xx < N && yy >=0 && yy < M && ch[xx][yy] >= 1){
                        s.insert(ch[xx][yy]);
                    }
                }

                set<int>::iterator it; int sum = 0;
                for(it = s.begin(); it != s.end(); it++){
                    sum += group_um[*it];
                }
                cout << (sum + 1)%10;
            }
            else cout << 0;
        }
        cout << "\n";
    }

    return 0;
}