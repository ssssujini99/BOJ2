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
#include <cstdio>

#define INF 999999999
using namespace std;

struct point{
    int idx;
    double x, y;
};

struct connect{
    point p1;
    point p2;
    double len;
};

struct compare{
    bool operator()(const connect c1, const connect c2){
        return c1.len > c2.len; // 거리가 작은 것이 우선순위 높게
    };
};

double calc_Len(point p1, point p2){
    double res = sqrt(pow(fabs(p1.x - p2.x), 2) + pow(fabs(p1.y - p2.y), 2));
    return res;
}

// Union-Find 함수
int parent[101] = {0, };

int Find(int v){
    if(parent[v] == v) return v;
    else{
        return parent[v] = Find(parent[v]);
    }
}

void Union(int a, int b){
    int parent_a = Find(a);
    int parent_b = Find(b);

    // 더 작은 쪽으로 부모 합치기
    if(parent_a < parent_b) parent[parent_b] = parent_a;
    else parent[parent_a] = parent_b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    point p[101];
    int n; cin >> n;
    double x, y;
    for(int i=0; i<n; i++){
        cin >> x >> y;
        p[i].idx = i;
        p[i].x = x;
        p[i].y = y;

        // parent 배열 초기화
        parent[i] = i;
    }

    priority_queue<connect, vector<connect>, compare> pq;
    connect c;
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            // 두 점 사이의 거리를 구해서 우선순위 큐에 넣기
            c.p1 = p[i]; c.p2 = p[j]; c.len = calc_Len(p[i], p[j]);
            pq.push(c);
        }
    }

    double res = 0; int cnt = 0;
    while(1){
        point p1 = pq.top().p1; point p2 = pq.top().p2; double len = pq.top().len;
        pq.pop();

        if(Find(p1.idx) != Find(p2.idx)){
            // 부모가 다르면 -> 서로 다른 집합
            Union(p1.idx, p2.idx);
            res += len;
            cnt++;
        }
        if(cnt == n-1){
            break;
        }
    }

    // cout << res << endl; // 결과 출력
    printf("%.2f", res);
    return 0;
}