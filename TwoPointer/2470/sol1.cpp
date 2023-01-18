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

    int N; cin >> N;
    vector<ll> v; ll tmp;

    for(int i=0; i<N; i++){
        cin >> tmp;
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());

    ll left = 0; ll right = v.size()-1;
    ll r_l = v[0], r_r = v[v.size()-1], r_s = v[left] + v[right];

    while(left < right) {
        if(v[left] + v[right] == 0) {
            r_l = v[left]; r_r = v[right]; break;
        }

        if(abs(v[left] + v[right]) < abs(r_s)) { // 갱신
            r_l = v[left]; r_r = v[right]; r_s = v[left] + v[right];
        }

        if(v[left] + v[right] > 0) right--;
        else left++;
    }

    cout << r_l << " " << r_r << endl;
    return 0;
}