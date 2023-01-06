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

deque<char> dq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K; cin >> N >> K;
    string s; cin >> s;

    dq.push_back(s[0]);

    int cnt = 0;
    int i = 1;
    while(cnt != K && i < s.size()) {

        if(dq.back() >= s[i]) dq.push_back(s[i]);
        else{
            // dq.back() < s[i] 인 경우
            while(!dq.empty() && dq.back() < s[i]) {
                dq.pop_back(); // 지우기
                cnt++; // 지운 횟수 증가

                if(cnt == K) break;
            }
            dq.push_back(s[i]);
        }

        i++;
    }

    cnt = 0;
    int totalCnt = s.size() - K;

    while(!dq.empty()) {
        cout << dq.front(); cnt++;
        dq.pop_front();

        if(cnt == totalCnt) exit(0);
    }
    while(i < s.size()) {
        cout << s[i++]; cnt++;
        if(cnt == totalCnt) exit(0);
    }

    return 0;
}