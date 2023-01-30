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
#include <climits>
using namespace std;

typedef long long ll;

unordered_map<int, int> um;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, d, k, c, ans, tmp; cin >> N >> d >> k >> c;
    vector<int> v;

    for(int i=0; i<N; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }

    for(int i=0; i<k-1; i++) {
        v.push_back(v[i]);
    }
    // 입력 끝

    // 시작
    for(int i=0; i<k; i++) {
        um[v[i]]++;
    }
    if(um.find(c) == um.end()) ans = um.size() + 1;
    else ans = um.size();


    for(int i=k; i<N+k-1; i++) {
        um[v[i-k]]--;
        if(um[v[i-k]] == 0) um.erase(v[i-k]);
        um[v[i]]++;

        int ansT;
        if(um.find(c) == um.end()) ansT = um.size() + 1;
        else ansT = um.size();

        ans = max(ans, ansT);
    }

    cout << ans << endl;
    return 0;
}