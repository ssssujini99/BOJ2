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

struct s{
    int A, B, C;
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<s> vec;

    int N, M; cin >> N >> M; // N: 도시의 개수, M: 버스 노선의 개수
    int A, B, C; // A: 시작도시, B: 도착도시, C: 걸리는시간(가중치)
    long long d[501] = {0, }; // 거리

    for(int i=0; i<M; i++){
        cin >> A >> B >> C;
        vec.push_back({A, B, C});
    }

    for(int i=1; i<=N; i++) d[i] = INF; // 거리 초기화

    d[1] = 0; // 1번 도시에서 출발
    for(int i=0; i<N-1; i++){ // (정점 - 1) 번 == (노드 수 - 1) 번 만큼 반복
        for(int j=0; j<vec.size(); j++){ // 한 사이클마다 모든 간선 확인해주기 -- > 시간복잡도: O((N-1) * V) == O((정점 수-1) * 간선 수)
            if(d[vec[j].A] != INF && d[vec[j].A] + vec[j].C < d[vec[j].B]) d[vec[j].B] = d[vec[j].A] + vec[j].C;
        } // 추가: 1번 -> A 까지의 거리가 무한대이면 안됨 !! (주의)
    } // 간선을 잇는 출발정점이 '한번이라도 계산이 된 정점이라면' 해당 간선이 잇는 정점의 거리를 비교해서 업데이트한다

    for(int j=0; j<vec.size(); j++){
        if(d[vec[j].A] != INF && d[vec[j].A] + vec[j].C < d[vec[j].B]){
            cout << -1; // 음수 사이클이 존재하는 경우 예외처리 해주기
            exit(0);
        }
    }

    for(int i=2; i<=N; i++){
        if(d[i] == 999999999) cout << "-1\n";
        else cout << d[i] << "\n";
    }
    return 0;
}