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

    vec<vec<pii>> adj(N);
    for(int i = 1; i < N; ++i) {
        char c; int p; cin >> c >> p;

        adj[p].emplace_back(i, c == 'P' ? 1 : c == 'N' ? 2 : 3);
    }

    vec<int> d(N);
    auto dfs = [&](int u, auto &&dfs) -> void {
        for(auto [v, w]: adj[u]) {
            d[v] = d[u] + w;
            dfs(v, dfs);
        }
    };

    dfs(0, dfs);

    cout << *max_element(all(d)) << lf;
}
