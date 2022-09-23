#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;
    vector<int> v(N);

    for(int i=0; i<N; i++){
        cin >> v[i];
    }
    sort(v.rbegin(), v.rend());

    int i = 0, tmp = K, cnt = 0;
    while(K > 0){
        while(v[i] > K) i++;

        cnt += K / v[i];
        K %= v[i];
    }

    cout << cnt << endl;
    return 0;
}