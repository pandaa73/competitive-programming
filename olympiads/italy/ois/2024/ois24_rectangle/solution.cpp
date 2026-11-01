#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

int main() {
    int n; cin >> n;
    vector<ll> v(n);
    for(auto& x: v) cin >> x;

    sort(rall(v));

    ll ans = 0;
    for(int i = 1;; ++i) {
        if(i >= n) { ans = 0; break; }
        if(v[i] == v[i-1]) {
            if(ans == 0) ans = v[i], ++i;
            else {
                ans *= v[i];
                break;
            }
        }
    } cout << ans << endl;
}