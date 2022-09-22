## 사고의 흐름 과정 정리


* 0인 칸들 중에서 벽 3개 고르기 -> **조합**
* 해당 벽 3개를 세우고 바이러스 퍼뜨리기 -> **BFS**
* 안전영역 구하기 -> **단순 반복문**


> 정리: 단계별로 잘 나누고, 해당 조건에 잘 풀면 어렵지 않은 문제인 것 같다.


* sol1, sol2 -> 직접 푼 맞는 풀이
* sol3 ~ -> 기타 해답 풀이


## ✔️ 기록하고 기억해야 할 부분만 정리

* 조합 -> next permutation + do - while 반복문 이용하기

```cpp
    // 조합 돌릴 준비
    for(int i=0; i<3; i++) comb.push_back(1);
    for(int i=0; i<zero.size()-3; i++) comb.push_back(0);
    sort(comb.begin(), comb.end()); // 조합 돌리기 전 정렬시키기

    do{
        // 배열 복사
        copy(&a[0][0], &a[0][0]+64, &a_copy[0][0]); // 2차원 배열 복사

        // 벽 3개 세우기
        for(int i=0; i<comb.size(); i++){
            if(comb[i] == 1){
                a_copy[zero[i].x][zero[i].y] = 1; // 벽 3개 세우기
            }
        }

        // 바이러스 퍼뜨리기
        bfs();

        // 안전영역 구하기
        int safe_place = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(a_copy[i][j] == 0) safe_place++;
            }
        }
        // 답 갱신
        res = max(res, safe_place);
    } while (next_permutation(comb.begin(), comb.end()));
    // 조합 끝
```

* 2차원 배열 복사 -> copy 함수 이용하기

```cpp
        // 배열 복사 (배열 a를 -> aa 에 복사하기)
        copy(&a[0][0], &a[0][0]+64, &a_copy[0][0]); // 2차원 배열 복사
```