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

int N; int col[16] = {0, };
int res = 0;
int dx[4] = {-1, 1, -1, 1};
int dy[4] = {-1, 1, 1, -1};

bool promising(int col_idx, int col_num){
    // 1. 행 체크 -> 행 기준으로 선택하므로 없어도 됨

    // 2. 열 체크
    for(int i=0; i<N; i++){
        if(col[i] == col_num) return false;
    }

    // 3. 대각선들 체크 (기울기 != -1 && 기울기 != 1)
    for(int i=col_idx - 1; i >= 0; i--){
        if(((col_idx - i) == (col_num - col[i])) || ((col_idx - i) == -(col_num - col[i]))){
            return false;
        }
    }

    // 1~3 통과한 경우
    return true;
}

void backtracking(int cnt){
    // 탈출 조건
    if(cnt == N){
        res++;
        return;
    }

    // 유망함수
    for(int i=0; i<N; i++){
        if(promising(cnt, i)){ // 유망하다면
            col[cnt] = i; // 상태 변화
            backtracking(cnt+1); // 재귀 호출
            col[cnt] = -1; // 상태 복귀
        }
        // non-promising인 경우에는 제외
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;

    for(int i=0; i<16; i++) col[i] = -1; // 초기화

    backtracking(0);

    // 결과 출력
    cout << res << "\n";

    return 0;
}