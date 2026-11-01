#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

constexpr int N = 1e5+7;

vector<array<ll, 2>> adj[N];
ll d1[N], d2[N];

bool shrt[N];
bool v1[N], v2[N];

void dijkstra(ll dist[], bool vis[], int src) {
    memset(dist, 0xff, sizeof(ll)*N);

    priority_queue<array<ll, 2>> pq; pq.push({0, src});

    while(!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();

        if(vis[v]) continue;
        vis[v] = 1;
        dist[v] = -d;

        for(auto [u, w]: adj[v]) {
            pq.push({d-w, u});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;

        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    dijkstra(d1, v1, 0);
    dijkstra(d2, v2, n-1);

    vector<ll> paths[n];
    ll shpth = LLONG_MAX, ans = LLONG_MAX;
    for(int v = 0; v < n; ++v) {
        for(auto &[u, w]: adj[v]) {
            paths[v].push_back(min(w+d1[v]+d2[u], w+d2[v]+d1[u]));

            if(d1[v] == -1 || d2[u] == -1) paths[v].back() = LLONG_MAX;
            shpth = min(shpth, paths[v].back());
        }
    }

    for(int v = 0; v < n; ++v) {
        int idx = 0;
        for(auto &[u, w]: adj[v]) {
            if(paths[v][idx] == shpth)
                shrt[v] = shrt[u] = 1;

            ++idx;
        }
    }

    for(int v = 0; v < n; ++v) {
        int idx = 0;
        for(auto &[u, w]: adj[v]) {
            if(shrt[u] && shrt[v]) goto inc;
            if(1 + paths[v][idx] - w < shpth)
                ans = min(ans, 1+paths[v][idx]-shpth);
inc:
            ++idx;
        }
    }

    cout << (ans == LLONG_MAX ? -1 : ans) << endl;
}