#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

struct j{
    long long int m, v;
};

struct compare{
    bool operator()(j& j1, j& j2){
        if(j1.v == j2.v){
            // 가격이 같으면 -> 무게가 오름차순으로
            return j1.m > j2.m;
        }
        else return j1.v < j2.v; // 가치가 다르면 가치 내림차순으로
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long int N, K, m, v; cin >> N >> K;
    priority_queue<j, vector<j>, compare> pq;
    vector<long long int> bag(K);

    for(int i=0; i<N; i++){
        cin >> m >> v;
        pq.push({m, v});
    }
    for(int i=0; i<K; i++){
        cin >> bag[i];
    }
    sort(bag.begin(), bag.end()); // bag 오름차순 정렬


    long long int res = 0;
    for(int i=0; i<K; i++){
        long long int max_c = bag[i];

        vector<j> tmp;
        while(!pq.empty()){
            if(pq.top().m <= max_c){
                res += pq.top().v;
                pq.pop();
                break; // 한 개를 담았으면 break -> 탈출
            }
            else{
                tmp.push_back(pq.top());
                pq.pop();
            }
        }

        for(int j=0; j<tmp.size(); j++){
            pq.push(tmp[j]);
        }
    }

    cout << res << endl;
    return 0;
}