#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

void solve(void) {
    ll N, M; cin >> N >> M;
    ll H, W; cin >> H >> W;

    if(N > M) swap(N, M);
    if(H > W) swap(H, W);

    bool b = 1;

    b &= gcd(H, W) == 1;
    b &= (H + W)&1;
    b &= N >= H + W;
    b &= M >= 2 * W;

    cout << (b ? "YES" : "NO") << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
