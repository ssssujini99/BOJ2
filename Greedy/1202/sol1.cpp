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

struct j{
    int m, v;
};

struct compare{
    bool operator()(j& j1, j& j2){
        if(j1.v == j2.v){
            // 가격이 같으면 -> 무게가 오름차순으로
            return j1.m > j2.m;
        }
        else return j1.v < j2.v; // 가격가 다르면 가격 내림차순으로
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K, m, v; cin >> N >> K;
    priority_queue<j, vector<j>, compare> pq;
    vector<long long int> bag(K);
    multiset<long long int> ms;
    multiset<long long int>::iterator it;
    long long t;

    for(int i=0; i<N; i++){
        cin >> m >> v;
        pq.push({m, v});
    }
    for(int i=0; i<K; i++){
        cin >> t;
        ms.insert(t);
    }

    long long int res = 0;

    while(!pq.empty()){
        long long int max_m = pq.top().m; // 보석 무게
        long long int max_v = pq.top().v; // 보석 가격
        pq.pop();

        it = ms.lower_bound(max_m);

        if(it != ms.end()){ // 해당 보석의 무게를 담을 수 있는 가방이 존재 한다면
            res += max_v;
            // 가방 삭제해주기
            ms.erase(it);
        }
    }

    cout << res << endl;
    return 0;
}