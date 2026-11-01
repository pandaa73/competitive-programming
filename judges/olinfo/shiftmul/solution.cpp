#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(int n, int k, int d, ll a[], ll b[], ll v[]) {
    ll pow = 1;
    ll k2 = 0;
    while(k > 0) {
        if(k&1) {
            for(int i = 0; i < n; ++i) {
                v[i] *= a[(i + (((k2 % n + n) % n) * (ll)(n - d)) % n) % n];
                v[i] %= MOD;
            }

            k2 += pow;
        }

        // cout << "b" << lf;
        for(int i = 0; i < n; ++i) {
            b[i] = a[i] * a[(i + (pow % n) * (n-d)) % n];
            b[i] %= MOD;

            // cout << b[i] << " ";
        }

        // cout << lf;
        swap(a, b);

        k >>= 1;
        pow <<= 1;
    }
}

vector<int> execute(int n, int k, int d, vector<int> sus) {
    ll v[n]; for(auto &x: v) x = 1;
    
    ll a[n]; for(int i = 0; i < n; ++i) a[i] = sus[i];
    ll b[n];

    solve(n, k, d, a, b, v);

    vector<int> ans(n);
    for(int i = 0; i < n; ++i) {
        ans[i] = v[i];
    }

    return ans;
}