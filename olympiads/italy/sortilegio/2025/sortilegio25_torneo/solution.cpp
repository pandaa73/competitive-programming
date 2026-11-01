// @check-accepted: examples draw cubic quadratic quadratic_fast_queries no_limits
#include <string>
#include <vector>
#include <cassert>
using namespace std;

using ll = long long;

vector<ll> S, C, F;

struct DSU {
    void init(int N) {
        dsu.resize(N, -1);
    }

    int find(int v) {
        return dsu[v] < 0 ? v : dsu[v] = find(dsu[v]);
    }

    void join(int u, int v) {
        u = find(u);
        v = find(v);

        assert(u != v);

        if(dsu[u] > dsu[v]) swap(u, v);

        dsu[u] += dsu[v];
        dsu[v] = u;

        S[u] += S[v];
        C[u] += C[v];
        F[u] += F[v];
    }

    vector<int> dsu;
};

DSU dsu;

void organizza(int N, string T) {
    S.resize(N, 0);
    C.resize(N, 0);
    F.resize(N, 0);
    for(int i = 0; i < N; ++i)
        (T[i] == 'S' ? S[i] : (T[i] == 'C' ? C[i] : F[i]))++;

    dsu.init(N);
}

int sfida(int a, int b) {
    int u = dsu.find(a);
    int v = dsu.find(b);

    assert(u != v);

    ll p = 0;

    p += S[u] * F[v];
    p += C[u] * S[v];
    p += F[u] * C[v];

    p -= S[v] * F[u];
    p -= C[v] * S[u];
    p -= F[v] * C[u];

    if(p == 0) return -1;

    return p > 0 ? a : b;
}

void allea(int a, int b) {
    dsu.join(a, b);
}
