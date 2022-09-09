#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <sstream>
#include <climits>
#include <cstdio>

#define INF 999999999
using namespace std;

int N;
char c[100][100];
int ch[100][100] = {0, };

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void BFS1(int x, int y){
    queue<pair<int, int> > q;
    ch[x][y] = 1; q.push({x, y});

    while(!q.empty()){
        int x = q.front().first; int y = q.front().second;
        q.pop();

        for(int i=0; i<4; i++){
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if(next_x >=0 && next_y < N
                && next_y >=0 && next_y < N
                && c[x][y] == c[next_x][next_y]
                && ch[next_x][next_y] == 0){
                    ch[next_x][next_y] = 1;
                    q.push({next_x, next_y});
                }
        }
    }

}

int check(int x, int y, int next_x, int next_y){
    char c1 = c[x][y];
    char c2 = c[next_x][next_y];

    if((c1 == 'R' && (c2 == 'R' || c2 == 'G')) ||
       (c1 == 'G' && (c2 == 'R' || c2 == 'G')) ||
       (c1 == 'B' && c2 == 'B'))
       return 1;
    else return 0;
}

void BFS2(int x, int y){
    queue<pair<int, int> > q;
    ch[x][y] = 1; q.push({x, y});

    while(!q.empty()){
        int x = q.front().first; int y = q.front().second;
        q.pop();

        for(int i=0; i<4; i++){
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if(next_x >=0 && next_y < N
                && next_y >=0 && next_y < N
                && check(x, y, next_x, next_y) == 1
                && ch[next_x][next_y] == 0){
                    ch[next_x][next_y] = 1;
                    q.push({next_x, next_y});
                }
        }
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    string s;
    for(int i=0; i<N; i++){
        cin >> s;
        for(int j=0; j<s.size(); j++){
            c[i][j] = s[j];
        }
    }

    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(ch[i][j]==0){
                BFS1(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << " ";

    memset(ch, 0, sizeof(ch)); // ch 배열 0으로 초기화

    cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(ch[i][j]==0){
                BFS2(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}