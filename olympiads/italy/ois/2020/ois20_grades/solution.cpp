#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    int v[n]; for(auto &x: v) cin >> x;

    int l = -1, r = -1;
    for(int i = 0; i < n; ++i) {
        if(l == -1) {
            if(v[i] < 6) l = i;
        } else if(v[i] >= 6) r = i;
    }

    if(r == -1) cout << -1 << lf; 
    else cout << r - l + 1 << lf;
}