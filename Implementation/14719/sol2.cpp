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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int H, W; cin >> H >> W;
    int arr[501] = {0, }; int ans = 0;

    for(int i=0; i<W; i++) cin >> arr[i];

    for(int i=1; i<W-1; i++) {
        // 인덱스 i를 기준으로 왼쪽, 오른쪽에서 가장 큰 값 탐색

        int leftMax = arr[i]; int rightMax = arr[i];
        for(int j=i-1; j>=0; j--) leftMax = max(leftMax, arr[j]);
        for(int j=i+1; j<W; j++) rightMax = max(rightMax, arr[j]);

        int tmpR = min(leftMax, rightMax);
        ans += (tmpR - arr[i]);
    }

    cout << ans << endl;
    return 0;
}