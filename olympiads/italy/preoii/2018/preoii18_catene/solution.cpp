#include <bits/stdc++.h>
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

long long profitto_massimo(int N, int U[], int V[], int W[]) {
    vector<vector<pll>> adj(N);
    for(int i = 0; i < N - 1; ++i) {
        U[i] -= 1, V[i] -= 1;
        W[i] = max(W[i], 0);

        adj[U[i]].emplace_back(V[i], W[i]);
        adj[V[i]].emplace_back(U[i], W[i]);
    }

    vector<pll> dp(N);
    auto dfs = [&](int v, int f, auto &&dfs) -> void {
        vector<pll> a; a.reserve(adj[v].size());
        for(auto [u, w]: adj[v]) {
            if(u == f) continue;

            dfs(u, v, dfs);

            a.emplace_back(dp[u].fi, dp[u].se + w);

            dp[v].fi += dp[u].fi;
        }

        sort(all(a), [&](const pll &x, const pll &y) -> bool {
            return x.se - x.fi > y.se - y.fi;
        });

        if(a.size() >= 1) {
            dp[v].fi += max(0LL, a[0].se - a[0].fi);
        }

        dp[v].se = dp[v].fi;

        if(a.size() >= 2) {
            dp[v].fi += max(0LL, a[1].se - a[1].fi);
        }

        infof("... %d: dp = {%d, %d}", v, dp[v].fi, dp[v].se);
    };

    dfs(0, -1, dfs);

    return dp[0].fi;
}

#ifdef LOCAL
int main(){
    int n;
    FILE *in = stdin, *out = stdout;
    assert(fscanf(in, "%d", &n) == 1);

    int *u = (int*)calloc(n-1, sizeof(int));
    int *v = (int*)calloc(n-1, sizeof(int));
    int *w = (int*)calloc(n-1, sizeof(int));

    for(int i=0; i<n-1; i++)
      assert(fscanf(in, "%d%d%d", u + i, v + i, w + i) == 3);

    long long answ = profitto_massimo(n, u, v, w);
    fprintf(out, "%lld\n", answ);

    free(u);
    free(v);
    free(w);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
#endif
