#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstring>
#include <set>
#include <climits>
using namespace std;

int a[21][21] = {0, };
int N, ans = 0;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int find_max(){
    int res = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(a[i][j] > res) res = a[i][j];
        }
    }

    return res;
}

void move_up(){
    int tmp[21][21] = {0, };

    for(int i=0; i<N; i++){ //// i 증가가 중심
        for(int j=0; j<N; j++){
            int k = i;
            while(k-1 >= 0 && a[k-1][j] == 0) k--;
            if(k != i){
                a[k][j] = a[i][j]; // 칸 이동
                a[i][j] = 0; // 원래 있던 칸은 빈칸으로
            }

            // 합쳐야 하는 경우
            if(k-1 >= 0 && a[k-1][j] == a[k][j] && tmp[k-1][j] == 0){
                tmp[k-1][j] = 1;
                a[k-1][j] *= 2;
                a[k][j] = 0;
            }
        }
    }


}

void move_down(){
    int tmp[21][21] = {0, };

    for(int i=N-1; i>=0; i--){ //// i 감소가 중심
        for(int j=0; j<N; j++){
            int k = i;
            while(k+1 < N && a[k+1][j] == 0) k++;
            if(k != i){
                a[k][j] = a[i][j]; // 칸 이동
                a[i][j] = 0; // 원래 있던 칸은 빈칸으로
            }

            // 합쳐야 하는 경우
            if(k+1 < N && a[k+1][j] == a[k][j] && tmp[k+1][j] == 0){
                tmp[k+1][j] = 1;
                a[k+1][j] *= 2;
                a[k][j] = 0;
            }
        }
    }
}

void move_left(){
    int tmp[21][21] = {0, };

    for(int j=0; j<N; j++){ //// j 증가가 중심
        for(int i=0; i<N; i++){
            int k = j;
            while(k-1 >= 0 && a[i][k-1] == 0) k--;
            if(k != j){
                a[i][k] = a[i][j]; // 칸 이동
                a[i][j] = 0; // 원래 있던 칸은 빈칸으로
            }

            // 합쳐야 하는 경우
            if(k-1 >= 0 && a[i][k-1] == a[i][k] && tmp[i][k-1] == 0){
                tmp[i][k-1] = 1;
                a[i][k-1] *= 2;
                a[i][k] = 0;
            }
        }
    }
}

void move_right(){
    int tmp[21][21] = {0, };

    for(int j=N-1; j>=0; j--){ // j 감소가 중심
        for(int i=0; i<N; i++){
            int k = j;
            while(k+1 < N && a[i][k+1] == 0) k++;
            if(k != j){
                a[i][k] = a[i][j]; // 칸 이동
                a[i][j] = 0; // 원래 있던 칸은 빈칸으로
            }

            // 합쳐야 하는 경우
            if(k+1 < N && a[i][k+1] == a[i][k] && tmp[i][k+1] == 0){
                tmp[i][k+1] = 1;
                a[i][k+1] *= 2;
                a[i][k] = 0;
            }
        }
    }
}

void pri(){
    cout << "\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void dfs(int cnt){
    if(cnt == 5){
        ans = max(ans, find_max());
    }
    else{
        int a_tmp[21][21] = {0, };
        copy(&a[0][0], &a[0][0] + 441, &a_tmp[0][0]);

        move_up();
        dfs(cnt+1);
        swap(a, a_tmp);

        copy(&a[0][0], &a[0][0] + 441, &a_tmp[0][0]);
        move_down();
        dfs(cnt+1);
        swap(a, a_tmp);

        copy(&a[0][0], &a[0][0] + 441, &a_tmp[0][0]);
        move_left();
        dfs(cnt+1);
        swap(a, a_tmp);

        copy(&a[0][0], &a[0][0] + 441, &a_tmp[0][0]);
        move_right();
        dfs(cnt+1);
        swap(a, a_tmp);
    }
}

void deb(){
    cout << "\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> a[i][j];
        }
    }

    dfs(0);

    cout << ans << endl;
    return 0;
}