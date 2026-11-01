#include <bits/stdc++.h>
using namespace std;

#define _ << " " <<
#define lf "\n"

using ll = long long;

constexpr int N = 3e5+7;

vector<array<int, 2>> adj[N];

bool vis[N];
ll dist[N];
int f[N];
int f2[N];

ll viaggia(int n, int m, vector<int> a, vector<int> b,
   vector<int> t, vector<int> vsus, vector<int> wsus) {
    for(int i = 0; i < m; ++i) {
        adj[b[i]].push_back({a[i], t[i]});
    }

    priority_queue<array<ll, 3>> pq; pq.push({0, n - 1, -1});
    while(!pq.empty()) {
        auto [d, v, fa] = pq.top(); pq.pop();

        if(vis[v]) continue;
        dist[v] = -d;
        vis[v] = 1;
        f[v] = fa;

        if(fa != -1) {
            if(vsus[fa] == -1)
                f2[v] = f2[fa];
            else f2[v] = fa;
        } else f2[v] = n - 1;

        for(auto [u, w]: adj[v]) {
            pq.push({d - w, u, v});
        }
    }

    memset(vis, 0x00, sizeof(vis));

    ll ans = 0;
    int curr = 0;
    while(f[curr] != -1) {
        if(!vis[curr] && vsus[curr] != -1) {
            vis[curr] = 1;
            ans += wsus[curr];
            curr = vsus[curr];

            continue;
        }

        ans += dist[curr] - dist[f2[curr]];
        int sus = f2[curr];
        f2[curr] = f2[f2[curr]];
        curr = sus;
    }

    return ans;
}