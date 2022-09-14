#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unordered_map<string, int> um;
    queue<pair<long long, string> > q;

    long long s, t; cin >> s >> t;

    if(s == t){
        cout << 0 << endl;
        return 0;
    }

    um[to_string(s)] = 1;
    q.push({s, ""});

    while(!q.empty()){
        long long value = q.front().first;
        string calc = q.front().second;
        q.pop();

        if(value == t){
            cout << calc << endl;
            exit(0);
        }

        if(value * value <= t && um[to_string(value * value)] == 0){
            um[to_string(value * value)] = 1;
            q.push({value * value, calc + "*"});
        }

        if(value + value <= t && um[to_string(value + value)] == 0){
            um[to_string(value + value)] = 1;
            q.push({value + value, calc + "+"});
        }

        if(um[to_string(value - value)] == 0){
            um[to_string(value - value)] = 1;
            q.push({value - value, calc + "-"});
        }

        if(value != 0 && um[to_string(value / value)] == 0){
            um[to_string(value / value)] = 1;
            q.push({value / value, calc + "/"});
        }

    }

    cout << -1 << endl;
    return 0;
}