#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, int> Node;

long long costruisci(int n, int m, vector<long long>& h, vector<int>& a, vector<int>& b, vector<int>& c) {
    vector<array<int, 2>> adj[n];
    for(int i = 0; i < m; ++i)
        adj[a[i]].push_back({b[i], c[i]});

    priority_queue<Node> pq;
    for(int i = 0; i < n; ++i)
        pq.push({-h[i], i});
    int vis[n]; fill(vis, vis+n, 0);

    long long sum = 0;
    while(!pq.empty()) {
        auto [u, i] = pq.top(); pq.pop();
        if(vis[i]) continue;

        vis[i] = 1;
        sum -= u;

        for(auto [v, w]: adj[i]) {
            pq.push({u-w, v});
        }
    } return sum;
}