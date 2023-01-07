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

struct s {
    int ni, si;
};

bool compare(s s1, s s2) {
    if(s1.si != s2.si) {
        return s1.si > s2.si; // 내림차순 정렬
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, nii, sii; cin >> N;
    vector<s> v;

    for(int i=0; i<N; i++) {
        cin >> nii >> sii;
        v.push_back({nii, sii});
    }

    sort(v.begin(), v.end(), compare);

    int ans = v[0].si - v[0].ni;

    if(ans < 0) { // 예외처리
        cout << -1 << endl;
        exit(0);
    }

    for(int i=1; i<N; i++) {
        ans = min(ans, v[i].si);

        if(ans - v[i].ni >= 0) ans -= v[i].ni;
        else {
            cout << -1 << endl;
            exit(0);
        }

    }

    cout << ans << endl;
    return 0;
}