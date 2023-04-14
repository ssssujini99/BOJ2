#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int n; vector<int> v;
    cin >> n;
    for(int i=0; i<n; i++) {
        int tmp; cin >>tmp;
        v.push_back(tmp);
    }

    int ch[1000001] = {0, };
    int len = 0; int cnt = 0;

    for(int i=0; i<v.size(); ) {
        len = v[i];
        ch[i] = 1; cnt++; len--; // 터트리고 체크해주고 화살높이 -= 1
        if (i == v.size()-1) break;

        int j = i+1;
        while(j < v.size() && len > 0) {
            if (v[j] == len && ch[j] == 0) { // 길이가 화살과 같고, 아직 떠있는 풍선이면
                ch[j] = 1; len--; // 터트리고 체크해주고 화살높이 -= 1
            }
            j++;
        }

        while(i+1 <= v.size()) { // 다음번 i 위치 찾아주기
            i++;
            if (ch[i] == 0) break;
        }

        if (i == v.size()) break; // 아예 끝났을 경우 고려해주기
    }

    cout << cnt;
}