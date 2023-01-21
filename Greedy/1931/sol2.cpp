#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
using namespace std;

struct m{
    int start, finish;
};

struct compare{
    bool operator()(m& m1, m& m2){
        if(m1.finish != m2.finish){
            return m1.finish > m2.finish; // 끝나는 시간이 빠른거가 우선순위 높게
        }
        else{
            return m1.start > m2.start;
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    priority_queue<m, vector<m>, compare> pq;
    int N, t1, t2; cin >> N;
    for(int i=0; i<N; i++){
        cin >> t1 >> t2;
        pq.push({t1, t2});
    }

    int cnt = 1, finishTime = pq.top().finish; pq.pop();
    while(!pq.empty()){
        if(pq.top().start < finishTime){
            pq.pop();
            continue;
        }
        else{
            finishTime = pq.top().finish;
            cnt++;
            pq.pop();
        }
    }

    cout << cnt << endl;
    return 0;
}