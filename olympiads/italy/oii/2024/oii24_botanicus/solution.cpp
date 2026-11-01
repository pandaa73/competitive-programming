#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define _ << " " <<

using ll = long long;

constexpr int MAXN = 3e5+7;

vector<int> adj[MAXN];
vector<int> h[MAXN];
array<int, 2> line[MAXN];
int f[MAXN];

int dp[MAXN];

void dfs(int v, int d) {
    h[d].push_back(v);

    for(auto u: adj[v]) {
        line[u] = (
            adj[v].size() > 1 ? 
            (array<int, 2>){1, v} : 
            (array<int, 2>){line[v][0] + 1, line[v][1]}
        );

        dfs(u, d+1);
    }
}

int pota(int N, vector<int> P) {
    for(int i = 0; i < N; ++i)
        f[i] = P[i];

    for(int i = 1; i < N; ++i)
        adj[f[i]].push_back(i);

    dfs(0, 0);

    int mx_h = INT_MAX;
    for(int i = 0; i < N; ++i) {
        if(h[i].size()) continue;

        mx_h = i;
        break;
    }

    for(int i = 1; i < mx_h; ++i) {
        dp[i] = dp[i - 1];

        for(auto v: h[i - 1]) {
            if(adj[v].size()) continue;
            
            int delta = line[v][0];

            int curr = v;
            while(adj[line[curr][1]].size() == 1) {
                curr = line[curr][1];
                delta += line[curr][0];
            }

            adj[line[curr][1]].pop_back();
            dp[i] += delta;
        }
    }

    // for(int i = 0; i < mx_h; ++i) {
    //     cout << dp[i] << " ";
    // } cout << lf;

    int sum = 0, mn = INT_MAX;
    for(int i = mx_h - 1; i > 0; i--) {
        mn = min(mn, dp[i] + sum);
        sum += h[i].size();
    }

    mn = min(mn, sum);

    return mn;
}