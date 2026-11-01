#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr int INF = 1e9;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<string> G(N + 2);
    for(int i = 1; i <= N; ++i) {
        G[i].assign(M + 2, '0');
        for(int j = 1; j <= M; ++j) {
            cin >> G[i][j];
        }
    }

    G[    0].assign(M + 2, '0');
    G[N + 1].assign(M + 2, '0');

    vector vis(N + 2, vector<bool>(M + 2));
    auto island_dfs = [&](int i, int j, auto &&island_dfs) -> void {
        if(vis[i][j]) return;
        vis[i][j] = 1;

        for(int dx = -1; dx <= 1; ++dx) {
            for(int dy = -1; dy <= 1; ++dy) {
                if(dx && dy) continue;

                if(G[i + dx][j + dy] == '1') {
                    island_dfs(i + dx, j + dy, island_dfs);
                } else G[i + dx][j + dy] = '0';
            }
        }
    };

    int ans = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            if(vis[i][j]) continue;
            if(G[i][j] != '1') continue;

            ans += 1;
            island_dfs(i, j, island_dfs);
        }
    }

    int n = 0, m = 0;
    vector<pii> edges;
    vector id(N + 2, vector<int>(M + 2, -1));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            if(G[i][j] != '?') continue;

            bool b = (i+j)&1;

            id[i][j] = (b ? n : m)++;

            int u = id[i][j];

            for(int dx = -1; dx <= 1; ++dx) {
                for(int dy = -1; dy <= 1; ++dy) {
                    if(dx && dy) continue;
                    if(!dx && !dy) continue;

                    int v = id[i + dx][j + dy];

                    if(v < 0) continue;

                    if(b) {
                        edges.emplace_back(u, v);
                    } else edges.emplace_back(v, u);
                }
            }
        }
    }

    const int S = n + m;
    const int T = S + 1;

    vector<int> ed; ed.reserve(2 * edges.size());
    vector<vector<pii>> adj(n + m + 2);

    auto add_edge = [&](int u, int v) -> void {
        int i = ed.size();
        int j = i ^ 1;

        ed.emplace_back(1);
        ed.emplace_back(0);

        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, j);
    };

    for(int i = 0; i < n; ++i) {
        add_edge(S, i);
    }

    for(int i = 0; i < m; ++i) {
        add_edge(n + i, T);
    }

    for(int i = 0; i < edges.size(); ++i) {
        add_edge(edges[i].fi, n + edges[i].se);
    }

    vector<int> d(n + m + 2);
    auto bfs = [&](void) -> bool {
        fill(all(d), -1); d[S] = 0;

        queue<int> q; q.emplace(S);
        while(!q.empty()) {
            auto v = q.front(); q.pop();

            for(auto [u, e]: adj[v]) {
                if(d[u] >= 0) continue;
                if(ed[e] == 0) continue;

                d[u] = 1 + d[v];
                q.emplace(u);
            }
        }

        return d[T] >= 0;
    };

    vector<int> nxt(n + m + 2);
    auto dfs = [&](int v, int flow, auto &&dfs) -> int {
        if(v == T) return flow;

        for(int &id = nxt[v]; id < (int)adj[v].size(); ++id) {
            auto [u, e] = adj[v][id];

            if(d[u] <= d[v]) continue;
            if(ed[e] == 0) continue;

            int f = dfs(u, min(flow, ed[e]), dfs);

            if(f == 0) continue;

            ed[e ^ 0] -= f;
            ed[e ^ 1] += f;

            return f;
        }

        return 0;
    };

    int flow = 0;
    while(bfs()) {
        fill(all(nxt), 0);

        while(int f = dfs(S, INF, dfs)) {
            flow += f;
        }
    }

    ans += n + m - flow;

    cout << ans << lf;
}
