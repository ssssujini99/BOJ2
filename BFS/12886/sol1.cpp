#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

unordered_map<string, int> um;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    queue<vector<int> > q;
    int a, b, c; cin >> a >> b >> c;

    if((a+b+c)%3 != 0){ // 앞부분에서 먼저 처리해주기
        cout << 0 << endl;
        exit(0);
    }

    vector<int> v;
    v.push_back(a); v.push_back(b); v.push_back(c);
    sort(v.begin(), v.end());
    string s = to_string(v[0]) + to_string(v[1]) + to_string(v[2]);
    um[s] = 1;
    q.push(v);

    while(!q.empty()){
        vector<int> v = q.front(); q.pop();
        if(v[0] == v[1] && v[1] == v[2]){
            cout << 1 << endl;
            exit(0);
        }

        if(v[0] != v[1]){
            int t1 = v[0] * 2;
            int t2 = v[1] - v[0];
            v[0] = t1; v[1] = t2;
            sort(v.begin(), v.end());
            string s = to_string(v[0]) + to_string(v[1]) + to_string(v[2]);
            if(um[s] == 0){
                um[s] = 1;
                q.push(v);
            }
        }

        if(v[0] != v[2]){
            int t1 = v[0] * 2;
            int t2 = v[2] - v[0];
            v[0] = t1; v[2] = t2;
            sort(v.begin(), v.end());
            string s = to_string(v[0]) + to_string(v[1]) + to_string(v[2]);
            if(um[s] == 0){
                um[s] = 1;
                q.push(v);
            }
        }

        if(v[1] != v[2]){
            int t1 = v[1] * 2;
            int t2 = v[2] - v[1];
            v[1] = t1; v[2] = t2;
            sort(v.begin(), v.end());
            string s = to_string(v[0]) + to_string(v[1]) + to_string(v[2]);
            if(um[s] == 0){
                um[s] = 1;
                q.push(v);
            }
        }
    }

    cout << 0 << endl;
    return 0;
}