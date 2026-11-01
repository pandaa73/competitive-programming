#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ld = long double;
using ll = long long;

constexpr int K = 1e5+7;
constexpr int N = 1e4+7;
constexpr int MOD = 420;

bool vis[N][MOD];
bool pos[N][MOD];
vector<int> adj[N];

int main() {
    int n, m, k; cin >> n >> m >> k;

    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 0; i < k; ++i) {
        int l; cin >> l;
        int p[l]; for(auto& x: p) cin >> x;
        for(int j = 0; j < MOD; j += l) {
            for(int k = 0; k < l; ++k) pos[p[k]][j+k] = 1;
        }
    }

    if(pos[0][0]) { cout << -1 << endl; return 0; }
    queue<array<ll, 2>> q; q.push({0, 0});
    while(!q.empty()) {
        auto [d, v] = q.front(); q.pop();

        if(v == n-1) {
            cout << d << endl;
            return 0;
        }

        int idx = d%MOD;
        if(vis[v][idx]) continue;
        vis[v][idx] = 1;

        for(auto u: adj[v]) {
            if(!pos[u][(idx+1)%MOD]) q.push({d+1, u});
        } if(!pos[v][(idx+1)%MOD]) q.push({d+1, v});  
    } cout << -1 << endl;
}