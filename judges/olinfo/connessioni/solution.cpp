#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

struct DSU {
    DSU(void);
    DSU(size_t);

    size_t count(void);
    size_t find(size_t);
    void unite(size_t, size_t);

    size_t N;
    size_t sets;
    vector<int> dsu;
};

DSU::DSU(void) : N(0), sets(0), dsu(0) {}
DSU::DSU(size_t N) : N(N), sets(N), dsu(N, -1) {}

size_t DSU::count(void) { return sets; }
size_t DSU::find(size_t v) { return dsu[v] < 0 ? v : dsu[v] = find(dsu[v]); }
void DSU::unite(size_t u, size_t v) {
    u = find(u), v = find(v);

    if(u == v) return;

    sets--;
    if(u > v) swap(u, v);

    dsu[u] += dsu[v];
    dsu[v] = u;
}

DSU dsu;

void inizia(int N) { new (&dsu) DSU(N); }
int collega(int X, int Y) { return dsu.unite(X, Y), dsu.count(); };
