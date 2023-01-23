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
    int a[10001] = {0, };

    for(int i=0; i<N; i++) {
        cin >> a[i];
    }
    sort(a, a+N);

    ll ans = 0;

    for(int i=0; i<N-2; i++) {
        for(int j=i+1; j<N-1; j++) {
            int tmp = a[i] + a[j];

            ll cnt = upper_bound(a+(j+1), a+N, -tmp) - lower_bound(a+(j+1), a+N, -tmp);

            ans += cnt;
        }
    }

    cout << ans << endl;
    return 0;
}