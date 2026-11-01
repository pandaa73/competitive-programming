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

#define f(i) (max(0, V[i] - V[i + 1]))
#define g(i) (max(0, V[i] - V[i + 2]))

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    if(N == 1) {
        cout << 0 << lf;
        return 0;
    }

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    ll x = 0;
    for(int i = 0; i < N - 1; ++i) {
        x += f(i);
    }

    ll y = min(x - f(0), x - f(N - 2));
    for(int i = 1; i < N - 1; ++i) {
        y = min(y, x - f(i - 1) - f(i) + g(i - 1));
    }

    cout << y << lf;
}
