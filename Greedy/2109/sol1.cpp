#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
using namespace std;

struct c{
    int p, d;
};

struct compare{
    bool operator()(c& c1, c& c2){
        return c1.p < c2.p; // 가격 내림차순으로
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, date, pay; cin >> n;
    int res[10001] = {0, };
    int sum = 0;
    priority_queue<c, vector<c>, compare> pq;

    for(int i=0; i<n; i++){
        cin >> pay >> date;
        pq.push({pay, date});
    }

    while(!pq.empty()){
        date = pq.top().d; pay = pq.top().p; pq.pop();

        for(int i=date; i>=1; i--){ // 최대한 뒷 날 부터 배정해주기
            if(res[i] == 0){
                res[i] = pay;
                break; // 배정을 했다면 바로 탈출
            }
        }
    }

    for(int i=1; i<=10000; i++){
        sum += res[i];
    }
    cout << sum << endl;
    return 0;
}