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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T, N; ll tmp;
    priority_queue<ll, vector<ll>, greater<> > pq;

    cin >> T;
    while(T--) {
        cin >> N;

        for(int i=0; i<N; i++) {
            cin >> tmp;
            pq.push(tmp);
        }

        ll t1, t2, ans = 0;
        while(pq.size() != 1) {
            t1 = pq.top(); pq.pop();
            t2 = pq.top(); pq.pop();

            pq.push(t1 + t2);
            ans += (t1 + t2);
        }

        cout << ans << "\n";
        pq.pop();
    }

    return 0;
}