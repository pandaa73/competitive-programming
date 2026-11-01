#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5;
vector<array<int, 3>> adj[N];

int dijkstra(int n, int t) {
    priority_queue<array<int, 2>> pq; pq.push({0, 0});
    int vis[n]; fill(vis, vis+n, 0);
    while(!pq.empty()) {
        auto [u, v] = pq.top(); pq.pop();

        if(vis[v]) continue;
        if(v == n-1) return -u;

        vis[v] = 1;
        for(auto [d, w, b]: adj[v]) {
            if((b && w-u <= t) || !b) pq.push({u-w, d});
        }
    }

    return -1;
}

int main() {
    int n, m, t; cin >> n >> m >> t;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        int c, e; cin >> c >> e;

        adj[a].push_back({b, c, e});
    }

    cout << dijkstra(n, t) << endl;
}