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

long long harvest(int N, int M, int K, vector<int>& P, vector<int>& V,
        vector<int>& D, vector<int>& W) {
    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i) {
        adj[P[i]].emplace_back(i);
    }

    vector<vector<pii>> fruits(N);
    for(int i = 0; i < M; ++i) {
        fruits[V[i]].emplace_back(D[i], W[i]);
    }

    auto dfs = [&](int v, auto &&dfs) -> map<int, ll> {
        map<int, ll> dp;
        for(auto u: adj[v]) {
            auto m = dfs(u, dfs);

            if(m.size() > dp.size()) swap(m, dp);

            for(auto [d, w]: m) dp[d] += w;
        }

        for(auto [d, w]: fruits[v]) {
            dp[d] += w;
            ll x = dp[d + 1] -= w;

            auto it = dp.upper_bound(d);
            while(x <= 0 && next(it) != dp.end()) {
                it = dp.erase(it);
                x += it->se;
            }

            it->se = x;
        }

        if(dp.end() != dp.begin()) {
            auto end = prev(dp.end());
            if(end->se <= 0) dp.erase(end);
        }

        infof("Node {}: dp = {}", v, dp);

        return dp;
    };

    auto dp = dfs(0, dfs);

    ll x = 0;
    for(auto [d, w]: dp) x += w;

    return x;
}

#ifdef LOCAL
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;
	vector<int> p(n), v(m), d(m), w(m);
	for (int i = 0; i < n; i++)
		cin >> p[i];
	for (int j = 0; j < m; j++)
		cin >> v[j] >> d[j] >> w[j];

	cout << harvest(n, m, k, p, v, d, w) << "\n";

	return 0;
}
#endif
