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

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int MAXN = 1 << 16;

int conta(int N, vector<int> V) {
    vec<int> Q(MAXN, N - 1);
    for(int i = 0; i < N; ++i) {
        Q[V[i]] = i;
    }

    vec<int> dp(N + 1);
    vector rg(N + 1, vec<bool>(N + 1));
    for(int i = 0; i < N; ++i) {
        rg[i][i] = 1;
    }

    for(int r = 2; r <= N; ++r) {
        dp[r] = dp[r - 1];

        int M = r;
        for(int l = r - 3; l >= 0; l -= 3) {
            int x = V[l], z = V[r - 1], y = x ^ z;
            int m = Q[y];

            rg[l][r] = (rg[l][M] & rg[M][r])
                | (rg[l + 1][m] & rg[m + 1][r - 1]);

            if(rg[l][r]) {
                dp[r] = max(dp[r], dp[l] + r - l);
                M = l;
            }
        }
    }

    return dp[N];
}

#ifdef LOCAL
int main() {
	// se vuoi leggere da file decommenta queste due linee
	// assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));

	int n;
	cin >> n;

	vector<int> d(n);
	for (auto &x : d)
		cin >> x;

	int ans = conta(n, d);
	cout << ans << '\n';
}
#endif
