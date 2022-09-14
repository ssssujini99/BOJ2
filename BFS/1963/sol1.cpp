#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

int is_Prime(int n){
    for(int i=2; i<=sqrt(n); i++){
        if(n%i == 0){
            return 0;
        }
    }

    return 1;
}

queue<pair<string, int> > q;
int um[10000] = {0, };


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    int a, b;

    while(T--){

        while(!q.empty()) q.pop(); // 큐 비워주기
        memset(um, 0, sizeof(um)); // um 초기화

        int flag = 1;
        cin >> a >> b;

        if(a == b){
            cout << "0\n";
            flag = 0;
            continue;
        }

        um[a] = 1;
        q.push({to_string(a), 0});

        while(!q.empty()){
            string s = q.front().first; int cnt = q.front().second; q.pop();

            if(stoi(s) == b){
                cout << cnt << endl;
                flag = 0;
                break;
            }

            for(int i=0; i<4; i++){
                for(int j=0; j<10; j++){
                    if(i==0 && j==0) continue; // 비밀번호는 1000부터 시작

                    string tmp = s;
                    tmp[i] = j + '0';
                    if(um[stoi(tmp)] == 0 && is_Prime(stoi(tmp)) == 1){
                        um[stoi(tmp)] = 1;
                        q.push({tmp, cnt + 1});
                    }
                }
            }

        } // bfs 끝


        if(flag == 1) cout << "impossible\n"; // 불가능한 경우 -> impossible 출력
    } // 한 test case 끝

    return 0;
}