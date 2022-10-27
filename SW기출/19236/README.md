## 백트래킹

* 모든 가능한 경우의 수를 탐색하는 알고리즘

백트래킹은 트리 자료구조에서 그래프 탐색의 변형된 모습이다.   
대부분의 백트래킹 알고리즘은 **깊이 우선 탐색(DFS)**의 형태를 가지고 있다.   
모든 경우의 수를 탐색하는 깊이 우선 탐색과는 다르게,
백트래킹은 유망하지 않다고(non-promising) 판단된 노드는 배제한다.(prunning-가지치기)   
즉, 해당 노드가 유망한지(promising) 검사하여 해가 될 수 있는 경우에만 자식노드를 탐색하는 것이다.   

* 특정한 집합에서 어떤 기준을 만족하는 원소들의 순서를 선택하는 알고리즘

또한 백트래킹은 각 원소들을 **순서대로** 방문(DFS)하면서 기준을 만족하는지(promising) 검사한다.   
따라서 수열이나 조합을 구하는 문제를 푸는 방법이 될 수 있다.   


## 백트래킹 기본 구조

백트래킹의 기본 구조는 다음과 같다.

1. 탈출 조건
2. 유망 함수
   1. 상태 변화
   2. 재귀 호출
   3. 상태 복구


```cpp
void backtracking(int index){
    if(index==n){		// 탈출 조건
        return;
    }
    
    if(isPromising()){ // 유망하다면
        visited[index] = true;	// 상태 변화
        backtracking(index+1);	// 재귀 호출
        visited[index] = false;	// 상태 복구
    }
}

bool isPromising(int index){	// 유망함수
    if(non-promising)
        return false;
    if(promising)
        return true;
}
```