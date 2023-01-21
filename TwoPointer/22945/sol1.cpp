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
    int arr[100001] = {0, };

    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }

    ll ans = 0;
    int l = 0, r = N-1;

    while(l < r) {
        ll tmp = (r-l-1) * min(arr[l], arr[r]); // 팀의 능력

        if(tmp > ans) ans = tmp;

        if(arr[l] <= arr[r]) l++;
        else r--;
    }

    cout << ans << endl;
    return 0;
}