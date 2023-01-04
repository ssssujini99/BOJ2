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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, tmp;
    vector<int> crane;
    vector<int> box;

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> tmp;
        crane.push_back(tmp);
    }
    cin >> M;
    for(int i=0; i<M; i++){
        cin >> tmp;
        box.push_back(tmp);
    }

    sort(crane.begin(), crane.end(), greater<>());
    sort(box.begin(), box.end(), greater<>());

    int timer = 0;

    if(crane[0] < box[0]){ // 예외처리
        cout << -1;
        return 0;
    }

    while(box.size() != 0) {

        for(int i=0; i<crane.size(); i++){

            int size = box.size();

            for(int j=0; j<size; j++) {
                if(crane[i] >= box[j]) {
                    box.erase(box.begin() + j);
                    break;
                }
            }

        } // for문 끝

        timer++;
    }

    cout << timer << endl;
    return 0;
}