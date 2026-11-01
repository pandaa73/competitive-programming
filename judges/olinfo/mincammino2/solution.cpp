#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

void mincammino(int N, int M, vector<int> X, vector<int> Y,
   vector<int> P, vector<long long>& D) {
    vector<vector<array<int, 2>>> adj(N);

    for(int i = 0; i < M; ++i) 
        adj[X[i]].push_back({Y[i], P[i]});

    new (&D) vector<ll>(N, -1);

    priority_queue<array<ll, 2>> pq; pq.push({0, 0});
    while(!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
    
        if(D[v] >= 0) continue;
        D[v] = -d;

        for(auto [u, w]: adj[v])
            pq.push({d - w, u});
    }
}
