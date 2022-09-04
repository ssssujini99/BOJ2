#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <sstream>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<pair<int, int> > vec[20001];
    int ch[20001] = {0, };
    int d[20001];

    int V, E, S; cin >> V >> E >> S;
    int u, v, w;

    for(int i=0; i<E; i++){
        cin >> u >> v >> w;
        vec[u].push_back(make_pair(v, w));
    }

    for(int i=1; i<=V; i++){
        d[i] = 987654321;
    }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq; // {거리, 노드}
    d[S] = 0; // 시작점까지의 거리 = 0
    pq.push({0, S});

    while(!pq.empty()){
        int dis = pq.top().first; int node = pq.top().second;
        pq.pop();

        if(d[node] < dis) continue; // 갱신할 필요가 없는 경우 -> continue

        for(int i=0; i<vec[node].size(); i++){
            if(dis + vec[node][i].second < d[vec[node][i].first]){
                d[vec[node][i].first] = dis + vec[node][i].second;
                pq.push({d[vec[node][i].first], vec[node][i].first});
            }
        }
    }

    for(int i=1; i<=V; i++){
        if(d[i] == 987654321){
            cout << "INF\n";
        }
        else cout <<  d[i] << "\n";
    }

    return 0;
}