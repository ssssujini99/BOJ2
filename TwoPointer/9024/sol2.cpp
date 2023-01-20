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

    int t; cin >> t;
    while(t--) {
        int N; ll K; cin >> N >> K;
        vector<ll> v; ll tmp;

        for(int i=0; i<N; i++) {
            cin >> tmp;
            v.push_back(tmp);
        }
        sort(v.begin(), v.end());

        int l = 0, r = N-1;
        ll ans = 200000000; ll cnt = 0;

        while(l < r) {
            ll res = v[l] + v[r];
            // 갱신
            if(abs(K-res) < abs(ans-K)) {
                ans = res;
                cnt = 1;
            }
            else if(abs(K-res) == abs(ans-K)) {
                cnt++;
            }
            else {
            }

            // 포인터 이동
            if (res <= K) l++;
            else r--;
        }

        cout << cnt << "\n";

    }

    return 0;
}