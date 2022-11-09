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

struct point{
    int x, y;
};

int R, C, day = 0;
char a[1501][1501];
int ch[1501][1501] = {0, };
queue<point> waterQ;
queue<point> swanQ;
vector<point> swan;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void melting(){
    int cnt = waterQ.size();

    while(cnt--){
        point p = waterQ.front(); waterQ.pop();
        int x = p.x; int y = p.y;

        int nx, ny;
        for(int i=0; i<4; i++){
            nx = x + dx[i]; ny = y + dy[i];

            if(nx >= 0 && nx < R && ny >= 0 && ny < C && a[nx][ny] == 'X'){
                a[nx][ny] = '.'; // 녹이기
                waterQ.push({nx, ny});
            }
        }
    }
}

void movingSwan(){

    queue<point> nextQ;

    while(!swanQ.empty()){
        int x = swanQ.front().x; int y = swanQ.front().y; swanQ.pop();

        if(x == swan[1].x && y == swan[1].y){
            cout << day;
            exit(0);
        }

        for(int i=0; i<4; i++){
            int nx = x + dx[i]; int ny = y + dy[i];

            if(nx >= 0 && nx < R && ny >= 0 && ny < C && ch[nx][ny] == 0){
                ch[nx][ny] = 1;
                if(a[nx][ny] == '.'){
                    swanQ.push({nx, ny});
                }
                else{
                    nextQ.push({nx, ny});
                }
            }
        }
    }

    swap(swanQ, nextQ);

}

void deb(){
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void logic(){

    for(int i=0; ; i++){
        movingSwan();
        day++;
        melting();
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C;
    string s;

    for(int i=0; i<R; i++){
        cin >> s;
        for(int j=0; j<s.size(); j++){
            a[i][j] = s[j];

            if(a[i][j] == '.') waterQ.push({i, j});
            if(a[i][j] == 'L'){ // 백조위치
                swan.push_back({i, j});
                waterQ.push({i, j});
                a[i][j] =  '.';
            }
        }
    }

    ch[swan[0].x][swan[0].y] = 1;
    swanQ.push({swan[0].x, swan[0].y});

    logic();
    return 0;
}