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

int pianifica(int N, int L, vector<vector<int>> F) {
    vector<vector<int>> dist(L);
    vector<vector<array<int, 2>>> V(N);

    for(int i = 0; i < L; ++i) {
        const int K = F[i].size();
        dist[i].resize(K, INT_MAX);

        for(int j = 0; j < K; ++j)
            V[F[i][j]].push_back({i, j});
    }

    deque<array<int, 2>> q;
    for(auto [i, j]: V[0])
        q.push_front({i, j}), dist[i][j] = 0;

    while(!q.empty()) {
        auto [i, j] = q.front(); q.pop_front();

        if(dist[i][j] < 0) continue;
        int d = dist[i][j];

        dist[i][j] = -1;

        if(F[i][j] == N - 1) return d;

        if(j + 1 < F[i].size() && dist[i][j + 1] > d)
            q.push_front({i, j + 1}), dist[i][j + 1] = d;

        d++;
        for(auto [ni, nj]: V[F[i][j]])
            if(dist[ni][nj] > d)
                q.push_back({ni, nj}), dist[ni][nj] = d;
        V[F[i][j]].clear();
    }

    return -1;
}
