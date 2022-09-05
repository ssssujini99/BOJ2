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
    int A, B, C; // A -> B, 가중치: C
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int TC; cin >> TC; // 테스트 케이스
    int N, M, W; // N: 지점의 수, M; 도로의 개수, W; 웜홀의 개수
    int S, E, T; // S: 시작지점, E: 도착지점, T: 줄어드는시간
    int d[501] = {0, };

    while(TC--){

        vector<s> v;

        cin >> N >> M >> W; // N: 지점의 수, M; 도로의 개수, W; 웜홀의 개수
        for(int i=1; i<=N; i++) d[i] = INF; // 거리 초기화
        for(int i=0; i<M; i++){
            // 도로 정보 입력받기
            cin >> S >> E >> T;
            v.push_back({S, E, T});
            v.push_back({E, S, T});
        }
        for(int i=0; i<W; i++){
            // 웜홀 정보 입력받기
            cin >> S >> E >> T;
            v.push_back({S, E, -T});
        }

        for(int i=0; i<N-1; i++){ // 매 사이클에서
            for(int j=0; j<v.size(); j++){ // 모든 간선 확인
                if(d[v[j].A] + v[j].C < d[v[j].B]){
                    d[v[j].B] = d[v[j].A] + v[j].C;
                }
            }
        }
        bool flag = true;

        for(int j=0; j<v.size(); j++){
            if(d[v[j].A] + v[j].C < d[v[j].B]){
                cout << "YES\n";
                flag = false;
                break;
            }
        }
        if(flag) cout << "NO\n";

    } // while문 끝

    return 0;
}