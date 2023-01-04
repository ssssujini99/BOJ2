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

vector<pair<ll, ll> > mauel;
unordered_map<ll, ll> um; // {위치, 누적합}
priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<> > ans; // {거리합, 우체국 위치}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    ll x, a;

    for(int i=0; i<N; i++) {
        cin >> x >> a;
        mauel.push_back(make_pair(x, a)); // {위치, 사람 수}
    }
    sort(mauel.begin(), mauel.end()); // 위치 기준으로 마을 정렬

    // 누적합 구해서 um에 기록 {위치, 누적합}
    ll total = 0;
    for(auto el : mauel) {
        total += el.second;
        um[el.first] = total;
    }

    // for(auto el : um) {
    //     cout << el.first << ", " << el.second << endl;
    // }

    // 이분탐색으로 왼쪽누적합 오른쪽누적합의 최소가 되는 위치 찾기
    int l = 0; int r = mauel.size()-1;
    while(l <= r) {
        int m = (l+r)/2;

        ll lSum = um[mauel[m].first];
        ll rSum = total - um[mauel[m].first];

        // cout << "m: " << m << " | " << "l: " << l << ", r: " << r << endl;
        // cout << "< " << lSum << ", " << rSum << " >"<< endl;
        // cout << mauel[m].first << ", " << abs(lSum-rSum) << endl << endl;


        if(lSum >= rSum) {
            r = m - 1;
            ans.push(make_pair(abs(lSum-rSum), mauel[m].first));
        }
        else{
            l = m + 1;
        }
    }

    cout << ans.top().second << endl; // 우체국 위치 출력

    return 0;
}