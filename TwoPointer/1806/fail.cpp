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

    int N, tmp; ll S;
    int a[100001] = {0, }; ll b[100001] = {0, };
    ll tSum = 0;

    cin >> N >> S;
    cin >> a[0]; b[0] = a[0];
    for(int i=1; i<N; i++) {
        cin >> a[i];
        b[i] = b[i-1] + a[i]; // 누적합
    }

    int minLen = N; ll minSum = 0;

    for(int i=0; i<N; i++) {
        int l = i; int r = N-1;

        while(l <= r) {
            int tmpLen = r - l + 1;
            ll partSum = b[r] - b[l] + a[l]; // l ~ r 까지 수열의 합

            if(partSum >= S && tmpLen < minLen) { // 갱신이 필요한 부분
                minSum = partSum;
                minLen = tmpLen;
            }

            if(partSum >= S) {
                r—;
            }
            else {
                l++;
            }
        }
    }

    if(minSum == 0) {
        cout << 0 << endl;
    }
    else {
        cout << minLen << endl;
    }

    return 0;
}