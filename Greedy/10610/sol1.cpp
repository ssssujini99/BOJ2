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

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int cnt[10] = {0, };
    string s; cin >> s;
    int sum = 0;

    for(int i=0; i<s.size(); i++){
        cnt[s[i]-'0'] ++;
        sum += s[i]-'0';
    }

    if(cnt[0] == 0 || sum%3 != 0){
        cout << -1 << endl;
        exit(0);
    }

    string tmp = "";
    for(int i=9; i>=0; i--){
        while(cnt[i] > 0){
            tmp += i + '0';
            cnt[i]--;
        }
    }

    cout << tmp << endl;
    return 0;
}