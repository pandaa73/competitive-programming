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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int MAXN = 1e9;
constexpr int K = 1e6; // sum(phi(i)) >= MAXN; 1 <= i < K

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vec<int> primes;
    vec<int> lp(K), phi(K);

    phi[1] = 1;
    for(ll n = 2; n < K; ++n) {
        if(lp[n] == 0) {
            lp[n] = n;
            phi[n] = n - 1;
            primes.emplace_back(n);
        }

        for(auto p: primes) {
            const int m = n * p;
            if(p >= lp[n] || m >= K) break;

            lp[m] = p;
            phi[m] = phi[n] * (p - 1);
        }

        if(n * lp[n] < K) {
            lp[n * lp[n]] = lp[n];
            phi[n * lp[n]] = phi[n] * lp[n];
        }
    }

    // ll because K may overflow since it's larger than neeeded
    vec<ll> phis(K + 1);
    for(int n = 0; n < K; ++n) {
        phis[n + 1] = phis[n] + phi[n];
    }

    int T; cin >> T;
    while(T--) {
        int N; cin >> N;

        int d = upper_bound(all(phis), N) - phis.begin() - 1;

        vec<int> unq;
        for(int x = d; x > 1; x /= lp[x]) {
            if(unq.empty() || lp[x] != unq.back()) {
                unq.emplace_back(lp[x]);
            }
        }

        const int M = unq.size();

        N -= phis[d];

        auto check = [&](int m) -> bool {
            auto count = [&](int p, int i, bool x, auto &&count) -> int {
                if(i == M) return 0;
                int c = count(p, i + 1, x, count);
                p *= unq[i];
                c += (m/p) * (x ? -1 : 1);
                c += count(p, i + 1, x ^ 1, count);
                return c;
            };

            return (m - count(1, 0, 0, count)) <= N;
        };

        int l = 0, r = d;
        while(r - l > 1) {
            int m = (l + r) / 2;

            if(check(m)) {
                l = m;
            } else {
                r = m;
            }
        }

        cout << (r) _ (d - r) << lf;
    }
}
