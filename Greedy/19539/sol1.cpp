#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <map>
#include <sstream>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, tmp;
    int tot = 0, divSum = 0, modSum = 0;
    cin >> n;

    for(int i=0; i<n; i++) {
        cin >> tmp;
        tot += tmp;
        divSum += tmp / 2;
        modSum += tmp % 2;
    }

    if (tot % 3 != 0) {
        cout << "NO" << endl;
        return 0;
    }

    tot /= 3; // 전체 물 뿌린 횟수

    if (divSum >= tot) {
        int tmp = divSum - tot;
        if (modSum + 2*tmp == tot) {
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}