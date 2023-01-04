## 1092 - 배 🛳

음 처음에 크레인, 박스 둘 다 내림차순 정렬시킨 후   

```cpp
for(int i=0; i<box.size(); ){
    int j;
    for(j=0; j<crane.size(); j++){
        int k = i+j;
        if(box[k] <= crane[j]) continue;
        else break;
    }
    ans++;
    i += j;
}
```

이렇게 큰 거 기준으로만 했더니 바로 틀려버렸다 ...

https://www.acmicpc.net/board/view/82800

여기서 힌트를 얻었고,   
보니까 작은 것과 큰 것을 함께 옮겨야 하는 상황도 있기 때문이었다. 

예시   
입력   
4   
1 2 3 4   
8   
1 1 2 2 3 3 4 4   

그래서 다시 풀게 되었고,   

```cpp
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
```

둘 다 내림차순 정렬시켰고
크레인을 기준으로 박스를 선택하는 것은 같은데,   
박스를 선택할 때 박스 전체를 돌면서 선택할 수 있는 박스의 최대 무게를 선택해주면 된다.   
(내림차순 정렬시켰으므로 가장 앞에 선택되면 그게 최대 무게임)   


"선택할 수 있는 박스의 최대 무게를 택하는 것" 이 핵심인 것 같다.   

N*M = 50 * 10,000 = 500,000 이므로 시간도 넘지 않는다!