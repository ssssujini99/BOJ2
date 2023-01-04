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

    int N, K; cin >> N >> K;
    long long ex, cur;
    vector<long long> v;

    cin >> ex;
    for(int i=1; i<N; i++){
        cin >> cur;
        v.push_back(cur - ex); // 구간합들 더하기
        ex = cur;
    }

    sort(v.begin(), v.end()); // 구간합들 정렬

    long long ans = 0;
    for(int i=0; i<v.size()-(K-1); i++) ans += v[i];
    cout << ans << endl;

    return 0;
}