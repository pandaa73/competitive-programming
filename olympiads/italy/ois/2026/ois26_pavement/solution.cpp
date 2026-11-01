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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    int n = N / K, nk = N % K;
    int m = M / K, mk = M % K;

    int ans = n * m;
    if(nk == 0 && mk == 0) {
        // WOW THIS IS SO COOL
    } else if(nk == 0 || mk == 0) {
        if(!mk) swap(n, m), swap(nk, mk);
        if(2 * mk <= K) {
            ans += (n + 1) / 2;
        } else ans += n;
    } else if(nk + mk <= K) {
        if(n < m) swap(n, m), swap(nk, mk);
        ans += m;
        n -= m;
        bool add = m == 0;
        if(2 * mk <= K) {
            ans += (n + 1) / 2;
            if(n&1) add = 0;
        } else ans += n;
        add |= n == 0;
        ans += add;
    } else {
        bool add = 1;
        if(2 * mk <= K) {
            ans += (n + 1) / 2;
            if(n&1) add = 0;
        } else ans += n;
        if(2 * nk <= K) {
            ans += (m + 1) / 2;
            if(m&1) add = 0;
        } else ans += m;
        ans += add;
    }

    cout << ans << lf;
}
