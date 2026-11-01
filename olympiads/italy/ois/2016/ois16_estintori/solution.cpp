#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int N, M; cin >> N >> M;

    vec<string> G(N);
    for(auto &x: G) cin >> x;

    int ans = 0;

    vector vis(N, vec<bool>(M));
    for(int r = 1; r < N - 1; ++r) {
        for(int c = 1; c < M - 1; ++c) {
            if(G[r][c] == '#' || vis[r][c]) continue;

            int n = 1, m = 1;
            for(; r + n < N - 1; ++n) {
                if(G[r + n][c] == '#') break;
            }

            for(; c + m < M - 1; ++m) {
                if(G[r][c + m] == '#') break;
            }

            bool ok = 0;
            for(int i = r; i < r + n; ++i) {
                for(int j = c; j < c + m; ++j) {
                    vis[i][j] = 1;
                    ok |= G[i][j] == '@';
                }
            }

            ans += 1 - ok;
        }
    }

    cout << ans << lf;
}
