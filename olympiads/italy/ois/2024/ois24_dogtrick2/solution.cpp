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

    int N, K; cin >> K >> N;

    vector<int> T(K);
    for(auto &x: T) cin >> x, x -= 1;

    vector<bool> vis(N);
    auto dfs = [&](int v, const vector<vector<int>> &adj, vector<int> &ord,
            auto &&dfs) -> void {
        vis[v] = 1;
        for(auto u: adj[v]) {
            if(vis[u]) continue;

            dfs(u, adj, ord, dfs);
        }

        ord.emplace_back(v);
    };

    int M; cin >> M;

    vector<vector<int>> adj(N), radj(N);
    for(int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        u -= 1, v -= 1;

        adj[u].emplace_back(v);
        radj[v].emplace_back(u);
    }

    vector<int> ord; ord.reserve(N);
    vector<int> rord; rord.reserve(N);
    for(int i = 0; i < N; ++i) {
        if(!vis[i]) dfs(i, adj, ord, dfs);
    }

    reverse(all(ord));

    vector<int> scc(N);
    vector<int> in;

    fill(all(vis), 0);
    for(auto i: ord) {
        if(vis[i]) continue;

        int tin = rord.size();
        dfs(i, radj, rord, dfs);

        in.emplace_back(tin);
        for(; tin < rord.size(); ++tin) {
            scc[rord[tin]] = in.size() - 1;
        }
    }

    in.emplace_back(rord.size());

    fill(all(vis), 0);
    auto find = [&](int v, int t, auto &&find) -> bool {
        vis[v] = 1;

        bool ret = 0;
        for(int n = in[v]; n < in[v + 1]; ++n) {
            for(auto u: radj[rord[n]]) {
                ret |= scc[u] == t;
                if(vis[scc[u]]) continue;

                ret |= find(scc[u], t, find);
            }
        }

        return ret;
    };

    for(int i = 0; i < N; ++i) {
        sort(all(adj[i]));
    }

    int score = 2;
    for(int i = 1; i < K; ++i) {
        int u = scc[T[i - 1]];
        int v = scc[T[i]];

        if(u != v && !find(v, u, find)) break;

        auto it = lower_bound(all(adj[T[i - 1]]), T[i]);
        score += 1 + (it != adj[T[i - 1]].end() && *it == T[i]);
    }

    cout << score << lf;
}
