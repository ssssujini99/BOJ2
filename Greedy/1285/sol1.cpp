#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int N, res = 400;
bool aa[21][21] = {0, };
bool a[21][21] = {0, };
int ch[21] = {0, };

int check(){
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(a[i][j] == 1) cnt++;
        }
    }
    return cnt;
}

void toggle(int dir, int idx){
    if(dir == 1){ // 행 toggle
        for(int i=0; i<N; i++){
            a[idx][i] = !a[idx][i];
        }
    }
    else{
        // 열 toggle
        for(int i=0; i<N; i++){
            a[i][idx] = !a[i][idx];
        }
    }
}

void DFS(int idx){
    if(idx == N){
        // aa배열에 a 배열 복사하기
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                a[i][j] = aa[i][j];
            }
        }

        // ch 배열에 담긴 정보로 행들 toggle (가로)
        for(int i=0; i<N; i++){
            if(ch[i] == 1) toggle(1, i);
        }

        // 정해진 행들 기준으로 열들 계산 (세로)
        for(int i=0; i<N; i++){
            int tmp = 0;
            for(int j=0; j<N; j++) tmp += a[j][i];

            if(tmp > N/2) toggle(0, i);
        }

        // 갱신
        res = min(res, check());
    }
    else{
        ch[idx] = 1; // idx행 toggle O
        DFS(idx+1);

        ch[idx] = 0; // idx행 toggle X
        DFS(idx+1);
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
            if(s[j] == 'H') aa[i][j] = 1; // 위
            else aa[i][j] = 0; // 아래
        }
    }

    DFS(0);

    cout << res << endl;
    return 0;
}


