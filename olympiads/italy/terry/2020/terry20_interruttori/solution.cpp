#include <bits/stdc++.h>
using namespace std;
// flag[10]

const int N = 1e5+1;
typedef pair<int, int> Node;

vector<Node> adj[2][N];
bool vis[N];
int dist[N];

pair<int, int> bfs(queue<Node> q) {
    int x, mx = 0;
    while(!q.empty()) {
        auto [t, n] = q.front(); q.pop();
    
        for(auto [u, v]: adj[t][n]) {
            if(vis[v]) continue;

            if(t) dist[v] = 1;
            else dist[v] = dist[n] + 1;

            if(dist[v] > mx) {
                mx = dist[v];
                x = v;
            }

            q.push({u, v});
            vis[v] = 1;
        }
    }

    return {x, mx};
}

void Solve(int t) {
    int n, m, o; cin >> n >> o >> m;
    queue<Node> q;
    for(int i = 0; i < o; ++i) {
        int v; cin >> v;
        adj[1][v].push_back({0, v});

        q.push({1, v});
    }

    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[0][u].push_back({0, v});
        adj[0][v].push_back({0, u});
    }

    auto [a, b] = bfs(q);
    cout << "Case #" << t+1 << ": " << a << " " << b << endl;

    for(int i = 0; i < N; ++i) {
        adj[0][i].clear();
        adj[1][i].clear();
    }

    fill(vis, vis+n, 0);
}

int main() {
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);

    int t; cin >> t;
    for(int i = 0; i < t; ++i) {
        Solve(i);
    }
}