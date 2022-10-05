#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <set>
using namespace std;

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    int res = 0;

    while(N+M-3-K>=0 && N-2>=0 && M-1>=0){
        N -= 2;
        M -= 1;
        res++;
    }

    cout << res << endl;
    return 0;
}