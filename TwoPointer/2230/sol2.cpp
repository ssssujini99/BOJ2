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

    vector<ll> v; int N; ll M, tmp;
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());

    int l = 0, r = 0;
    ll tmpDis = 2000000000;

    while(l<=r && r<N) {
        ll dis = v[r] - v[l];

        if(dis == M) {
            cout << dis << endl;
            exit(0);
        }

        if(dis >= M && dis < tmpDis) {
            tmpDis = dis; // 더 작은 차이로 갱신시키기
        }

        if(dis <= M) r++;
        else l++;
    }

    cout << tmpDis << endl;
    return 0;
}