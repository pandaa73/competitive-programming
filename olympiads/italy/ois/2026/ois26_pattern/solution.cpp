#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

#define int ll

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

pii vec(const pii &A, const pii &B) {
    return {A.fi - B.fi, A.se - B.se};
}

pii add(const pii &A, const pii &B) {
    return {A.fi + B.fi, A.se + B.se};
}

signed main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<pair<pii, pii>> V(N);
    for(auto &[p, q]: V) {
        auto &[a, b] = p;
        auto &[c, d] = q;

        cin >> a >> b >> c >> d;

        if(p > q) swap(p, q);
    }

    pii v = V[0].fi;
    for(auto &[p, q]: V) {
        p = vec(p, v);
        q = vec(q, v);
    }

    int M; cin >> M;

    set<pair<pii, pii>> s;
    vector<pair<pii, pii>> m;
    for(int i = 0; i < M; ++i) {
        pii p, q;
        auto &[a, b] = p;
        auto &[c, d] = q;

        cin >> a >> b >> c >> d;

        if(p > q) swap(p, q);

        s.emplace(p, q);

        if(vec(q, p) == V[0].se) {
            m.emplace_back(p, q);
        }
    }

    int cnt = 0;
    for(const auto &[p, q]: m) {
        bool ok = 1;
        for(int i = 1; i < N; ++i) {
            const auto &[a, b] = V[i];

            if(s.count({add(p, a), add(p, b)})) continue;

            ok = 0;
            break;
        }

        cnt += ok;
    }

    cout << cnt << lf;
}
