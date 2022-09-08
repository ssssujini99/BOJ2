## Union-Find 알고리즘 (서로소 집합 알고리즘)

* 서로소 집합(Disjoint Sets): 공통 원소가 없는 두 집합

## 서로소 집합 자료구조

* 서로소 부분 집합들로 나누어진 원소들의 데이터를 처리하기 위한 자료구조
* 서로소 집합 자료구조는 두 종류의 연산을 지원함
  * **합집합(Union)**: 두 개의 원소가 포함된 집합을 하나의 집합으로 합치는 연산
  * **찾기(Find)**: 특정한 원소가 속한 집합이 어떤 집합인지 알려주는 연산
* 서로소 집합 자료구조는 합치기 집합(Union Find) 자료구조라고 불림



### ⭐️ 코드 분석

```cpp
// 특정 원소가 속한 집합을 찾기
int Find(int v){
    if(parent[v] == v) return v;
    else return parent[v] = Find(parent[v]); // Find 함수를 최적화하기 위해 경로 압축 이용하기
}

// 두 원소가 속한 집합을 합치기
void Union(int a, int b){
    int parent_a = Find(a);
    int parent_b = Find(b);

    // 더 작은 쪽으로 합침
    if(parent_a < parent_b){
        parent[parent_b] = parent_a;
    }
    else parent[parent_a] = parent_b;
}
```



추가)

### ✔️서로소 집합 자료구조 : ✨경로 압축✨
* 경로 압축 기법을 적용하면 각 노드에 대하여 **찾기(Find) 함수를 호출한 이후에** 해당 노드의 루트 노드가 바로 부모 노드가 됨
* 기본적인 방법에 비하여 시간 복잡도가 개선됨