#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int mult[15] = {
    1, 2, 5, 10, 20, 50, 100, 200, 500, 
    1000, 2000, 5000, 10000, 20000, 50'000
};

int main() {
    ll sum = 0, x;
    for(int i = 0; i < 15; ++i)
        cin >> x, sum += x*mult[i];
    
    ll v[15];
    for(int i = 15; i > 0; i--) 
        v[i-1] = sum/mult[i-1], sum %= mult[i-1];

    for(auto x: v) cout << x << " ";
}