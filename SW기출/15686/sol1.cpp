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

int N, M;
long long res = LONG_MAX;
int a[52][52] = {0, };

vector<pair<int, int> > chicken;
vector<pair<int, int> > house;

int dist(pair<int, int> p1, pair<int, int> p2){
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> a[i][j];

            if(a[i][j] == 1) house.push_back(make_pair(i, j));
            if(a[i][j] == 2) chicken.push_back(make_pair(i, j));
        }
    }

    vector<int> v;
    for(int i=0; i<M; i++) v.push_back(1);
    for(int i=0; i<chicken.size()-M; i++) v.push_back(0);

    sort(v.begin(), v.end());

    do{
        // 치킨집 중 M개 구하기 (조합)
        map<pair<int, int>, priority_queue<int, vector<int>, greater<int> > > m;

        for(int i=0; i<v.size(); i++){
            if(v[i] == 1){
                // 선택된 치킨집에 대해서 -> 각 집까지의 거리 구하기
                for(int j=0; j<house.size(); j++){
                    m[house[j]].push(dist(house[j], chicken[i]));
                }

            }
        }

        // 도시의 치킨 거리 구하기
        long long res_tmp = 0;
        for(auto it = m.begin(); it != m.end(); it++){
            res_tmp += it->second.top();
        }

        // 갱신
        res = min(res, res_tmp);

    }while(next_permutation(v.begin(), v.end()));

    cout << res << endl;

    return 0;
}