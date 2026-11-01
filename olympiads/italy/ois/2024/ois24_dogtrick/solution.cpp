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

template<typename T>
void chmax(T &a, T b) {
    a = max(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<int> T(N);
    for(auto &x: T) cin >> x, x -= 1;
    T.emplace_back(K);

    int M; cin >> M;

    vector<vector<int>> adj(K + 1);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
    }

    for(auto &v: adj) sort(all(v));

    auto find = [&](int u, int v) -> bool {
        auto it = lower_bound(all(adj[u]), v);
        return it != adj[u].end() && *it == v;
    };

    vector<int> dp(N + 1);
    dp[N - 1] = T[N - 1] < K;
    dp[N - 2] = T[N - 2] < K;

    for(int i = N - 2; i >= 0; i--) {
        if(find(T[i], T[i + 1])) chmax(dp[i], dp[i + 1] + 1);
        if(find(T[i], T[i + 2])) chmax(dp[i], dp[i + 2] + 1);

        if(dp[i] + dp[i + 1] == 0) break;
    }

    cout << max(dp[0], dp[1]) << lf;
}
