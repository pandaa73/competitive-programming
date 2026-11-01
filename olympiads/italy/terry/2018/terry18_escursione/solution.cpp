#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e4+7;

using ll = long long;

#define get_v(x, y) ((x) * M + (y))

bitset<MAXN> vis;
vector<array<int, 2>> adj[MAXN];

void solve(void) {
    int N, M; cin >> N >> M;

    for(int i = 0; i < N * M; ++i)
        adj[i].clear();

    vis = 0;

    int sus[N][M];
    for(auto &a: sus)
        for(auto &x : a)
            cin >> x;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            auto a = get_v(i, j);

            auto push = [&](int a, int b, int c) -> void {
                adj[a].push_back({b, c});
                adj[b].push_back({a, c});
            };

            if(i - 1 >= 0) push(a, get_v(i - 1, j), abs(sus[i][j] - sus[i - 1][j]));
            if(i + 1 <  N) push(a, get_v(i + 1, j), abs(sus[i][j] - sus[i + 1][j]));
            if(j - 1 >= 0) push(a, get_v(i, j - 1), abs(sus[i][j] - sus[i][j - 1]));
            if(j + 1 <  M) push(a, get_v(i, j + 1), abs(sus[i][j] - sus[i][j + 1]));
        }
    }

    priority_queue<array<int, 3>> pq; pq.push({0, get_v(0, 0), -1});
    while(!pq.empty()) {
        auto [d, v, fa] = pq.top(); pq.pop();

        if(vis[v]) continue;
        if(v == get_v(N - 1, M - 1)) {
            cout << -d << lf;
            break;
        }

        vis[v] = 1;

        for(auto [u, w]: adj[v])
            pq.push({min(d, -w), u, v});
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve();
}
