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

char a[11][11];
int N, M, res = 987654321;

struct point{
    int x, y;
    int flag;
};

point red, blue, hole; // 빨간구슬, 파란구슬

// 방향좌표: 상, 하, 좌, 우
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int find_max(){
    int res = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(a[i][j] > res) res = a[i][j];
        }
    }

    return res;
}

void com(char c, int x, int y){
    if(x == hole.x && y == hole.y){
        if(c == 'R'){
            red.flag = 1;
            red.x = -1; red.y = -1;
            // cout << "Red : 1" << "\n";
        }
        else{
            blue.flag = 1;
            blue.x = -1; blue.y = -1;
            // cout << "Blue : 1" << "\n";
        }
    }
}


void move_up(){
    // move_up 방향 : (-1, 0)
    int tmp;
    if(red.x < blue.x){
        tmp = red.x;
        while(tmp-1 >= 1 && (a[tmp-1][red.y] == '.' || a[tmp-1][red.y] == 'O') && !(tmp-1 == blue.x && red.y == blue.y)){
            tmp--;
            com('R', tmp, red.y);
        }
        if(red.x != -1 && red.y != -1) red.x = tmp;

        tmp = blue.x;
        while(tmp-1 >= 1 && (a[tmp-1][blue.y] == '.' || a[tmp-1][blue.y] == 'O') && !(tmp-1 == red.x && blue.y == red.y)){
            tmp--;
            com('B', tmp, blue.y);
        }
        if(blue.x != -1 && blue.y != -1) blue.x = tmp;
    }
    else{
        tmp = blue.x;
        while(tmp-1 >= 1 && (a[tmp-1][blue.y] == '.' || a[tmp-1][blue.y] == 'O') && !(tmp-1 == red.x && blue.y == red.y)){
            tmp--;
            com('B', tmp, blue.y);
        }
        if(blue.x != -1 && blue.y != -1) blue.x = tmp;

        tmp = red.x;
        while(tmp-1 >= 1 && (a[tmp-1][red.y] == '.' || a[tmp-1][red.y] == 'O') && !(tmp-1 == blue.x && red.y == blue.y)){
            tmp--;
            com('R', tmp, red.y);
        }
        if(red.x != -1 && red.y != -1) red.x = tmp;
    }
}

void move_down(){
    // move_down 방향 : (1, 0)
    int tmp;
    if(red.x > blue.x){
        tmp = red.x;
        while(tmp+1 < N-1 && (a[tmp+1][red.y] == '.' || a[tmp+1][red.y] == 'O') && !(tmp+1 == blue.x && red.y == blue.y)){
            tmp++;
            com('R', tmp, red.y);
        }
        if(red.x != -1 && red.y != -1) red.x = tmp;

        tmp = blue.x;
        while(tmp+1 < N-1 && (a[tmp+1][blue.y] == '.' || a[tmp+1][blue.y] == 'O') && !(tmp+1 == red.x && blue.y == red.y)){
            tmp++;
            com('B', tmp, blue.y);
        }
        if(blue.x != -1 && blue.y != -1) blue.x = tmp;
    }
    else{
        tmp = blue.x;
        while(tmp+1 < N-1 && (a[tmp+1][blue.y] == '.' || a[tmp+1][blue.y] == 'O') && !(tmp+1 == red.x && blue.y == red.y)){
            tmp++;
            com('B', tmp, blue.y);
        }
        if(blue.x != -1 && blue.y != -1) blue.x = tmp;

        tmp = red.x;
        while(tmp+1 < N-1 && (a[tmp+1][red.y] == '.' || a[tmp+1][red.y] == 'O') && !(tmp+1 == blue.x && red.y == blue.y)){
            tmp++;
            com('R', tmp, red.y);
        }
        if(red.x != -1 && red.y != -1) red.x = tmp;
    }
}

void move_left(){
    // move_left 방향 : (0, -1)
    int tmp;
    if(red.y < blue.y){
        tmp = red.y;
        while(tmp-1 >= 1 && (a[red.x][tmp-1] == '.' || a[red.x][tmp-1] == 'O') && !(red.x == blue.x && tmp-1 == blue.y)){
            tmp--;
            com('R', red.x, tmp);
        }
        if(red.x != -1 && red.y != -1) red.y = tmp;

        tmp = blue.y;
        while(tmp-1 >= 1 && (a[blue.x][tmp-1] == '.' || a[blue.x][tmp-1] == 'O') && !(red.x == blue.x && red.y == tmp-1)){
            tmp--;
            com('B', blue.x, tmp);
        }
        if(blue.x != -1 && blue.y != -1) blue.y = tmp;
    }
    else{
        tmp = blue.y;
        while(tmp-1 >= 1 && (a[blue.x][tmp-1] == '.' || a[blue.x][tmp-1] == 'O') && !(red.x == blue.x && red.y == tmp-1)){
            tmp--;
            com('B', blue.x, tmp);
        }
        if(blue.x != -1 && blue.y != -1) blue.y = tmp;

        tmp = red.y;
        while(tmp-1 >= 1 && (a[red.x][tmp-1] == '.' || a[red.x][tmp-1] == 'O') && !(red.x == blue.x && tmp-1 == blue.y)){
            tmp--;
            com('R', red.x, tmp);
        }
        if(red.x != -1 && red.y != -1) red.y = tmp;
    }
}

void move_right(){
    // move_right 방향 : (0, 1)
    int tmp;
    if(red.y > blue.y){
        tmp = red.y;
        while(tmp+1 < M-1 && (a[red.x][tmp+1] == '.' || a[red.x][tmp+1] == 'O') && !(red.x == blue.x && tmp+1 == blue.y)){
            tmp++;
            com('R', red.x, tmp);
        }
        if(red.x != -1 && red.y != -1) red.y = tmp;

        tmp = blue.y;
        while(tmp+1 < M-1 && (a[blue.x][tmp+1] == '.' || a[blue.x][tmp+1] == 'O') && !(red.x == blue.x && red.y == tmp+1)){
            tmp++;
            com('B', blue.x, tmp);
        }
        if(blue.x != -1 && blue.y != -1) blue.y = tmp;
    }
    else{
        tmp = blue.y;
        while(tmp+1 < M-1 && (a[blue.x][tmp+1] == '.' || a[blue.x][tmp+1] == 'O') && !(red.x == blue.x && red.y == tmp+1)){
            tmp++;
            com('B', blue.x, tmp);
        }
        if(blue.x != -1 && blue.y != -1) blue.y = tmp;

        tmp = red.y;
        while(tmp+1 < M-1 && (a[red.x][tmp+1] == '.' || a[red.x][tmp+1] == 'O') && !(red.x == blue.x && tmp+1 == blue.y)){
            tmp++;
            com('R', red.x, tmp);
        }
        if(red.x != -1 && red.y != -1) red.y = tmp;
    }
}

void pri(){
    cout << "\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(red.x == i && red.y == j) cout << "R ";
            else if(blue.x == i && blue.y == j) cout << "B ";
            else cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void deb(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "--------------------\n";
    cout << "\n";
}

void dfs(int cnt){

    if(cnt >= 11) return; // 10회 이하
    if(blue.flag == 1) return;

    if(red.flag == 1){
        if(blue.flag == 0){
            res = min(res, cnt); // 갱신
            return;
        }
        else{
            // blue.flag == 1
            return;
        }
    }
    else{
        point red_tmp = red;
        point blue_tmp = blue;

        move_up();
        dfs(cnt + 1);
        swap(red, red_tmp); swap(blue, blue_tmp);

        red_tmp = red; blue_tmp = blue;
        move_down();
        dfs(cnt + 1);
        swap(red, red_tmp); swap(blue, blue_tmp);

        red_tmp = red; blue_tmp = blue;
        move_left();
        dfs(cnt + 1);
        swap(red, red_tmp); swap(blue, blue_tmp);

        red_tmp = red; blue_tmp = blue;
        move_right();
        dfs(cnt + 1);
        swap(red, red_tmp); swap(blue, blue_tmp);

    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    red.flag = 0; blue.flag = 0;

    for(int i=0; i<N; i++){
        string s;
        cin >> s;
        for(int j=0; j<s.size(); j++){
            a[i][j] = s[j];

            if(a[i][j] == 'R'){
                red.x = i; red.y = j;
                a[i][j] = '.';
            }
            if(a[i][j] == 'B'){
                blue.x = i; blue.y = j;
                a[i][j] = '.';
            }
            if(a[i][j] == 'O'){
                hole.x = i; hole.y = j;
            }
        }
    }


    dfs(0);

    if(res != 987654321) cout << res << endl;
    else cout << -1 << endl;

    return 0;
}