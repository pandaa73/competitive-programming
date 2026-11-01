#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

void solve(void) {
    int N, K; cin >> N >> K;

    int n = N % (K + 1);
    int m = (2 * (N / (K + 1))) % K;

    infof("... n = %d | m = %d", n, m);

    if(n == 0) {
        cout << (m ? "Bob" : "Alice") << lf;
        return;
    }

    if(m == K - 1 || (n > 1 && m == K - 2)) {
        cout << "Alice" << lf;
    } else cout << "Bob" << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
