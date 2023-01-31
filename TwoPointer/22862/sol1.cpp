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

    int N, K; ll tmp; cin >> N >> K; // K: 지울 수 있는 홀수 개수
    vector<ll> v;
    int count[1000001] = {0, }; // (자신포함) 홀수항 개수

    cin >> tmp;
    v.push_back(tmp);
    if(tmp % 2 == 1) count[0] = 1;
    else count[0] = 0;

    for(int i=1; i<N; i++) {
        cin >> tmp;
        v.push_back(tmp);

        if(tmp % 2 == 1) count[i] = count[i-1] + 1;
        else count[i] = count[i-1];
    }


    int l = 0, r = 0;
    int ans = 0;

    while(r < N) {
        int firstOdd, totOdd;
        // 왼쪽 포인터가 짝수인지 홀수인지 체크
        if(v[l] % 2 == 1) firstOdd = 1;
        else firstOdd = 0;

        while(r+1 < N && firstOdd + count[r+1] - count[l] <= K) r++;

        // l 과 r 사이 홀수의 개수 구하기
        if(v[l]%2 == 1 && v[r]%2 == 1) { // 홀 홀
            totOdd = count[r] - count[l] + 1;
        }
        else if(v[l]%2 == 1 && v[r]%2 == 0) { // 홀 짝
            totOdd = count[r] - count[l] + 1;
        }
        else if(v[l]%2 == 0 && v[r]%2 == 1) { // 짝 홀
            totOdd = count[r] - count[l];
        }
        else { // 짝 짝
            totOdd = count[r] - count[l];
        }

        // cout << "l: " << l << ", r: " << r << " | " << r - l + 1 - totOdd << endl;

        ans = max(ans, (r-l+1) - totOdd);

        if(r == N-1) break;

        l++;
    }

    cout << ans << endl;
    return 0;
}