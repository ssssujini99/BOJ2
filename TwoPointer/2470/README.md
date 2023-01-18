## 두 용액 🧪

* 핵심: 입력된 용액들 중 서로 다른 두 개의 용액을 혼합하여 0에 가장 가까운 두 용액을 찾는 것   


1. 먼저 입력된 용액들을 정렬시킨다.
2. 두 포인터를 설정한다
   1. left : 왼쪽 포인터
   2. right : 오른쪽 포인터
3. 그리고 두 용액을 기록해야하므로, 기록해야 할 두 용액도 변수로 기록한다.
   1. r_l : 좌 용액
   2. r_r : 우 용액
   3. r_s : 용액 합


4. 초기 세팅은 다음과 같다.
```cpp
ll left = 0; ll right = v.size()-1;
ll r_l = v[0], r_r = v[v.size()-1], r_s = v[left] + v[right];
```

5. 두 포인터를 이동시켜 0에 가장 가까운 두 용액을 찾는 핵심 과정은 다음과 같다.
```cpp
    while(left < right) {
        if(v[left] + v[right] == 0) { // 바로 정답인 경우 -> 기록 후 탈출
            r_l = v[left]; r_r = v[right]; break;
        }

        if(abs(v[left] + v[right]) < abs(r_s)) { // 값을 갱신해야 할 경우 -> 갱신값으로 갱신
            r_l = v[left]; r_r = v[right]; r_s = v[left] + v[right];
        }
        
        // 포인터 이동
        if(v[left] + v[right] > 0) right—;
        else left++;
    }

```