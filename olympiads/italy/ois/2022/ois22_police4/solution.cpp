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

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#else

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr ll INF = 1e18;

void chmin(ll &a, ll b) {
    a = min(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K, T, L; cin >> N >> K >> T >> L;

    vector<ll> V(N + 1);
    for(int i = 1; i <= N; ++i) cin >> V[i];

    vector dp(N + 1, vector<ll>(K + 1, INF));
    fill(all(dp[0]), 0);

    auto next_green = [&](ll t) -> ll {
        ll q = t / T;

        return q&1 ? T * (q + 1) : t;
    };

    for(int i = 0; i < N; ++i) {
        ll d = V[i + 1] - V[i];

        dp[i + 1][0] = next_green(dp[i][0]) + d;
        for(int k = 1; k <= K; ++k) {
            chmin(dp[i + 1][k - 1], dp[i][k] + d);
            chmin(dp[i + 1][k], next_green(dp[i][k]) + d);
        }
    }

    ll x = next_green(dp[N][0]);
    if(K > 0) chmin(x, dp[N][1]);

    cout << (L - V[N]) + x << lf;
}
