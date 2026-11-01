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

int add(int a, int b) {
    int x = a + b;

    if(x >= MOD) {
        x -= MOD;
    }

    return x;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<array<ll, 3>> ed(M);
    for(auto &[w, u, v]: ed) {
        cin >> u >> v >> w;
        u -= 1, v -= 1;
    }

    sort(rall(ed));

    vector<map<int, int>> dp(N);
    for(auto [w, u, v]: ed) {
        chadd(dp[v][w], add(dp[u][w + 1], 1));
        chadd(dp[u][w], add(dp[v][w + 1], 1));
    }

    int ans = MOD - M;
    for(auto &m: dp) {
        for(auto [k, v]: m) {
            chadd(ans, v);
        }
    }

    cout << ans << lf;
}
