#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ll> v;
    int N; ll M, tmp; cin >> N >> M;
    for(int i=0; i<N; i++) {
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());

    ll gap = 2000000000;

    for(int i=0; i<v.size()-1; i++) {
        int l = i+1; int r = v.size()-1;

        while(l <= r) {
            int m = (l+r)/2;

            if(v[m]-v[i] == M) {
                cout << M << endl;
                exit(0);
            }
            else if(v[m]-v[i] >= M && v[m]-v[i] < gap) {
                gap = v[m]-v[i]; // 갱신
            }
            else {
            }

            if(v[m]-v[i] > M) {
                r = m - 1;
            }
            else { // v[m] - v[i] < M
                l = m + 1;
            }
        }
    }

    cout << gap << endl;
    return 0;
}