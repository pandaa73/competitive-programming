#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 2e5+7;

int K;

vector<ll> V;
vector<ll> sfx;
vector<int> nle;
vector<vector<array<int, 2>>> tbl;

int get_mn(int l, int r) {
    infof("get_mn: [%d, %d)", l, r);

    int lg = 31 - __builtin_clz(r - l);

    return min(tbl[lg][l], tbl[lg][r - (1 << lg)])[1];
}

void pianifica(int N, int K, vector<int> C) {
    ::K = K;

    V.resize(MAXN);
    sfx.resize(MAXN);
    nle.resize(MAXN);

    tbl.resize(LOG);
    for(auto &v: tbl)
        v.resize(MAXN);

    fill(all(nle), N);

    stack<array<int, 2>> s;
    for(int i = N - 1; i >= 0; i--) {
        int x = C[i];

        V[i] = x;
        tbl[0][i] = {x, i};

        while(!s.empty() && s.top()[0] >= x) s.pop();
        if(!s.empty()) nle[i] = s.top()[1];
        s.push({x, i});
    }

    for(int lg = 1; lg < LOG; ++lg)
        for(int i = 0; i + (1 << lg) <= N; ++i)
            tbl[lg][i] = min(tbl[lg - 1][i], tbl[lg - 1][i + (1 << (lg - 1))]);

    sfx[N - 1] = V[N - 1];
    for(int i = N - 2; i >= 0; i--) {
        int r = min(i + K + 1, N + 1);

        if(nle[i] < r) {
            sfx[i] = sfx[nle[i]] + V[i] * (nle[i] - i);
            continue;
        }

        int j = get_mn(i + 1, r);

        infof("%d: j = %d [sfx = %d | V = %d]", i, j, sfx[j], V[j]);

        sfx[i] = V[i] * K + sfx[j] - V[j] * (K - (j - i));
    }
}

long long viaggia(int l, int r) {
    int lk = max(l, r - K);

    int i = get_mn(lk, r);

    infof("[%d, %d): i = %d | sfx[l] = %lld | sfx[i] = %lld | V[i] = %lld",
            l, r, i, sfx[l], sfx[i], V[i]);

    return sfx[l] - sfx[i] + V[i] * (r - i);
}
