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

    int N; cin >> N;
    vector<int> v(N);

    for(int i=0; i<N; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    int sum = 0;
    for(int i=0; i<v.size(); i++){
        sum += v[i]*(N-i);
    }

    cout << sum << endl;
    return 0;
}