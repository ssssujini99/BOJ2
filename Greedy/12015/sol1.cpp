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

    multiset<int> mts;
    int N, tmp, idx; cin >> N;
    int res = 0;


    for(int i=0; i<N; i++){
        cin >> tmp;

        if(mts.lower_bound(tmp) == mts.end()){
            mts.insert(tmp);
        }
        else{
            mts.erase(*(mts.lower_bound(tmp)));
            mts.insert(tmp);
        }
    }

    cout << mts.size() << endl;

    return 0;
}