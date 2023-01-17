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

    int arr[501] = {0, }; int result = 0;
    int H, W; cin >> H >> W;

    for(int i=0; i<W; i++) {
        cin >> arr[i];
    }

    int left = 0; int right = W-1;
    int leftMax = arr[0];
    int rightMax = arr[W-1];

    while(left < right) {
        leftMax = max(leftMax, arr[left]);
        rightMax = max(rightMax, arr[right]);

        if(leftMax <= rightMax) {
            result += (leftMax - arr[left]);
            left += 1;
        }
        else {
            result += (rightMax - arr[right]);
            right -= 1;
        }
    }

    cout << result << endl;
    return 0;
}