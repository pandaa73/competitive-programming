#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

void solve(void) {
    int N, M; cin >> N >> M;
    int S, T; cin >> S >> T;
    if(S > T) swap(S, T);

    vector<vector<pii>> adj(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        char w; cin >> w; w -= 'a';

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    set<array<int, 3>> vis;

    queue<array<int, 5>> q; q.push({S, -1, T, -1, 0});

    int ans = INT_MAX;
    while(!q.empty()) {
        auto [u, a, v, b, d] = q.front(); q.pop();
        if(d > ans) break;

        if(a != b) continue;
        if(u > v) swap(u, v);

        array<int, 3> k = {u, v, a};
        if(vis.count(k)) continue;
        vis.insert(k);

        if(u == v) {
            ans = min(ans, d);
            continue;
        }

        for(auto [x, n]: adj[u]) {
            if(x == v) {
                ans = min(ans, d + 1);
                break;
            }

            for(auto [y, m]: adj[v]) {
                q.push({x, n, y, m, d + 2});
            }
        }
    }

    if(ans == INT_MAX) ans = -1;

    static int t = 1;
    cout << "Case #" << t++ << ":" _ ans << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
