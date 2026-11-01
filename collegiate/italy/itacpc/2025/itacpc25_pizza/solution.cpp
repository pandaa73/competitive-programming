#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
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

constexpr int LOG = 30;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

vector<ll> fact(MAXN);

ll mod_inv(ll n) {
    ll e = MOD - 2;

    ll ans = 1;
    while(e > 0) {
        if(e&1) ans = (ans * n) % MOD;

        e >>= 1;
        n = (n * n) % MOD;
    }

    return ans;
}

ll choose(ll n, ll k) {
    ll a = fact[n];
    ll b = (fact[k] * fact[n - k]) % MOD;

    ll c = (a * mod_inv(b)) % MOD;

    infof("%lld choose %lld = %lld", n, k, c);

    return c;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    fact[0] = 1;
    for(int i = 1; i < MAXN; ++i)
        fact[i] = (i * fact[i - 1]) % MOD;

    int N, S, T; cin >> N >> S >> T;

    vector<int> V; V.reserve(N);
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        if((x&S) == x) V.push_back(x);

    }

    if((T&S) != T || V.size() < N) return cout << 0 << lf, 0;

    ll ans = 1;
    for(ll pow = 1; pow <= S; pow <<= 1) {
        if((S & pow) == 0) continue;

        int cnt = 0;
        for(auto x: V)
            cnt += (x & pow) != 0;

        int n = N - cnt;

        ll layer = 0;

        infof("pow = %lld, T = %lld | T&pow = %lld", pow, T, T&pow);

        int i = (cnt&1) ^ ((T&pow) != 0);

        infof("i = %d | n = %d", i, n);

        if(n == N && i == 0) i = 2; // remove (n choose 0)
        if(n == 0 && i == 1) layer = 0; // need odd but all are chosen -> imp

        for(; i <= n; i += 2)
            layer = (layer + choose(n, i)) % MOD;

        infof("layer %4lld: %lld", pow, layer);

        ans = (ans * layer) % MOD;
    }

    cout << ans << lf;
}
