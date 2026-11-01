#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infof

#define infos(str)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 21;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 3e5+7;

using adj_t = vector<vector<array<int, 2>>>;

struct Query {
    int a, b, q;
};

vector<int> ans(MAXN);

int col[MAXN];
bool intr[MAXN];
Query Qs[MAXN];
int cioc[LOG][MAXN];
vector<array<int, 2>> adj[LOG][MAXN];

inline int compress(const int n, const int d, int &rm) {
    auto &cioc1 = cioc[d], &cioc2 = cioc[d + 1]; 
    auto &adj1 = adj[d], &adj2 = adj[d + 1];

    memset(col, 0xff, n * sizeof(int));
    for(int i = 0; i < n; ++i) adj2[i].clear();

    int sz = 0;
    auto dfs = [&](int v, int f, auto &&dfs) -> array<int, 2> {
        vector<array<int, 2>> subt;

        int mx = 0;
        for(auto [u, w]: adj1[v]) {
            if(u == f) continue;

            auto ret = dfs(u, v, dfs);

            ret[1] = max(ret[1], w);

            if(ret[0] >= 0) {
                subt.push_back(ret);

                continue;
            }

            mx = max(mx, ret[1]);
            rm = max(rm, ret[1]);
        }

        if(subt.size() + intr[v] <= 1) {
            if(!subt.empty())
                return {subt[0][0], max(subt[0][1], cioc1[v])};
            if(!intr[v])
                return {-1, max(mx, cioc1[v])};

            col[v] = sz++;
            cioc2[col[v]] = cioc1[v];

            return {v, 0};
        }

        col[v] = sz++;
        cioc2[col[v]] = cioc1[v];
        for(auto [u, w]: subt) {
            adj2[col[u]].push_back({col[v], w});
            adj2[col[v]].push_back({col[u], w});
        }

        return {v, 0};
    };

    rm = max(rm, dfs(0, -1, dfs)[1]);

    return sz;
}

void solve(int l, int r, const int n, const int d, int rm) {
    auto &adj1 = adj[d];

    memset(intr, 0x00, n * sizeof(bool));
    for(int i = l; i < r; ++i)
        intr[Qs[i].a] = intr[Qs[i].b] = 1;

    int sz = compress(n, d, rm);

    if(r - l == 1) {
        ans[l] = rm;

        return;
    }

    for(int i = l; i < r; ++i)
        Qs[i].a = col[Qs[i].a], Qs[i].b = col[Qs[i].b];

    int m = (l + r) / 2;

    solve(l, m, sz, d + 1, rm);
    solve(m, r, sz, d + 1, rm);
}

vector<int> raccogli(int N, int Q, vector<int> &A, vector<int> &B,
        vector<int> &C, vector<int> &L, vector<int> &T) {
    for(int i = 0; i < N - 1; ++i) {
        adj[0][A[i]].push_back({B[i], 0});
        adj[0][B[i]].push_back({A[i], 0});
    }

    for(int i = 0; i < N; ++i)
        cioc[0][i] = C[i];

    for(int i = 0; i < Q; ++i)
        Qs[i] = {L[i], T[i], i};

    int rm = 0;
    solve(0, Q, N, 0, rm);

    ans.resize(Q);
    return ans;
}
