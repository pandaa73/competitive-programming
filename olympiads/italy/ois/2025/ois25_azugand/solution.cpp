#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int EXP = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 2e5+7;;

using ll = long long;

bitset<EXP> adj[EXP];

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    vector<int> v(N);
    for(auto &x: v) cin >> x;

    for(auto u: v) {
        for(int e = 0; e < EXP; ++e) {
            int x = 1 << e;

            if(!(u & x)) continue;

            for(int f = 0; f < EXP; ++f) {
                int y = 1 << f;

                if(!(u & y) || e == f) continue;

                adj[e][f] = 1;
                adj[f][e] = 1;
            }
        }
    }

    // for(int e = 0; e < EXP; ++e)
    //     for(int f = e + 1; f < EXP; ++f)
    //         if(adj[e][f]) cerr << "edge:" _ (1 << e) _ (1 << f) << lf;


    // cerr << "---------------------" << lf;

    auto bfs = [&](int src, vector<int> &d) -> void {
        d.resize(EXP, -1);

        bitset<EXP> vis;
        queue<int> q; q.push(src);

        d[src] = 0;
        while(!q.empty()) {
            auto v = q.front(); q.pop();

            for(int u = 0; u < EXP; ++u) {
                if(!adj[v][u] || vis[u]) continue;

                vis[u] = 1;
                d[u] = d[v] + 1;

                q.push(u);
            }
        }
    };

    vector<int> d[EXP];

    for(int e = 0; e < EXP; ++e)
        bfs(e, d[e]);

    auto query = [&](int a, int b) -> int {
        if(a & b) return 1;

        int ans = INT_MAX;
        for(int e = 0; e < EXP; ++e) {
            int x = 1 << e;

            if(!(a & x)) continue;

            for(int f = 0; f < EXP; ++f) {
                int y = 1 << f;

                if(!(b & y)) continue;
                if(d[e][f] < 0) continue;

                // cerr << "possibile path [" << a << "," _ b << "]:" _ x _ y << lf;;

                int dist = d[e][f] + 1;
                // cerr << "dist:" _ dist << lf;

                ans = min(ans, dist);
            }
        }

        return ans == INT_MAX ? -1 : ans;
    };

    while(Q--) {
        int a, b; cin >> a >> b;

        cout << query(v[a - 1], v[b - 1]) << lf;
    }
}
