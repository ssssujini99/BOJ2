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

bool brr[500001] = {false};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K; cin >> N >> K;
    string s; cin >> s;

    int cnt = 0;
    while(cnt != K) {

        for(int i=0; (i<s.size()-1) && (brr[i] == false); i++) {

            int nextIdx = i+1;
            while(nextIdx < s.size()) {
                if(nextIdx < s.size() && brr[nextIdx] == false) break;
                nextIdx++;
            }

            if(nextIdx < s.size() && s[i] < s[nextIdx]) { // 지워야 하는 경우
                brr[i] = true;
                cnt++;
                if(cnt == K) break;
            }
        }

    }

    for(int i=0; i<s.size(); i++) {
        if(brr[i] == false) cout << s[i];
    }
    return 0;
}