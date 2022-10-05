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

    string s; cin >> s;
    int sum = 0;

    for(int i=0; i<s.size(); i++){
        sum += s[i]-'0';
    }

    sort(s.begin(), s.end());

    if(s[0] != '0' || sum%3 != 0){
        cout << -1 << endl;
        exit(0);
    }

    reverse(s.begin(), s.end());
    cout << s << endl;
    return 0;
}