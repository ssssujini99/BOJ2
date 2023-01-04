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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    ll x, a, totalSum = 0;

    for(int i=0; i<N; i++) {
        cin >> x >> a;
        mauel.push_back(make_pair(x, a));
        totalSum += a;
    }

    if(totalSum % 2 != 0) totalSum++;
    sort(mauel.begin(), mauel.end());

    ll s = 0;
    for(int i=0; i<mauel.size(); i++) {
        s += mauel[i].second;
        if(s >= totalSum / 2) {
            cout << mauel[i].first << endl;
            exit(0);
        }
    }

    return 0;
}