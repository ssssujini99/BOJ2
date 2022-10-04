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

    vector<int> v;
    int N, tmp, idx; cin >> N >> tmp;
    v.push_back(tmp);

    for(int i=1; i<N; i++){
        cin >> tmp;

        if(v.back() < tmp){
            v.push_back(tmp);
        }
        else{
            auto it = lower_bound(v.begin(), v.end(), tmp);
            *it = tmp;
        }
    }

    cout << v.size() << endl;

    return 0;
}