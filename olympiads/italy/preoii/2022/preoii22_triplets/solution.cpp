#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5+73;
typedef array<int, 2> Node;

vector<int> adj[N];

Node dfs(vector<int>& v, int src, int f = -1) {
    Node mx = {0, src};
    v[src] = f != -1 ? v[f]+1 : 0;
    for(int u: adj[src]) {
        if(u == f) continue;
        mx = max(mx, dfs(v, u, src)); 
    }

    return {mx[0]+1, mx[1]};
}

int build(int n, vector<int> a, vector<int> b) {
    for(int i = 0; i < n-1; ++i) {
        adj[a[i]].push_back(b[i]);    
        adj[b[i]].push_back(a[i]);
    }

    vector<int> vx(n), vy(n);
    Node x = dfs(vx, 0); x[0]--;
    Node y = dfs(vx, x[1]); y[0]--;
    dfs(vy, y[1]);

    Node z = {0, 0};
    for(int i = 0; i < n; ++i) {
        if(i == x[1] || i == y[1]) continue;
        z = max(z, {vx[i]+vy[i], i});
    }return y[0]+z[0];
}