#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;

    vector<array<int, 2>> v(n);
    for(auto &[x, _]: v) cin >> x;
    for(auto &[_, y]: v) cin >> y;

    ll sum = 0, mx = 0, last = 0;
    for(auto &[a, b]: v) {
        if(!b || a < last) {
            mx = max(mx, sum);
            sum = a*b, last = a*b;

            continue;
        }

        sum += a, last = a;
    } 
    
    mx = max(mx, sum);
    
    cout << mx << endl;   
    return 0;
}