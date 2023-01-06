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

ll arr[100001] = {0, };
ll accum1[100001] = {0, };
ll accum2[100001] = {0, };
ll tot = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    ll middleMax = 0;

    ll ans1 = 0, ans2 = 0, ans3 = 0, ans = 0;
    ll tmpAns;

    for(int i=0; i<N; i++) {
        cin >> arr[i];
        tot += arr[i];
        accum1[i] = tot; // i 까지의 누적합 저장

        if(i != 0 && i != N-1) middleMax = max(middleMax, arr[i]);
    }

    tot = 0;
    for(int i=N-1; i>=0; i--) {
        tot += arr[i];
        accum2[i] = tot;
    }

    // case1 : 벌, 벌, 꿀통
    for(int i=1; i<N-1; i++) {
        tmpAns = (accum1[N-1]-accum1[i]) + (accum1[N-1]-arr[0]-arr[i]);
        ans1 = max(ans1, tmpAns);
    }

    // case2 : 꿀통, 벌 벌
    for(int i=N-2; i>=1; i--) {
        tmpAns = (accum2[0]-accum2[i]) + (accum2[0]-arr[N-1]-arr[i]);
        ans2 = max(ans2, tmpAns);
    }

    // case3 : 벌, 꿀통, 벌
    ans3 = tot - (arr[0] + arr[N-1]) + middleMax;

    ans = ans1;
    ans = max(ans, ans2);
    ans = max(ans, ans3);

    cout << ans << endl;
    return 0;
}