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


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, tmp, sum=0; cin >> N;
    vector<int> p; vector<int> m;

    for(int i=0; i<N; i++){
        cin >> tmp;
        if(tmp > 0) p.push_back(tmp);
        else m.push_back(tmp);
    }
    sort(p.begin(), p.end(), greater<>()); // 내림차순 정렬
    sort(m.begin(), m.end());

    int i, j;
    for(i=0; i+1<p.size(); i+=2){
        if(p[i]*p[i+1] > p[i]+p[i+1]) sum += p[i]*p[i+1];
        else sum += p[i]+p[i+1];
    }
    if(i == p.size()-1) sum += p[i];

    for(j=0; j+1<m.size(); j+=2){
        sum += m[j] * m[j+1];
    }
    if(j == m.size()-1) sum += m[j];

    cout << sum << endl;
    return 0;
}