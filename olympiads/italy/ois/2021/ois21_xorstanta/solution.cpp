#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int n; cin >> n;
    
    int xb = (1 << (32-__builtin_clz(n)))-1;
    int xa = xb;
    if(n%4 == 0) xa ^= n;
    if(n%4 == 1) xa ^= 1;
    if(n%4 == 2) xa ^= n+1;
    
    cout << xa+xb << endl;
}

int main() {
    int t; cin >> t;
    while(t--) Solve();
}