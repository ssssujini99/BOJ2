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

vector<int> v;

int binarySearch(int l, int r, int val){
    int ans = 1000001;

    while(l<=r){
        int mid = (l+r)/2;

        if(v[mid] >= val){ // val 이상인 값이 있는 지 확인 -> 벡터에 push를 해도 되는지 확인하는 용도
            ans = min(ans, mid);
            r = mid - 1;
        }
        else{ // v[mid] < val
            l = mid + 1;
        }
    }

    if(ans != 1000001) return ans;
    else return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    multiset<int> mts;
    int N, tmp, idx; cin >> N >> tmp;
    v.push_back(tmp);

    for(int i=1; i<N; i++){
        cin >> tmp;

        int idx = binarySearch(0, v.size()-1, tmp);
        if(idx == -1){
            v.push_back(tmp);
        }
        else{
            v[idx] = tmp;
        }
    }

    cout << v.size() << "\n";
    return 0;
}