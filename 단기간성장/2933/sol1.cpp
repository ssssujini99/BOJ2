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

int R, C, N;
char a[101][101];
int cnt[101] = {0, }; // 던지는 높이

// 방향: (아래, 왼, 오, 위) 순서로
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, -1, 1, 0};

int grouping[101][101] = {0, };
int groupingCnt = 0;

struct point{
    int x, y;
};

point throw_left(int height){
    point p = {-1, -1};

    for(int i=0; i<C; i++){
        if(a[R-height][i] == 'x'){
            a[R-height][i] = '.'; // 미네랄 파괴
            p.x = R-height; p.y = i;
            break;
        }
    }

    return p;
}

point throw_right(int height){
    point p = {-1, -1};

    for(int i=C-1; i>=0; i--){
        if(a[R-height][i] == 'x'){
            a[R-height][i] = '.'; // 미네랄 파괴
            p.x = R-height; p.y = i;
            break;
        }
    }

    return p;
}

void bfs(int x, int y){
    queue<pair<point, int> > q; // {좌표, groupingCnt}
    grouping[x][y] = groupingCnt;
    point p = {x, y};
    q.push(make_pair(p, groupingCnt));

    while(!q.empty()){
        p = q.front().first; int n = q.front().second; q.pop();
        int xx = p.x; int yy = p.y;

        for(int i=0; i<4; i++){
            int nx = xx + dx[i]; int ny = yy + dy[i];

            if(nx >= 0 && nx < R && ny >= 0 && ny < C && a[nx][ny] == 'x' && grouping[nx][ny] == 0){
                grouping[nx][ny] = groupingCnt;
                point np = {nx, ny};
                q.push(make_pair(np, groupingCnt));
            }
        }
    }

}

void gc(){
    memset(grouping, 0, sizeof(grouping));
    groupingCnt = 1;

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(a[i][j] == 'x' && grouping[i][j] == 0){
                bfs(i, j);
                groupingCnt++;
            }
        }
    }

    groupingCnt -= 1;

}

void deb(){
    cout << "----grouping 배열 출력-----\n";

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << grouping[i][j];
        }
        cout << "\n";
    }

    cout << "\n";
    cout << "groupingCnt: " << groupingCnt << "\n";
}

void debb(){
    // cout << "----배열 a 출력----\n";

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << a[i][j];
        }
        cout << "\n";
    }
}

void falling(int idx){
    // grouping 된 number가 idx인 클러스터 아래로 떨어뜨리기

    queue<pair<point, int> > q;

    int fN = 0; // 떨어뜨릴 수 있는 최대 높이
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(grouping[i][j] == idx){
                point p = {i, j};
                q.push(make_pair(p, 0));
            }
        }
    } // queue에 넣기

    // bfs 로 떨어뜨릴 수 있는 최대 높이 계산
    int count = q.size();

    point p; int h = 0;

    while(!q.empty()){
        p = q.front().first; h = q.front().second; q.pop();
        int x = p.x; int y = p.y;

        if((x+1 <= R && a[x+1][y] == '.') || (a[x+1][y] == 'x' && grouping[x+1][y] == idx)){
            p = {x + 1, y};
            q.push(make_pair(p, h+1));
        }
        else{
            break;
        }
    }
    // cout << "idx: " << idx << ", 떨어뜨릴 수 있는 높이: " << h << "\n";

    // 클러스터 떨어뜨리기 -> 맨 밑에칸부터 먼저 떨어뜨리기
    if(h > 0){
        for(int i=R-1; i>=0; i--){
            for(int j=C-1; j>=0; j--){
                if(grouping[i][j] == idx){
                    a[i+h][j] = 'x';
                    a[i][j] = '.';
                }
            }
        }
    }

}

void logicFunc(){
    // 1. 던짐(좌 또는 우) + 미네랄 제거
    // 3. 클러스터 그룹핑
    // 4. 그룹핑 된 클러스터 모음들 밑으로 떨어뜨리기
    // 5. 클러스터 재그룹핑

    for(int i=0; i<N; i++){
        // cout << "------------------------횟수 : " << i << "번째--------------------\n";
        // debb();
        // cout << "던지기\n";

        if(i % 2 == 0) throw_left(cnt[i]);
        else throw_right(cnt[i]);

        // debb();
        // cout << "---grouping---\n";

        gc();

        // deb();
        // debb();

        // cout << "-------떨어뜨리기-------\n";
        for(int j=groupingCnt; j>=1; j--){
            falling(j);
            // debb();
        }

        // debb();
        gc();
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
        }
    }

    cin >> N;
    for(int i=0; i<N; i++) cin >> cnt[i];

    logicFunc();
    debb(); // 정답출력

    return 0;
}