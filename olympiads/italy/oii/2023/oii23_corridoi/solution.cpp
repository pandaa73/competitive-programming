#include <bits/stdc++.h>
#include <filesystem>
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

constexpr ll INF = 1e15+7;

vector<long long> shorten(int N, int M, int Q, vector<long long> K,
        vector<int> A, vector<int> B, vector<int> C) {
    vector<vector<array<ll, 2>>> adj(N);
    for(int i = 0; i < M; ++i) {
        adj[A[i]].push_back({B[i], C[i]});
        adj[B[i]].push_back({A[i], C[i]});
    }

    auto dijkstra = [&](int src, vector<ll> &dist) -> void {
        priority_queue<array<ll, 2>> q; q.push({0, src});

        while(!q.empty()) {
            auto [d, v] = q.top(); q.pop();

            if(dist[v] >= 0) continue;
            dist[v] = -d;

            for(auto [u, w]: adj[v])
                q.push({d - w, u});
        }
    };

    vector dist(3, vector<ll>(N, -1));

    dijkstra(0, dist[0]);
    dijkstra(1, dist[1]);
    dijkstra(2, dist[2]);

    vector<array<ll, 2>> V(N);
    for(int i = 0; i < N; ++i) {
        ll d0 = dist[0][i];
        ll d1 = dist[1][i];
        ll d2 = dist[2][i];

        V[i] = {d1, d0 + d2};
    }

    sort(all(V), [&](const array<ll, 2> &a, const array<ll, 2> &b) -> bool {
        ll x = 2 * a[0] + a[1];
        ll y = 2 * b[0] + b[1];

        if(x == y)
            return a[0] < b[0];
        return x < y;
    });

    auto calc = [](const array<ll, 2> &v, ll k) -> ll {
         ll x = min(v[0], k);

         return 2 * (v[0] - x) + v[1] - min(v[1], k - x);
    };

    infos("-------------");
    infor("V [%d]:", V.size());
    for(auto [x, y]: V)
        infor(" (%lld, %lld)", x, y);
    infos("");

    vector<ll> W;
    vector<array<ll, 2>> V2;
    for(int i = 0; i < N; ++i) {
        while(!W.empty() && calc(V2.back(), W.back()) >= calc(V[i], W.back()))
            W.pop_back(), V2.pop_back();

        if(W.empty()) {
            W.push_back(0);
            V2.push_back(V[i]);
            continue;
        }

        ll l = W.back(), r = V[i][0] + V[i][1] + 1;
        while(r - l > 1) {
            ll m = (l + r) / 2;

            ll a = calc(V2.back(), m);
            ll b = calc(V[i], m);

            if(a < b)
                l = m;
            else r = m;
        }

        if(l == V[i][0] + V[i][1]) continue;

        W.push_back(l + 1);
        V2.push_back(V[i]);
    }

    infos("-------------");
    infor("W [%d]:", W.size());
    for(auto x: W)
        infor(" %lld", x);
    infos("");
    infor("V2 [%d]:", V2.size());
    for(auto [x, y]: V2)
        infor(" (%lld, %lld)", x, y);
    infos("");

    vector<ll> ans; ans.reserve(Q);
    for(auto k: K) {
        auto it = upper_bound(all(W), k);

        assert(it != W.begin());
        it = prev(it);

        ans.push_back(calc(V2[it - W.begin()], k));
    }

    return ans;
}
