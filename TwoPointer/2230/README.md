## 수 고르기 🔢

> #### 처음에 실패했던 이유
> 해당 수에서 차이가 M이상이면서 제일 작은 수를 그냥 단순히 선형탐색으로 구할 경우,   
> N <= 100,000 이므로 , O(N^2) = O(10^10) 으로 시간초과가 나기 때문!
> 
> ✅ 제발 먼저 코드짜지 말고 기본적인 시간/공간복잡도는 확인을 하자!


> #### 다시 생각해 본 방법
> 
> 시간을 줄여야 한다   
> 근데 정렬을 먼저 시키고, 그 다음 O(N) 으로 특정 수 a를 기준으로 이제 조건에 맞는 b를 골라야 한다.   
> a는 선형탐색으로 쭉 찾아야 함 -> 그렇다면 b를 찾는 과정을 어떻게 줄일까?
> 정렬이 되어있으므로 이분탐색을 활용한다면 logN 만에 b를 구할 수 있음
> 
> 총 시간복잡도는 그럼 N*logN 으로, 충분히 시간 내에 답을 찾을 수 있음!
> 
> 이분탐색 내 투포인터를 이용하여, 답을 구할 수 있었다.



### 핵심 코드
```cpp
    for(int i=0; i<v.size()-1; i++) {
        int l = i+1; int r = v.size()-1;

        while(l <= r) { // 매 for문마다 이분탐색으로 차이가 M이상이면서 가장 작은 수 찾기
            int m = (l+r)/2;

            if(v[m]-v[i] == M) {
                cout << M << endl;
                exit(0);
            }
            else if(v[m]-v[i] >= M && v[m]-v[i] < gap) {
                gap = v[m]-v[i]; // 갱신해야하는 경우 -> 갱신
            }
            else {
            }
            
            // 포인터 이동시키기
            if(v[m]-v[i] > M) {
                r = m - 1;
            }
            else { // v[m] - v[i] < M
                l = m + 1;
            }
        } // while문 끝
        
    }
```


### 👍🏻 추가 다른 풀이

투포인터 문제인데 나는 이분탐색으로 풀어서 다른 사람의 풀이도 가져와봤다.  
와.... 나는 왜 이 생각을 못했을까..   
해당 설명과 코드는 아래 링크를 첨부하였다


```cpp
#include <iostream>
#include <algorithm>
#define INF 2000000000

using namespace std;

int n, target;
int arr[100000];

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);

  cin >> n >> target;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  sort(arr, arr+n);

  int start = 0, end = 0;
  int answer = INF;
  while (start < n && end < n) {
    int result = arr[end] - arr[start];
    if (result < target) {
      end++;
    }
    else {
      answer = min(answer, result);
      start++;
    }
  }
  cout << answer;
}
```

링크 : https://velog.io/@e7838752/BOJ2230