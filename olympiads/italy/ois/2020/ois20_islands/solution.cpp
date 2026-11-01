#include <bits/stdc++.h>
using namespace std;

const int N = 1e3+3;

typedef pair<int, int> Node;

vector<Node> adj[N][N];
bool vis[N][N];

bool DFS(Node v, int n, int m) {
    vis[v.first][v.second] = 1;
    bool pen = 0; 
    if(v.first == n or v.first == 1 or v.second == m or v.second == 1) pen = 1;
    for(auto [i, j]: adj[v.first][v.second]) {
        if(i == n or i == 1 or j == m or j == 1) pen = 1;

        if(!vis[i][j]) pen |= DFS({i, j}, n, m);
    }

    return pen;
}

int main() {
    int n, m; cin >> n >> m;
    bool v[n+2][m+2];
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int x; cin >> x;
            v[i][j] = x == 1;
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(!v[i][j]) continue;

            if(v[i+1][j]) {
                adj[i][j].push_back({i+1, j});
                adj[i+1][j].push_back({i, j});
            }

            if(v[i][j+1]) {
                adj[i][j].push_back({i, j+1});
                adj[i][j+1].push_back({i, j});
            }

            if(v[i-1][j]) {
                adj[i][j].push_back({i-1, j});
                adj[i-1][j].push_back({i, j});
            }

            if(v[i][j-1]) {
                adj[i][j].push_back({i, j-1});
                adj[i][j-1].push_back({i, j});
            }
        }
    }

    int is = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(vis[i][j] or !v[i][j]) continue;

            if(!DFS({i, j}, n, m)) is++;
        }
    }

    cout << is << endl;
}