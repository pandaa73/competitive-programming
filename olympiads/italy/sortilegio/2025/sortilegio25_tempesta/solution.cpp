// @check-accepted: examples adjacent line nearly_line quadratic no_limits
#include <vector>
#include <queue>
using namespace std;

using ll = long long;

long long atterra(int N, vector<int> U, vector<int> V) {
    vector<vector<int>> adj(N);
    for(int i = 0; i < N - 1; ++i) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }

    queue<int> q;
    vector<int> path;
    vector<ll> dist(N, -1);

    auto dfs = [&](int v, int f, auto &&dfs) -> bool {
        bool b = v == N - 1;

        for(auto u: adj[v]) {
            if(b) break;
            if(u == f) continue;

            b |= dfs(u, v, dfs);
        }

        if(!b) return 0;

        for(auto u: adj[v]) {
            if(u == f) continue;
            if(!path.empty() && u == path.back()) continue;

            q.push(u);
            dist[u] = 0;
        }

        path.push_back(v);

        return 1;
    };

    dfs(0, -1, dfs);

    if(path.size() == N) return -1;

    while(!q.empty()) {
        auto v = q.front(); q.pop();

        for(auto u: adj[v]) {
            if(dist[u] >= 0) continue;

            q.push(u);
            dist[u] = 1 + dist[v];
        }
    }

    ll ans = 0;
    for(auto x: path)
        ans += dist[x];

    return ans;
}
