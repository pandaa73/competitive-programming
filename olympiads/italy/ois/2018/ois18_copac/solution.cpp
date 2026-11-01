#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vec<vec<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vec<int> ans;

    vec<int> sz(N);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        sz[u] = 1;
        int mx = 0;
        for(auto v: adj[u]) {
            if(v == p) continue;

            dfs(v, u, dfs);

            sz[u] += sz[v];
            mx = max(mx, sz[v]);
        }

        mx = max(mx, N - sz[u]);

        if(mx <= N / 2) {
            ans.emplace_back(u);
        }
    };

    dfs(0, N, dfs);

    sort(all(ans));
    for(auto x: ans) {
        cout << x + 1 << lf;
    }
}
