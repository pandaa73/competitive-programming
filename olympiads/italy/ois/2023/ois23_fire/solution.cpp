#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5+3;
vector<int> adj[N];
int mx[N], dp[N];
int ans[N];

void dfs(int v, int f) {
    dp[v] = 1;

    for(auto u: adj[v]) {
        if(u == f) continue;
        dfs(u, v);
        
        if(dp[u] > mx[v]) {
            dp[v] += mx[v];
            mx[v] = dp[u];
        } else dp[v] += dp[u];
    }
}

void reroute(int v, int up, int f) {
    int sum = 1+up, mx1 = up, mx2 = 0;
    for(auto u: adj[v]) {
        if(u == f) continue;
        if(dp[u] > mx1) mx2 = mx1, mx1 = dp[u];
        else if(dp[u] > mx2) mx2 = dp[u];

        sum += dp[u];
    } ans[v] = sum-mx1;

    for(auto u: adj[v]) {
        if(u == f) continue;

        int down = sum-mx1;
        if(dp[u] == mx1) down -= mx2;
        else down -= dp[u];

        reroute(u, down, v);
    }
}

int main() {
    int n; cin >> n;
    for(int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    } 
    
    dfs(0, -1); 
    reroute(0, 0, -1);

    for(int i = 0; i < n; ++i)
        cout << ans[i] << " ";
}