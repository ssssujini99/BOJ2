#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <sstream>
#include <climits>

#define INF 999999999
using namespace std;

int parent[10001] = {0, };

struct s{
    int v1, v2;
    long long w;
};

struct compare{
    bool operator()(const s& s1, const s& s2){
        return s1.w > s2.w; // 가중치가 작은 것이 우선순위 높게
    }
};

int Find(int v){
    if(parent[v] == v) return v;
    else return parent[v] = Find(parent[v]);
}

void Union(int a, int b){
    int parent_a = Find(a);
    int parent_b = Find(b);

    // 더 작은쪽으로 합치기
    if(parent_a < parent_b) parent[parent_b] = parent_a;
    else parent[parent_a] = parent_b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int V, E, a, b, c; cin >> V >> E; // V: 정점의 개수, E: 간선의 개수
    priority_queue<s, vector<s>, compare> pq;

    for(int i=1; i<=V; i++) parent[i] = i;
    for(int i=0; i<E; i++){
        cin >> a >> b >> c;
        pq.push({a, b, c});
    }

    // 가장 작은거 하나는 따로 처리
    long long res_weight = pq.top().w; int cnt = 1;
    Union(pq.top().v1, pq.top().v2);
    pq.pop();

    while(1){
        int v1 = pq.top().v1; int v2 = pq.top().v2; int w = pq.top().w; pq.pop();
        if(Find(v1) != Find(v2)){
            Union(v1, v2);
            res_weight += w;
            cnt++;
        }

        if(cnt == V-1) break;
    }

    cout << res_weight;
    return 0;
}