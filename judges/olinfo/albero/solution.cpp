#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ld = long double;
using ll = long long;

constexpr int N = 1e5+7;
vector<pair<int, bool>> adj[N];

int dp[N];
void dfs(int v, int f) {
    for(auto [u, i]: adj[v]) {
        if(u == f) {
            dp[v] += !i;
            continue;
        }

        dfs(u, v);
        dp[v] += dp[u];
    }
}

int ans[N], mn = INT_MAX;
void reroute(int v, int up, int f) {
    for(auto [u, _]: adj[v])
        if(u != f) up += dp[u];
    mn = min(mn, ans[v] = up);

    for(auto [u, i]: adj[v])
        if(u != f) reroute(u, !i+up-dp[u], v);
}

int main() {
    int n; cin >> n;
    for(int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back({b, 0});
        adj[b].push_back({a, 1});
    }

    dfs(1, 0);
    reroute(1, 0, 0);

    cout << mn << endl;
    for(int i = 1; i <= n; ++i)
        if(ans[i] == mn) cout << i << " ";
    cout << endl;
}