## 사고의 흐름 과정 정리

### 최장 증가 부분 수열(LIS 알고리즘) with O(NlogN)


> DP에서의 O(N^2)의 시간복잡도를 O(NlogN) 까지 개선해보기   
> * DP에서의 시간을 더 축소시키는 그리디 알고리즘


* sol1.cpp -> multiset 이용해 검색을 logN으로 수행
  * 총 시간복잡도: O(NlogN)

* sol2.cpp -> 이진탐색을 직접 구현하여 검색을 logN으로 수행
  * 총 시간복잡도: O(NlogN)


### 📝 아이디어 및 생각 정리

* 상한, 하한의 lower_bound, upper_bound는 **logN**의 시간복잡도로 구할 수 있다
* 굳이 lower_bound, upper_bound 함수를 쓰지 않고 직접 **이진탐색**으로 구현해서 logN으로 구할 수도 있다
  * -> sol2.cpp
  * 시험에서는 웬만하면 있는 거 갖다 쓰자!


[참고링크]
* https://www.youtube.com/watch?v=i4NBDE8ZEV8
* https://jason9319.tistory.com/113