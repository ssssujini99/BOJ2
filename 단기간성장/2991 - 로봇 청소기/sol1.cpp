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

int N, M, k;
int a[21][21] = {0, };
bool visited[21][21][1<<11];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct point{
    int x, y;
};

struct st{
    int x, y; // 좌표
    int b; // 비트
    int t; // 시간
};

point robot;

void bfs(int r_x, int r_y) {

    queue<st> q;
    st stt= {r_x, r_y, 0, 0};
    q.push(stt);

    while(!q.empty()){
        int x = q.front().x; int y = q.front().y;
        int b = q.front().b; int t = q.front().t;
        q.pop();


        if(b == ((pow(2, k)) - 1)){
            cout << t << "\n";
            return;
        }

        for(int i=0; i<4; i++){
            int xx = x + dx[i]; int yy = y + dy[i];
            int tt = t + 1; int bb = b;

            if(xx < 0 || xx >= N || yy < 0 || yy >= M || a[xx][yy] < 0) continue;

            // 먼지인 경우
            if(a[xx][yy] > 0) bb |= 1<<(a[xx][yy] - 1);

            if(visited[xx][yy][bb] == 1) continue; // 이미 이 상태로 방문한 경우가 있다면 -> continue;

            visited[xx][yy][bb] = 1; // 이 형태로 방문했음을 출력
            q.push({xx, yy, bb, tt});
        }
    }

    cout << -1 << "\n";
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(1){
        cin >> M >> N;
        if(N == 0 && M == 0) break;

        memset(a, 0, sizeof(a));
        memset(visited, 0, sizeof(visited));

        k = 0;

        for(int i=0; i<N; i++){
            string s; cin >> s;
            for(int j=0; j<s.size(); j++){

                if(s[j] == 'x'){ // 벽인 경우 -> -1
                    a[i][j] = -1;
                }
                else if(s[j] == '*'){ // 먼지인 경우 -> 1 ~ 10 으로 양수 매핑
                    a[i][j] = ++k;
                }
                else if(s[j] == 'o'){// 로봇 청소기인 경우
                    a[i][j] = 0;
                    robot.x = i; robot.y = j;
                }
                else{ // 빈칸인 경우 -> 0
                    a[i][j] = 0;
                }
            }
        } // 입력 끝

        // 로봇 넣고 시작
        bfs(robot.x, robot.y);
    }

    return 0;
}