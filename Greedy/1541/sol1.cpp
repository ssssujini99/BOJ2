#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstring>
#include <set>
#include <sstream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> numbers;
    string line; cin >> line;
    string op = ""; string tmp;

    for(int i=0; i<line.size(); i++){
        if(line[i] == '+' || line[i] == '-'){
            op += line[i];
            line[i] = ' ';
        }
    }


    stringstream sstream(line);

    while(getline(sstream, line, ' ')){
        numbers.push_back(stoi(line));
    }

    int sum = numbers[0]; int del = 0;
    int flag = 0;
    for(int i=0; i<op.size(); i++){
        if(flag == 0 && op[i] == '+') sum += numbers[i+1];
        else{
            flag = 1;
            del += numbers[i+1];
        }
    }

    cout << sum - del << endl;
    return 0;
}