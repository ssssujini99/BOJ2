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

int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    char c[9][9]; string s; int ch[9][9] = {0, };
    queue<p> wall;
    deque<p> man;

    for(int i=0; i<8; i++){
        cin >> s;
        for(int j=0; j<s.size(); j++){
            c[i+1][j+1] = s[j];

            if(c[i+1][j+1] == '#'){
                wall.push({i+1, j+1});
            }
        }
    }
    man.push_back({8, 1});
    c[8][1] = 'M';

    while(!man.empty()){
        if(wall.empty()){
            cout << 1 << endl;
            exit(0);
        }

        queue<p> man_tmp;
        int size = man.size();

        for(int i=0; i<size; i++){
            p tmp = man.front(); man.pop_front();
            if(c[tmp.x][tmp.y] == '#'){
                continue;
            }
            man.push_back(tmp);

            for(int i=0; i<8; i++){
                int next_x = tmp.x + dx[i];
                int next_y = tmp.y + dy[i];

                if(next_x == 1 && next_y == 8 && c[next_x][next_y] == '.'){
                    cout << 1 << endl;
                    exit(0);
                }

                if(next_x >= 1 && next_x <= 8 && next_y >= 1 && next_y <= 8 && c[next_x][next_y]=='.'){
                    c[next_x][next_y] = 'M';
                    man_tmp.push({next_x, next_y});
                }
            }
        }

        while(!man_tmp.empty()){
            man.push_back(man_tmp.front()); man_tmp.pop();
        }

        queue<p> wall_tmp;
        while(!wall.empty()){
            p tmp = wall.front(); wall.pop();
            if(tmp.x + 1 <= 8){
                wall_tmp.push({tmp.x+1, tmp.y});
            }
            c[tmp.x][tmp.y] = '.';
        }
        while(!wall_tmp.empty()){
            p tmp = wall_tmp.front(); wall_tmp.pop();
            c[tmp.x][tmp.y] = '#';
            wall.push(tmp);
        }
    }

    cout << 0 << endl;
    return 0;
}