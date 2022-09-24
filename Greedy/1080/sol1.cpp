#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int N, M, res = 0;
string s;
bool a[51][51] = {0, };
bool b[51][51] = {0, };

void change(int x, int y){
    for(int i=x; i<x+3; i++){
        for(int j=y; j<y+3; j++){
            a[i][j] = !a[i][j]; // toggle
        }
    }
}

bool compare(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(a[i][j] != b[i][j]) return 0;
        }
    }

    return 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for(int i=0; i<N; i++){
        cin >> s;
        for(int j=0; j<s.size(); j++){
            if(s[j] == '0') a[i][j] = 0;
            else a[i][j] = 1;
        }
    }

    for(int i=0; i<N; i++){
        cin >> s;
        for(int j=0; j<s.size(); j++){
            if(s[j] == '0') b[i][j] = 0;
            else b[i][j] = 1;
        }
    }

    if(compare() == 1){
        cout << 0 << endl;
        exit(0);
    }

    if(N < 3 || M < 3){
        cout << -1 << endl;
        exit(0);
    }

    for(int i=0; i<N-2; i++){
        for(int j=0; j<M-2; j++){
            if(a[i][j] != b[i][j]){
                change(i, j);
                res++;
                if(compare() == 1){
                    cout << res << endl;
                    exit(0);
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}