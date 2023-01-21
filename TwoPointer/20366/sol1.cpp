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
    ll a[601] = {0, };

    for(int i=0; i<N; i++) cin >> a[i];
    sort(a, a+N);

    ll ans = 2000000000;

    for(int i=0; i<N-1; i++) {
        for(int j=i+1; j<N; j++) {

            // i, j 를 선택
            int l = i+1; int r = N-1;

            while(l == i || l == j) l++;
            while(r == j || r == i) r--;

            while(l < r) {
                ll sum1 = a[i] + a[j];
                ll sum2 = a[l] + a[r];
                ll dif = abs(sum1 - sum2);

                if(dif == 0) { cout << 0; exit(0); };
                if(dif < ans) ans = dif; // 차이 갱신

                if(sum1 < sum2) r--;
                else l++; // sum1 > sum2;

                while(l == i || l == j) l++;
                while(r == j || r == i) r--;
            }
        }
    }

    cout << ans << endl;
    return 0;
}