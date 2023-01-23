## 팀 빌딩 👬

> ### Key point
> 변하는 값은 다음과 같다.   
> 1 - min(A, B) -> 계속 값이 변함   
> 2 - A와 B 사이 간격 -> 계속 값이 변함

1. 모든 경우의 수를 확인하기 -> O(N^2)
   1. 위의 방법은 N = 10^5 이므로 시간초과가 날 수 있음
   2. 1번의 방법은 시간초과가 날 수 있기 때문에 두 변수(값이 변하는 수) 중 하나의 값을 통제할 수 있어야 한다.
      1. min(A, B)는 계속 변하므로 (심지어 정렬되어 있지도 않고, 정렬을 시킬수도 없음) 이 변수는 통제하기가 어렵다.
      2. **⭐️ A와 B 사이 간격은 내가 직접 늘리거나 줄일 수 있다. ⭐️**
   

2. 특정 변수의 값 하나 통제하기 -> [A와 B 사이의 간격을 통제하자]
   1. A와 B 사이의 개발자 수를 계속 늘리게 조절하는 경우, 시작 지점을 어디로 잡을 지 애매함
      1. 만약 잡았다고 하더라도 명확하게 설명할 수 없다.
   2. **⭐️A와 B사이의 개발자 수를 계속 줄이는 경우 -> 양 끝에서 시작해서 점점 줄이는 방법 하나만 존재⭐️**
      1. **이를 투포인터를 이용하여 설계하기**