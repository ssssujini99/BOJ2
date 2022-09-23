#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

struct s{
    long long start, end;
    long long len;
};

bool comp(s s1, s s2){
    if(s1.end != s2.end) return s1.end < s2.end; // 회의가 빨리 끝나는 거 기준으로
    else{
        return s1.start < s2.start; // 끝나는 시간이 같으면 먼저 시작하는 거 기준으로
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    vector<s> v;
    long long t1, t2; int cnt = 0;

    for(int i=0; i<n; i++){
        cin >> t1 >> t2;
        v.push_back({t1, t2, t2-t1});
    }

    sort(v.begin(), v.end(), comp);

    long long start_time = v[0].start;
    long long end_time = v[0].end;
    cnt = 1;

    for(int i=1; i<v.size(); i++){
        if(v[i].start >= end_time){
            end_time = v[i].end;
            cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}