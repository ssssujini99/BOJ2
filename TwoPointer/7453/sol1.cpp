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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    ll a[4001][4];
    vector<ll> s1; vector<ll> s2;

    for(int i=0; i<N; i++) {
        for(int j=0; j<4; j++) {
            cin >> a[i][j];
        }
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            s1.push_back(a[i][0] + a[j][1]);
            s2.push_back(a[i][2] + a[j][3]);
        }
    }

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    ll ans = 0;
    for(int i=0; i<s1.size(); i++) {
        ans += (upper_bound(s2.begin(), s2.end(), -s1[i]) - lower_bound(s2.begin(), s2.end(), -s1[i]));
    }

    cout << ans << endl;
    return 0;
}