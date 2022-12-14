## MST(최소신장트리) 1 - 크루스칼 알고리즘

* 신장 트리: 그래프에서 모든 노드를 포함하면서 ~~사이클이 존재하지 않는~~ 부분 그래프를 의미
  * 모든 노드가 포함되어 서로 연결되면서 사이클이 존재하지 않는다는 조건은 트리의 조건이기도 함

## 크루스칼 알고리즘

* 대표적인 **최소 신장 트리 알고리즘**
* 그리디 알고리즘으로 분류됨 (현재에서 가장 가중치가 작은 간선을 계속해서 택해나감)

* 구체적인 동작 과정
  1) 간선 데이터를 비용에 따라 오름차순 정렬함
  2) 간선을 하나씩 확인하며 **현재의 간선이 사이클이 발생시키는지 확인**
     1) 사이클이 발생하지 않는 경우 -> 최소 신장 트리에 포함O
     2) 사이클이 발생하는 경우 -> 최소 신장 트리에 포함X
  3) 모든 간선에 대해서 2번의 과정 반복

* 최소 신장 트리에 포함되어 있는 간선의 비용만 모두 더하면, 그 값이 최종 비용에 해당 !

### ⭐️ 코드 분석

```cpp
struct s{
    int v1, v2;
    long long w;
};

struct compare{
    bool operator()(const s& s1, const s& s2){
        return s1.w > s2.w; // 가중치가 작은 것이 우선순위 높게
    }
};


//////////


for(int i=1; i<=V; i++) parent[i] = i;
for(int i=0; i<E; i++){
    cin >> a >> b >> c;
    pq.push({a, b, c});
}

// 가장 작은거 하나는 따로 처리
long long res_weight = pq.top().w; int cnt = 1;
Union(pq.top().v1, pq.top().v2);
pq.pop();

while(1){
    int v1 = pq.top().v1; int v2 = pq.top().v2; int w = pq.top().w; pq.pop();
    if(Find(v1) != Find(v2)){ // 사이클이 발생하지 않은 경우에 대해서만
        Union(v1, v2); 
        res_weight += w; // 최소 신장 트리에 포함하고 가중치 더하기
        cnt++;
    }

    if(cnt == V-1) break; // 포함한 간선의 개수가 (정점-1)개 이면 -> 종료
}
```



### ✔️ 크루스칼 알고리즘의 성능 분석

* 크루스칼 알고리즘은 간선의 개수가 E개일 때, **O(E*logE)** 의 시간복잡도를 가짐
* 크루스칼 알고리즘에서 가장 많은 시간을 요구하는 곳은 간선의 정렬을 수행하는 부분임
  * 표준 라이브러리를 이용해 E개의 데이터를 정렬하기 위한 시간 복잡도는 O(E*logE)