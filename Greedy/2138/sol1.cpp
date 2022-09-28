#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int N, res1 = 0, res2 = 0;
string s1, s2;
bool a[100001] = {0, };
bool b[100001] = {0, };
bool c[100001] = {0, };

void toggle1(int x){
    a[x] = !a[x];
    a[x+1] = !a[x+1];
    a[x+2] = !a[x+2];
}

bool compare1(){
    for(int i=0; i<N; i++){
        if(a[i] != c[i]){
            return 0;
        }
    }
    return 1;
}

void toggle2(int x){
    b[x] = !b[x];
    b[x+1] = !b[x+1];
    b[x+2] = !b[x+2];
}

bool compare2(){
    for(int i=0; i<N; i++){
        if(b[i] != c[i]){
            return 0;
        }
    }
    return 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> s1 >> s2;

    if(s1 == s2){
        cout << 0 << endl;
        exit(0);
    }

    for(int i=0; i<N; i++){
        if(s1[i] == '0') a[i] = 0, b[i] = 0;
        else a[i] = 1, b[i] = 1;
    }
    for(int i=0; i<N; i++){
        if(s2[i] == '0') c[i] = 0;
        else c[i] = 1;
    }

    // 0번 전구 안누르고 시작
    res2 = 0;
    int flag2 = 0;

    if(compare2() == 1){
        cout << 0 << endl;
        exit(0);
    }

    for(int i=0; i<N-2; i++){
        if(b[i] != c[i]){
            toggle2(i);
            res2++;
            if(compare2() == 1){
                flag2 = 1;
                break;
            }
        }
    }

    if(b[N-2] != c[N-2]){
        b[N-2] = !b[N-2];
        b[N-1] = !b[N-1];
        res2++;
    }
    if(compare2() == 1) flag2 = 1;


    // 0번 전구 누르고 시작
    int flag1 = 0;
    res1++;
    a[0] = !a[0]; a[1] = !a[1];

    if(compare1() == 1){
        cout << 1 << endl;
        exit(0);
    }

    for(int i=0; i<N-2; i++){
        if(a[i] != c[i]){
            toggle1(i);
            res1++;
            if(compare1() == 1){
                flag1 = 1;
                break;
            }
        }
    }

    if(a[N-2] != b[N-2]){
        a[N-2] = !a[N-2];
        a[N-1] = !a[N-1];
        res1++;
    }
    if(compare1() == 1) flag1 = 1;


    if(flag1 == 1 && flag2 == 1){
        cout << min(res1, res2) << endl;
    }
    else if(flag1 == 1){
        cout << res1 << endl;
    }
    else if(flag2 == 1){
        cout << res2 << endl;
    }
    else{
        cout << "-1" << endl;
    }

    return 0;
}