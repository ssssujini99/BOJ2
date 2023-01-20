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

        ll ans = 200000000; ll cnt = 0;

        for(int i=0; i<v.size()-1; i++) {
            int l = i+1; int r = v.size()-1; // 두 포인터 설정

            while(l <= r) {
                int mid = (l+r) / 2;

                if(abs(K-(v[i]+v[mid])) < ans) { // 더 가까운 수여서 갱신 필요
                    ans = abs(K - (v[i] + v[mid]));
                    cnt = 1;
                }
                else if(abs(K-(v[i]+v[mid])) == ans) { // 같으면 -> cnt만 증가
                    cnt++;
                }
                else {
                    // 갱신 필요없는 경우
                }

                if(v[i] + v[mid] <= K) {
                    l = mid + 1;
                }
                else { // v[i] + v[mid] > K
                    r = mid - 1;
                }
            }
        }

        cout << cnt << "\n";
    }

    return 0;
}