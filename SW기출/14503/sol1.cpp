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
using namespace std;

int a[51][51] = {0, }; // 0: 빈칸, 1: 벽, 2: 청소완료

int dx[4] = {-1, 0, 1, 0}; // 북, 동, 남, 서
int dy[4] = {0, 1, 0, -1};

struct point{
    int x, y, dir; // 좌표, 방향
};

int N, M, res = 0;
point robot;

void clean(){
    // 현재 방향을 기준으로 왼쪽 방향부터 차례로 탐색 진행

    while(1){
        int flag = 0;

        for(int i=0; i<4; i++){
            int next_d = robot.dir - 1;
            if(next_d == -1) next_d = 3;

            int n_x = robot.x + dx[next_d];
            int n_y = robot.y + dy[next_d];

            if(a[n_x][n_y] == 0){
                robot.dir = next_d; // 방향바꿈
                robot.x = n_x; robot.y = n_y; // 로봇 정보 갱신
                res++; a[n_x][n_y] = 2; // 청소 정보 갱신
                flag = 1;
                break;
            }
            else robot.dir = next_d; // 청소할 공간이 없다면 -> 그 방향으로 회전만
        }

        // 현재 좌표를 기준으로 네 방향 모두 만족 X
        if(flag == 0){
            // 후진 좌표 검색
            int back_d = (robot.dir + 2) % 4; // 뒷 방향
            int n_x = robot.x + dx[back_d];
            int n_y = robot.y + dy[back_d];

            if(a[n_x][n_y] != 1){ // 후진했을때 벽이 아닌 경우 -> 방향은 그대로 & 후진만
                robot.x = n_x;
                robot.y = n_y;
            }
            else break; // 벽인 경우 -> 작동 멈춤
        }
    } // while문 종료

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    int x, y, dir; cin >> x >> y >> dir;
    robot.x = x; robot.y = y; robot.dir = dir;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> a[i][j];
        }
    }

    a[robot.x][robot.y] = 2;
    res++;

    clean();

    cout << res << endl;
    return 0;
}