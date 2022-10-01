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

    for(int i=0; i<(1<<N); i++){
        // a배열에 aa 배열 복사하기
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                a[i][j] = aa[i][j];
            }
        }

        // N개의 행들에 대해 정해주기
        for(int j=0; j<N; j++){
            if(i & (1<<j)){
                toggle(1, j); // j행 toggle 시키기
            }
        }

        // 그 다음 열들 고려해주기
        int tmp = 0;
        for(int j=0; j<N; j++){
            // j열에 대해서
            tmp = 0;
            for(int k=0; k<N; k++){
                tmp += a[k][j];
            }
            if(tmp > N/2) toggle(0, j); // j열 toggle 시키기
        }

        // 갱신시키기
        res = min(res, check());
    }

    cout << res << endl;
    return 0;
}

