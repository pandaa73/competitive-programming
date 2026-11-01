#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

vector<ll> calcola(int n, int m, vector<ll> c, vector<ll> p) {
    array<ll, 2> pfx[n+1]; pfx[0] = {0, c[0]};
    for(int i = 1; i < n; ++i) {
        pfx[i] = pfx[i-1];
        pfx[i][0] += c[i] * ll(i);
        pfx[i][1] += c[i];

        assert(pfx[i][0] >= 0);
    }

    vector<ll> ans(m);
    for(int i = 0; i < m; ++i) {
        int l = 0, r = n;
        while(r - l > 1) {
            int m = (l + r) / 2;

            if(p[i] >= pfx[m][0])
                l = m;
            else r = m;
        }

        ans[i] = pfx[l][1];

        ll lft = p[i] - pfx[l][0];
        if(l+1 < n) ans[i] += min(lft / (l+1), c[l+1]); 
    }

    return ans;
}