#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <map>
#include <sstream>
using namespace std;

int cp[21][21] = {0, }; // 좌표평면 배열
int dice[4][3] = {0, }; // 주사위 배열

// 동서남북 좌표
int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, 1, -1, 0, 0};

void movingDice(int dir) { // 해당 방향에 맞게 주사위 정보 갱신시키는 함수
    int tmp[4][3] = {0, };
    if (dir == 1) { // 동
        tmp[0][1] = dice[0][1]; tmp[1][0] = dice[1][1]; tmp[1][1] = dice[1][2];
        tmp[1][2] = dice[3][1]; tmp[2][1] = dice[2][1]; tmp[3][1] = dice[1][0];
    }
    else if (dir == 2) { // 서
        tmp[0][1] = dice[0][1]; tmp[1][0] = dice[3][1]; tmp[1][1] = dice[1][0];
        tmp[1][2] = dice[1][1]; tmp[2][1] = dice[2][1]; tmp[3][1] = dice[1][2];
    }
    else if (dir == 3) { // 남
        tmp[0][1] = dice[1][1]; tmp[1][0] = dice[1][0]; tmp[1][1] = dice[2][1];
        tmp[1][2] = dice[1][2]; tmp[2][1] = dice[3][1]; tmp[3][1] = dice[0][1];
    }
    else { // 북
        tmp[0][1] = dice[3][1]; tmp[1][0] = dice[1][0]; tmp[1][1] = dice[0][1];
        tmp[1][2] = dice[1][2]; tmp[2][1] = dice[1][1]; tmp[3][1] = dice[2][1];
    }

    copy(&tmp[0][0], &tmp[0][0] + 4*3, &dice[0][0]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, x, y, K, tmp; // x, y: 현재 주사위 위치
    vector<int> order; // 주사위 이동 방향 순서

    cin >> N >> M >> x >> y >> K;

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> cp[i][j];
        }
    }
    for(int i=0; i<K; i++) {
        cin >> tmp;
        order.push_back(tmp);
    }
    // 입력끝

    int cnt = 0;
    while(cnt < K) {
        int dir = order[cnt];
        int nx = x + dx[dir]; int ny = y + dy[dir]; // 주사위가 이동할 방향

        if (! (nx >= 0 && nx < N && ny >= 0 && ny < M)) { // 바깥이동시 무시
            cnt++;
            continue;
        }
        // 좌표 범위는 만족
        x = nx; y = ny; // 현재 주사위 위치 갱신시키기
        movingDice(dir); // 이제 해당 방향에 맞게 움직인 주사위 정보 갱신시키기

        if (cp[x][y] == 0) { // 이동할 칸에 쓰인 수가 0이면
            cp[x][y] = dice[1][1]; // 주사위 바닥면에 쓰인 수가 칸에 복사
        }
        else { // 이동할 칸에 쓰인 수가 0이 아니면
            dice[1][1] = cp[x][y]; // 칸에 쓰여있는 수가 주사위 바닥면으로 복사
            cp[x][y] = 0; // 칸에 쓰인 수는 0이 된다
        }

        // 주사위 상단에 쓰여있는 수 출력하기
        cout << dice[3][1] << "\n";
        cnt++;
    }

    return 0;
}