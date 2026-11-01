#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr ll INF  = 1e18;
constexpr ll LINF = 1e10;

struct DSU {
    DSU(int N): T(N, -1) {}

    int find(int n) {
        return T[n] < 0 ? n : T[n] = find(T[n]);
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);

        if(u == v) return 0;

        if(T[u] > T[v]) {
            swap(u, v);
        }

        T[u] += T[v];
        T[v] = u;

        return 1;
    }

    vec<int> T;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    vec<tuple<ll, int, int>> A, B;
    for(int e = 0; e < M; ++e) {
        int u, v, w; cin >> u >> v >> w;
        u -= 1, v -= 1;

        (u * v == 0 ? A : B).emplace_back(w, u, v);
    }

    if(A.size() < K) {
        cout << -1 << lf;
        return 0;
    }

    sort(all(A));
    sort(all(B));

    A.emplace_back(INF, N, N);
    B.emplace_back(INF, N, N);

    auto check = [&](ll lambda) -> pll {
        DSU dsu(N);

        ll x = 0, c = 0;
        int a = 0, b = 0;
        for(; a < A.size() - 1 || b < B.size() - 1;) {
            auto [wa, ua, va] = A[a];
            auto [wb, ub, vb] = B[b];

            bool is_a = wa - lambda < wb;

            ll w; int u, v;
            if(is_a) {
                a += 1;
                w = wa - lambda, u = ua, v = va;
            } else {
                b += 1;
                w = wb, u = ub, v = vb;
            }

            if(dsu.join(u, v)) {
                x += w;
                c += is_a;
            }
        }

        return {x, c};
    };

    ll l = -LINF, r = LINF;
    while(r - l > 1) {
        ll m = l + (r - l) / 2;

        auto [x, c] = check(m);

        if(c > K) {
            r = m;
        } else {
            l = m;
        }
    }

    auto [x, c] = check(l);

    cout << (c <= K ? x + K * l : -1) << lf;
}
