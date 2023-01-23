## C++ stl lower_bound, upper_bound 정리


### 1. lower_bound란?
* **```이진 탐색 (binary search) 기반```**의 탐색 방법입니다. (단, 배열 또는 리스트가 **```오름차순으로 정렬```**되어있어야 합니다.)
* **```찾으려는 key값보다 같거나 큰 숫자```**가 **```배열 몇 번째에서 처음 등장```**하는지 찾기 위함입니다. (인덱스를 반환)
* lower_bound의 반환형은 iterator이므로 실제로 몇 번째 인덱스인지 알고싶다면, lower_bound 값에서 배열의 첫 번째 주소를 가리키는 배열의 이름을 빼 주면 됩니다.
* vector의 경우, 벡터.begin()을 빼 주면 됩니다.


#### 예시

* 배열일 경우

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a[10] = {1, 3, 4, 6, 7, 9, 11, 13, 19, 20};

    cout << lower_bound(a, a+10, 6) - a << endl; // 6이 위치한 인덱스인 "3" 반환
    return 0;
}
```   

* 벡터일 경우
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> v = {1, 3, 4, 6, 7, 9, 11, 13, 19, 20};

    cout << lower_bound(v.begin(), v.end(), 6) - v.begin() << endl; // 6이 위치한 인덱스인 "3" 반환
    return 0;
}
```

---

### 2. upper_bound란?
* 마찬가지로 **```이진 탐색 (binary search) 기반```**의 탐색 방법입니다. (단, 배열 또는 리스트가 **```오름차순으로 정렬```**되어있어야 합니다.)
* **```찾으려는 key값을 초과하는 숫자```**가 **```배열 몇 번째에서 처음 등장```**하는지 찾기 위함입니다. (인덱스를 반환)
* upper_bound의 반환형은 iterator이므로 실제로 몇 번째 인덱스인지 알고싶다면, lower_bound 값에서 배열의 첫 번째 주소를 가리키는 배열의 이름을 빼 주면 됩니다.
* vector의 경우, 벡터.begin()을 빼 주면 됩니다.


```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> v = {1, 3, 4, 6, 7, 9, 11, 13, 19, 20};

    cout << upper_bound(v.begin(), v.end(), 6) - v.begin() << endl; // 7이 위치한 인덱스인 "4" 반환
    return 0;
}
```

---

### 3. 활용 예시

#### 💡 오름차순 정렬된 자료에서 "특정 범위에 속하는 숫자"들이 "몇 개" 있는지 탐색하고자 할 때 유용하게 쓰일 수 있습니다.

* 이진 탐색 기반의 lower_bound, upper_bound를 사용하여 **```시간복잡도 O(logN)으로 탐색```**하여 O(N)이 불가능한 경우에 유용하게 쓰일 수 있습니다.


* 예시)
{1, 3, 4, 6, 7, 9, 11, 13, 19, 20} 에서 6 이상 11 이하의 수가 몇 개 인지 구할 때
-> (답) (idx)7 - (idx)3 = 4

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> v = {1, 3, 4, 6, 7, 9, 11, 13, 19, 20};

    cout << upper_bound(v.begin(), v.end(), 11) - lower_bound(v.begin(), v.end(), 6) << endl; // 4 출력
    return 0;
}
```