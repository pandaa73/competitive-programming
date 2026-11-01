#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
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

template<typename... Args>
using vec = vector<Args...>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    ll C = accumulate(all(V), 0LL) - *max_element(all(V));

    int n = K / (N - 1);
    int m = K % (N - 1);

    ll ans = C * n;

    int mx = V[0];
    for(int i = 1; i <= m; ++i) {
        if(mx < V[i]) {
            ans += mx;
            mx = V[i];
        } else ans += V[i];
    }

    cout << ans << lf;
}
