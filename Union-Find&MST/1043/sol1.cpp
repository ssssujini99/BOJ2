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

int parent[51] = {0, };

// 특정 원소가 속한 집합을 찾기
int Find(int v){
    if(parent[v] == v) return v;
    else return parent[v] = Find(parent[v]); // Find 함수를 최적화하기 위해 경로 압축 이용하기
}

// 두 원소가 속한 집합을 합치기
void Union(int a, int b){
    int parent_a = Find(a);
    int parent_b = Find(b);

    // 더 작은 쪽으로 합침
    if(parent_a < parent_b){
        parent[parent_b] = parent_a;
    }
    else parent[parent_a] = parent_b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; // N: 사람 수, M: 파티 수
    cin >> N >> M;

    for(int i=1; i<=N; i++) parent[i]=i; // parent 초기화
    vector<int> v; int tmp, t_Num; cin >> t_Num; // t_Num: 진실을 아는 사람 수

    if(t_Num == 0){ // 진실을 아는 사람의 수가 0인 경우 예외처리
        cout << M;
        exit(0);
    }

    for(int i=0; i<t_Num; i++){
        cin >> tmp;
        v.push_back(tmp); // 진실을 아는 사람 번호를 벡터에 저장

        if(i >= 1) Union(v[i-1], v[i]);
    }
    sort(v.begin(), v.end());

    vector<int> party[51];
    int peoples, num;
    for(int i=1; i<=M; i++){
        // 각 파티마다 오는 사람 수와 번호들
        cin >> peoples;
        for(int j=0; j<peoples; j++){
            cin >> num;
            party[i].push_back(num);

            if(j >= 1) Union(party[i][j-1], party[i][j]);
        }
    }

    for(int i=N; i>=1; i--) Find(i);

    int res = 0;
    for(int i=1; i<=M; i++){
        if(parent[party[i][0]] != parent[v[0]]) res++;
    }

    cout << res << "\n";
    return 0;
}