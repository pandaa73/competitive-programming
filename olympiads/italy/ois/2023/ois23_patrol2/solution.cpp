#include <bits/stdc++.h>
#include <queue>
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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    vector<vector<int>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> P(K);
    for(auto &x: P) cin >> x;

    vector<int> D(N, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> q;
    D[0] = 0; q.emplace(0, 0);

    int ans = -1;
    while(!q.empty()) {
        auto [d, v] = q.top(); q.pop();

        if(D[v] != d) continue;
        if(v == N - 1) {
            ans = d;
            break;
        }

        for(auto u: adj[v]) {
            int e = d + 1;
            if(P[e % K] == u) e += 1;

            if(D[u] <= e) continue;

            D[u] = e;
            q.emplace(e, u);
        }
    }

    cout << ans << lf;
}
