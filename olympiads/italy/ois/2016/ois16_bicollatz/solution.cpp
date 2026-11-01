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

mt19937 timmy_loves_gambling(73);

int main(void) {
#ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    pll x; cin >> x.fi >> x.se;

    set<pll> s;

    int it = 0;
    while(x.fi != 1 || x.se != 1) {
        if(s.count(x)) break;
        s.emplace(x);

        if((x.fi&1) && (x.se&1)) {
            x.fi = 3 * x.fi + 1;
            x.se = 3 * x.se + 1;
        } else if((x.fi&1) || (x.se&1)) {
            (x.fi&1 ? x.fi : x.se) += 3;
        } else {
            x.fi >>= 1;
            x.se >>= 1;
        }

        it += 1;
    }

    if(x.fi != 1 || x.se != 1) {
        cout << -1 << lf;
    } else cout << it << lf;
}
