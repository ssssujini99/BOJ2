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

int parent[1000001] = {0, };

// 부모 찾는 함수
int Find(int v){
    if(parent[v] == v) return v;
    else return parent[v] = Find(parent[v]);
}

// 합치는 함수
void Union(int a, int b){
    int parent_a = Find(a);
    int parent_b = Find(b);

    // 더 작은쪽으로 합치기
    if(parent_a < parent_b){
        parent[parent_b] = parent_a;
    }
    else{
        parent[parent_a] = parent_b;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    int a, b, c;

    for(int i=1; i<=n; i++) parent[i] = i;

    for(int i=0; i<m; i++){
        // m 번의 연산 수행
        cin >> a >> b >> c;
        if(a == 0){
            Union(b, c);
        }
        else{ // a == 1일때
            if(Find(b)==Find(c)) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}