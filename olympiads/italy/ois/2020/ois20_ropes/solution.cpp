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

    int n; cin >> n;
    int f[n]; for(auto &x: f) cin >> x;
    int k[n]; for(auto &x: k) cin >> x;

    for(int i = 0; i < n; ++i)
        adj[f[i]].push_back({i + 1, k[i]});

    dfs(0);

    cout << sum[0] << lf;
}