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

    int N, M; cin >> N >> M;
    int A, B; cin >> A >> B;

    vec<vec<int>> adj(N);
    for(int e = 0; e < M; ++e) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int c = 0;
    vec<bool> vis(N);
    auto dfs = [&](int u, auto &&dfs) -> void {
        vis[u] = 1;

        for(auto v: adj[u]) {
            if(vis[v]) continue;

            dfs(v, dfs);
        }
    };

    for(int n = 0; n < N; ++n) {
        if(!vis[n]) {
            c += 1;
            dfs(n, dfs);
        }
    }

    cout << (ll)(c - 1) * A + (ll)(M + c - N) * B << lf;
}
