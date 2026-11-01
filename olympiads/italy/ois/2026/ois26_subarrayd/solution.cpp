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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr ll NINF = -3e9;
constexpr ll INF = 1e15;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<ll> V(N);
    for(auto &x: V) cin >> x;

    auto check = [&](ll m) -> bool {
        ll k = K;
        ll x = 0;

        for(int i = 0; i < N; ++i) {
            x = max(x + V[i], V[i]);
            ll d = x - m;
            if(d > 0) {
                x -= d;
                k -= d;
            }
        }

        return k >= 0;
    };

    ll l = NINF, r = INF;
    while(r - l > 1) {
        ll m = (l + r) / 2;

        if(check(m)) {
            r = m;
        } else l = m;
    }

    cout << l + 1 << lf;
}
