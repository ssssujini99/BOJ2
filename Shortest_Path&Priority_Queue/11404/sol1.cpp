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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int dp[101][101] = {0, };
    int n, m; // n: 도시의 개수, m: 버스의 개수
    int a, b, c;
    cin >> n >> m;

    // 초기화 세팅
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i == j) dp[i][j] = 0;
            dp[i][j] = INF;
        }
    }

    // 입력 받기
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        dp[a][b] = min(dp[a][b], c); // 시작 도시와 도착 도시를 연결하는 노선이 여러 개인 경우 예외처리 -> 더 작은 걸로 갱신
    }

    for(int i=1; i<=n; i++){ // j 에서 k를 가는데 i를 경유 ( j -> "i" -> k )
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(j != k){
                    dp[j][k] = min(dp[j][k], dp[j][i]+dp[i][k]);
                }
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(dp[i][j] == INF) cout << "0 "; // i에서 j로 가는데 길이 없는 경우
            else cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}