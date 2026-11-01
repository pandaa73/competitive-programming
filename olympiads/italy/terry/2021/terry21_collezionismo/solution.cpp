#include <bits/stdc++.h>
using namespace std;
// flag[10]

int Solve() {
    int n, k; cin >> n >> k;
    if(n == k) return 0;
    int v[n], mx = INT_MIN, mn = INT_MAX; 
    for(auto& x: v) {
        cin >> x;
        mx = max(mx, x);
        mn = min(mn, x);
    } sort(v, v+n);

    int d[n-1]; 
    for(int i = n-1; i > 0; i--) {
        d[i-1] = v[i-1]-v[i];
    } sort(d, d+n-1);

    int ans = mx-mn;
    for(int i = 0; i < k-1; ++i) ans += d[i];

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t; cin >> t;
    for(int i = 0; i < t; ++i) {
        int x = Solve();
        cout << "Case #" << i+1 << ": " << x << "\n";
    }
}