#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

struct s{
    int x, y;
    int t; // time
};

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int R, C; cin >> R >> C;
    string str; char c[51][51]; int ch[51][51] = {0, };
    queue<s> water; // 물 이동 위치
    queue<s> hedgehog; // 고슴도치 이동 위치
    s start; s end;


    for(int i=0; i<R; i++){
        cin >> str;
        for(int j=0; j<str.size(); j++){
            c[i][j] = str[j];

            if(c[i][j] == '*'){
                ch[i][j] = 1;
                water.push({i, j, 0});
            }
            if(c[i][j] == 'S'){ // 고슴도치 위치
                hedgehog.push({i, j, 0});
            }
            if(c[i][j] == 'D'){ // 비버의 소굴 -> 최종 이동해야 할 위치
                end.x = i, end.y = j, end.t = 0;
            }
        }
    } // 입력 끝

    int time = 0;
    while(!hedgehog.empty()){
        while(water.size() > 0 && water.front().t == time){
            int x = water.front().x, y = water.front().y; water.pop();

            for(int i=0; i<4; i++){
                int next_x = x + dx[i], next_y = y + dy[i];

                if(next_x >= 0 && next_x < R &&
                   next_y >= 0 && next_y < C &&
                   ch[next_x][next_y] == 0 &&
                   c[next_x][next_y] != 'D' &&
                   c[next_x][next_y] != 'X'){
                       c[next_x][next_y] = '*'; // 물로 바꾸기
                       ch[next_x][next_y] = 1;
                       water.push({next_x, next_y, time+1});
                }
            }
        }

        while(hedgehog.size() > 0 && hedgehog.front().t == time){
            int x = hedgehog.front().x, y = hedgehog.front().y; hedgehog.pop();

            if(x == end.x && y == end.y){
                cout << time << endl;
                exit(0);
            }

            for(int i=0; i<4; i++){
                int next_x = x + dx[i], next_y = y + dy[i];

                if(next_x >= 0 && next_x < R &&
                   next_y >= 0 && next_y < C &&
                   (c[next_x][next_y] == '.' || c[next_x][next_y] == 'D')){
                       c[next_x][next_y] = 'S';
                       hedgehog.push({next_x, next_y, time+1});
                }
            }
        }

        time++;
    }

    cout << "KAKTUS\n";
    return 0;
}