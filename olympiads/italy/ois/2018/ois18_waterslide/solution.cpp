#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+7;
vector<int> adj[N];
int vis[N], w[N];
double dp[N];

void dfs(int v) {
    vis[v] = 1;

    for(auto u: adj[v]) {
        if(!vis[u]) dfs(u);
        dp[v] += dp[u]/(double)w[u];
    }
}

int main() {
    int n, m, k; cin >> n >> m >> k;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        adj[b].push_back(a), ++w[a];
    }

    double mx = 0;
    int idx; dp[0] = 1;
    for(int i = 0; i < k; ++i) {
        dfs(n-i-1);
        if(dp[n-i-1] > mx)
            mx = dp[n-i-1], idx = n-i-1;
    } cout << idx << endl;
}