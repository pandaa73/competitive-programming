#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

constexpr int N = 1e6+7;

bool vis[N];
vector<array<int, 2>> adj[N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m; cin >> n >> m;
    int s, d; cin >> s >> d;
    
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    
    priority_queue<array<ll, 2>> pq; pq.push({0, s});
    while(!pq.empty()) {
        auto [x, v] = pq.top(); pq.pop();
        
        if(v == d) {
            cout << -x << endl;
            return 0;
        }
        
        if(vis[v]) continue;
        vis[v] = 1;
        
        for(auto [u, w]: adj[v]) {
            pq.push({x-w, u});
        }
        
    } cout << -1 << endl;
}