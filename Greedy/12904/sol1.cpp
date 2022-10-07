#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <set>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S, T; cin >> S >> T;

    while(T.size() != S.size()){
        if(T[T.size()-1] == 'A'){
            T = T.substr(0, T.size()-1); // A 빼기
        }
        else{
            T = T.substr(0, T.size()-1); // B 빼고
            reverse(T.begin(), T.end()); // 뒤집기
        }
    }

    if(S == T) cout << 1 << endl;
    else cout << 0 << endl;

    return 0;
}