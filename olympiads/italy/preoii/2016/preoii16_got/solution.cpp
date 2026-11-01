#include <bits/stdc++.h>
#include <queue>
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

constexpr int INF = 1e9+7;

struct Edge {
    int v;

    ll a;
    ll b;
    ll k;
};

struct Data {
    int v;

    ll d;
    int t;

    bool operator<(const Data &oth) const {
        return this->d > oth.d;
    }
};

int avoid_volunteers(int subtask, int N, int M, int K, int S, int E, int T,
        int A[], int B[], int W[], int P[], int V[]) {

    vector<vector<Edge>> adj(N);
    for(int i = 0; i < M; ++i) {
        adj[A[i]].push_back({B[i], W[i], P[i], V[i]});
        adj[B[i]].push_back({A[i], W[i], P[i], V[i]});
    }

    vector<vector<bool>> vis(N, vector<bool>(K + 1));

    auto check = [&](int m) -> bool {
        for(auto &v: vis) fill(all(v), 0);
        fill(all(vis[S]), 1);
        vis[S][K] = 0;

        priority_queue<Data> q; q.push({S, 0, K});
        while(!q.empty()) {
            auto [v, d, t] = q.top(); q.pop();

            if(v == E) return 1;
            if(vis[v][t]) continue;
            vis[v][t] = 1;

            for(auto [u, a, b, k]: adj[v]) {
                if(k <= m && d + a <= T) q.push({u, d + a, t});
                if(t  > 0 && d + b <= T) q.push({u, d + b, t - 1});
            }
        }

        return 0;
    };

    if(!check(INF)) return -1;

    vector<int> s(M);
    for(int i = 0; i < M; ++i)
        s[i] = V[i];

    sort(rall(s));

    int l = 0, r = M;
    while(r - l > 1) {
        int m = (l + r) / 2;

        if(check(s[m]))
            l = m;
        else r = m;
    }

    return s[l];
}
