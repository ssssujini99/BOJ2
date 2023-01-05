#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstring>
#include <set>
#include <climits>
using namespace std;

struct s {
    int send;
    int get;
    int count;
};

bool compare(s s1, s s2) {
    if(s1.get != s2.get) {
        return s1.get < s2.get; // 끝나는 마을이 빠른 기준
    }
    else { // 끝나는 시간이 같으면 -> 늦게 시작하는 거 기준 == 간격이 작은 거 위주로
        return s1.send > s2.send;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, C, M; cin >> N >> C >> M;
    vector<s> v;
    s ss;

    int t1, t2, t3;
    for(int i=0; i<M; i++) {
        cin >> t1 >> t2 >> t3;
        ss.send = t1; ss.get = t2; ss.count = t3;
        v.push_back(ss);
    }

    sort(v.begin(), v.end(), compare);

    int mauel[2001] = {0, };
    long long ans = 0;

    for(int i=0; i<v.size(); i++) {

        int flag = 1;
        int w = ( C >= v[i].count ? v[i].count : C ); // 최대 이걸로 시작

        for(int j=v[i].send; j<v[i].get; j++) {
            if(mauel[j] == C) { // 못 실음
                flag = 0;
                break;
            }
            else { // 만약 담을 수 있는 무게가 작아지면 작아진대로 갱신해주기
                int maxC = C - mauel[j]; // 해당 j 마을에서 담을 수 있는 최대 무게
                w = ( maxC >= w ? w : maxC );
            }
        }

        // 넣을 수 있는 무게 값 넣어주기
        if(flag != 0) {
            ans += w;

            for(int j = v[i].send; j<v[i].get; j++) {
                mauel[j] += w;
            }
        }
    }

    cout << ans << endl;
    return 0;
}