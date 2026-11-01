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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr int MAXK = 500;
constexpr ll INF = 1e18;

template<typename T>
void chmax(T &a, T b) {
    a = max(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector C(N, vector<ll>(M)), W(N, vector<ll>(M));
    for(auto &v: W) for(auto &x: v) cin >> x;
    for(auto &v: C) for(auto &x: v) cin >> x;

    ll ans = -INF;

    vector dp(N + 1, vector<ll>(M + 1));
    for(int k = 1; k <= MAXK; ++k) {
        for(auto &v: dp) fill(all(v), -INF);

        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= M; ++j) {
                const auto c = C[i - 1][j - 1];
                const auto w = W[i - 1][j - 1];

                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

                if(dp[i][j] == -INF && c != k) continue;

                dp[i][j] += w;

                if(c == k) {
                    chmax(dp[i][j], w);
                    chmax(ans, dp[i][j]);
                }
            }
        }
    }

    cout << ans << lf;
}
