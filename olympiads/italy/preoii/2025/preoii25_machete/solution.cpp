#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int machete(int N, int K, vector<int> P) {
    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i)
        adj[P[i]].push_back(i);

    int ans = 0;

    auto dfs = [&](int v, int d, auto &&dfs) -> int {
        int ret = max(0, d - K + 1);
        for(auto u: adj[v]) {
            int x = dfs(u, d + 1, dfs);

            if(d > 0 && x == d)
                ans++;
            else ret = max(ret, x);
        }

        return ret;
    };

    dfs(0, 0, dfs);

    return ans;
}
