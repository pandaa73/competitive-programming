#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int u, v, w; cin >> u >> v >> w;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<array<bool, 3>> V(N);
    for(int i = 0; i < 3; ++i) {
        int M, x; cin >> M;
        while(M--) {
            cin >> x;
            V[x][i] = 1;
        }
    }

    vector<array<int, 3>> sz(N);
    auto dfs = [&](int v, int f, auto &&dfs) -> void {
        for(int i = 0; i < 3; ++i) {
            sz[v][i] = V[v][i];
        }

        for(auto u: adj[v]) {
            if(u == f) continue;

            dfs(u, v, dfs);

            for(int i = 0; i < 3; ++i) {
                sz[v][i] += sz[u][i];
            }
        }

        infof("{}: sz = {}", v, sz[v]);
    };

    dfs(0, -1, dfs);

    vector<ll> ans(N);
    auto reroot = [&](int v, int f, array<int, 3> up, auto &&reroot) -> void {
        infof("===== reroot({}, {}, {}) =====", v, f, up);

        ll A = 0, B = 0, C = 0;
        ll AB = 0, AC = 0, BC = 0;

        for(auto u: adj[v]) {
            auto [a, b, c] = u == f ? up : sz[u];

            ans[v] += c * AB;
            ans[v] += b * AC;
            ans[v] += a * BC;

            AB += A * b + a * B;
            AC += A * c + a * C;
            BC += B * c + b * C;

            A += a, B += b, C += c;
        }

        ans[v] += BC * V[v][0];
        ans[v] += AC * V[v][1];
        ans[v] += AB * V[v][2];

        ans[v] += A * V[v][1] * V[v][2];
        ans[v] += B * V[v][0] * V[v][2];
        ans[v] += C * V[v][0] * V[v][1];

        ans[v] += V[v][0] * V[v][1] * V[v][2];

        A += V[v][0], B += V[v][1], C += V[v][2];

        infof("A = {} | B = {} | C = {}", A, B, C);
        infof("AB = {} | AC = {} | BC = {}", AB, AC, BC);

        for(auto u: adj[v]) {
            if(u == f) continue;

            auto [a, b, c] = sz[u];

            reroot(u, v, {(int)A - a, (int)B - b, (int)C - c}, reroot);
        }
    };

    reroot(0, -1, {0, 0, 0}, reroot);

    for(auto x: ans) {
        cout << x << " ";
    }

    cout << lf;
}
