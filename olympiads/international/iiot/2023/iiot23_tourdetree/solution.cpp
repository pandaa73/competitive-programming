#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int N = 1e5+3;

vector<array<ll, 2>> adj[N];
int vis[N];

void dfs(int u, ll d, int& x, ll& mx) {
    for(auto [v, w]: adj[u]) {
        if(!vis[v]) vis[v] = 1, dfs(v, d+w, x = (mx > d+w ? x : v), mx = max(mx, d+w));
    }
}

int main() {
    int n, k; cin >> n >> k;

    ll sum = 0;
    for(int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});

        sum += 2*w;
    } 
    
    if(k == 1) {
        cout << sum << endl;
        return 0;
    }

    ll d = 0; 
    int x = 1;
    
    vis[1] = 1;
    dfs(1, 0, x, d); 
    
    fill(vis, vis+n+1, 0);
    
    vis[x] = 1;
    dfs(x, 0, x, d = 0);

    sum -= d; cout << sum << endl;
}