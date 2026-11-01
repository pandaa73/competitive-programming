#include <bits/stdc++.h>
using namespace std;

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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr ll INF = 1e9+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll x, y; cin >> x >> y;

    ll l, r;

    l = 0, r = INF;
    while(r - l > 1) {
        ll m = (l + r) / 2;

        if(m * m < x) {
            l = m;
        } else r = m;
    }

    x = r;

    l = 0, r = INF;
    while(r - l > 1) {
        ll m = (l + r) / 2;

        if(m * m <= y) {
            l = m;
        } else r = m;
    }

    y = r;

    cout << y - x << lf;
}
