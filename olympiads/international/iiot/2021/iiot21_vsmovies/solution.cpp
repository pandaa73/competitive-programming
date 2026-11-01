#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

vector<array<int, 2>> adj[MAXN];

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> Q >> N;

    vector<array<int, 3>> q(Q), ed(Q);
    for(int i = 0; i < Q; ++i) {
        array<int, 3> in;
        auto &[w, a, b] = in;

        cin >> a >> b >> w;

        q[i] = ed[i] = in;
    }

    vector<int> dsu(N, -1);
    auto find = [&](int v, auto &&find) -> int {
        return dsu[v] < 0 ? v : dsu[v] = find(dsu[v], find);  
    };

    auto unite = [&](int a, int b) -> bool {
        a = find(a, find), b = find(b, find);    
    
        if(a == b) return 0;

        if(dsu[a] > dsu[b])
            swap(a, b);

        dsu[a] += dsu[b];
        dsu[b] = a;

        return 1;
    };

    sort(ed.begin(), ed.end());
    
    ll mst = 0;
    for(auto [w, a, b]: ed) {
        if(!unite(a, b)) continue;
        
        mst += w;
        
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    vector<int> depth(N, 0);
    vector<vector<int>> 
       lift(N, vector<int>(LOG, 0)),
       max_ed(N, vector<int>(LOG, 0));
    
    auto bin_lift = [&](int v, auto &&bin_lift) -> void {
        for(int i = 1; i < LOG; ++i) {
            lift[v][i] = lift[lift[v][i - 1]][i - 1];
            max_ed[v][i] = max(max_ed[v][i - 1], max_ed[lift[v][i - 1]][i - 1]);
        }

        for(auto [u, w]: adj[v]) {
            if(u == lift[v][0]) continue;

            lift[u][0] = v;
            max_ed[u][0] = w;
            depth[u] = 1 + depth[v];

            bin_lift(u, bin_lift);
        }
    };

    bin_lift(0, bin_lift);

    auto find_lca = [&](int a, int b) -> int {
        if(depth[a] < depth[b])
            swap(a, b);

        int pow = 0;
        int k = depth[a] - depth[b];
        while(k > 0) {
            if(k&1)
                a = lift[a][pow];

            pow++;
            k >>= 1;
        }

        if(a == b) return a;

        for(pow = LOG - 1; pow >= 0; pow--) {
            if(lift[a][pow] != lift[b][pow]) {
                a = lift[a][pow];
                b = lift[b][pow];
            }
        }

        return lift[a][0];
    };

    for(auto [w, a, b]: q) {
        int lca = find_lca(a, b);

        int j = depth[a] - depth[lca];
        int k = depth[b] - depth[lca];

        int mx = 0, pow = 0;
        while(j > 0 || k > 0) {
            if(j&1) {
                mx = max(mx, max_ed[a][pow]);
                a = lift[a][pow];
            }

            if(k&1) {
                mx = max(mx, max_ed[b][pow]);
                b = lift[b][pow];
            }

            pow++;
            j >>= 1;
            k >>= 1;
        }

        cout << mst + w - mx << lf;
    }
}
