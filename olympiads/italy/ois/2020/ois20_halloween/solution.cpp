#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int sum[N];
vector<array<int, 2>> adj[N];

void dfs(int v) {
    int sm = 0, mx = 0;

    for(auto [u, w]: adj[v]) {
        dfs(u);

        sum[v] += sum[u];

        sm += w;
        mx = max(mx, w);
    }

    sm -= mx;
    sum[v] += sm;
} 

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, k; cin >> n >> k;

    ll sum = 0;
    ll v[n]; for(auto &x: v) cin >> x, sum += x;

    k %= sum;
    if(k == 0) {
        for(int i = n - 1; i >= 0; i--) {
            if(v[i]) {
                cout << i << lf;
                break;
            }
        }

        return 0;
    }

    for(int i = 0; i < n; ++i) {
        k -= v[i];

        if(k <= 0) {
            cout << i << lf;
            break;
        }
    }
}