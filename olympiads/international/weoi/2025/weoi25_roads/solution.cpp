#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

vector<pair<int, int>> orient_roads(int N, int M, vector<int> A,
        vector<int> B, vector<int> W) {
    vector<map<int, ll>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u = A[i], v = B[i], w = W[i];

        adj[u][v] = w;
        adj[v][u] = w;
    }

    vector<int> F(N, INT_MAX);

    priority_queue<array<ll, 3>> q; q.push({0, 0, -1});
    while(!q.empty()) {
        auto [d, v, f] = q.top(); q.pop();

        if(F[v] < INT_MAX) continue;
        F[v] = f;

        for(auto [u, w]: adj[v])
            q.push({d - w, u, v});
    }

    int u = N - 1, v = F[u];
    while(v >= 0) {
        adj[u].erase(v);

        u = v;
        v = F[v];
    }

    fill(all(F), 0);

    auto dfs = [&](int v, auto &&dfs) -> void {
        F[v] = 1;

        for(auto [u, _w]: adj[v]) {
            if(F[u]) continue;

            adj[u].erase(v);

            dfs(u, dfs);
        }
    };

    dfs(N - 1, dfs);

    if(!F[0]) return {};

    vector<pair<int, int>> ed;
    for(int v = 0; v < N; ++v) {
        for(auto [u, _w]: adj[v]) {
            adj[u].erase(v);

            ed.push_back({v, u});
        }
    }

    return ed;
}
