#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infof

#define infos(str)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

struct DSU {
    DSU(int N): dsu(N, -1) {}

    int find(int v) {
        return dsu[v] < 0 ? v : dsu[v] = find(dsu[v]);
    }

    bool join(int a, int b) {
        a = find(a), b = find(b);

        if(a == b) return 0;

        if(dsu[a] > dsu[b])
            swap(a, b);

        dsu[a] += dsu[b];
        dsu[b] = a;

        return 1;
    }

    vector<int> dsu;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, Q; cin >> N >> M >> Q;

    vector<array<int, 3>> ed(M);
    for(auto &[w, u, v]: ed)
        cin >> u >> v >> w, u--, v--;

    sort(rall(ed));

    vector<int> Qs(Q);
    for(auto &x: Qs) cin >> x;
    
    vector<int> order(Q); iota(all(order), 0);
    sort(all(order), [&](int i, int j) -> bool {
        if(Qs[i] == Qs[j])
            return i < j;
        return Qs[i] > Qs[j];
    });

    DSU dsu(N);

    int cc = N;
    for(int i = 0, j = 0; i < Q; ++i) {
        auto &q = Qs[order[i]];

        for(; j < M && q <= ed[j][0]; ++j)
            cc -= dsu.join(ed[j][1], ed[j][2]);

        q = cc;
    }

    for(auto &x: Qs)
        cout << x << lf;
}
