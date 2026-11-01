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

    #ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int N; cin >> N;

    vec<int> V(N);
    vec<vec<int>> adj(N);
    for(int i = 0; i < N; ++i) {
        int p; cin >> V[i] >> p;

        if(p >= 0) {
            adj[p].emplace_back(i);
        }
    }

    int ans = 0;
    auto dfs = [&](int u, int x, auto &&dfs) -> void {
        ans += V[u] > x;
        x = min(x, V[u]);
        for(auto v: adj[u]) {
            dfs(v, x, dfs);
        }
    };

    dfs(0, V[0] + 1, dfs);

    cout << ans << lf;
}
