#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define ff endl
#define lf "\n"
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<vector<array<ll, 2>>> adj(N);
    for(int i = 0; i < M; ++i) {
        ll u, v, w; cin >> u >> v >> w;

        u--, v--;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<ll> D(N, -1);

    priority_queue<array<ll, 2>> q; q.push({0, N - 1});
    while(!q.empty()) {
        auto [d, v] = q.top(); q.pop();

        if(D[v] >= 0) continue;
        D[v] = -d;

        for(auto [u, w]: adj[v])
            if(D[u] < 0) q.push({d - w, u});
    }

    for(auto &v: adj) {
        sort(all(v), [&](const array<ll, 2> &A, const array<ll, 2> &B) -> bool {
            const auto &[a, _wa] = A;
            const auto &[b, _wb] = B;

            return D[a] > D[b];
        });
    }

    vector<ll> dp(N, -1), nxt(N, -1);
    auto dfs = [&](int v, auto &&dfs) -> void {
        if(dp[v] >= 0) return;
        dp[v] = 0;

        for(auto [u, w]: adj[v]) {
            if(D[v] >= D[u]) break;

            dfs(u, dfs);

            if(dp[v] < dp[u] + w)
                dp[v] = dp[u] + w, nxt[v] = u;
        }
    };

    dfs(N - 1, dfs);

    int v = N - 1;
    vector<int> path = {v + 1};

    while(nxt[v] >= 0)
        path.push_back((v = nxt[v]) + 1);

    reverse(all(path));

    cout << dp[N - 1] _ path.size() << lf;
    for(auto x: path)
        cout << x << " ";
    cout << lf;
}
