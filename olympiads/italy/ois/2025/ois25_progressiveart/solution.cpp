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
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, L, K; cin >> N >> M >> L >> K;

    if(K == 0) {
        cout << "YES" << lf;

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                cout << 'R';
            }

            cout << lf;
        }

        return 0;
    }

    if(L % 3 != 0 || (N - L + 1) * (M - L + 1) < K) {
        cout << "NO" << lf;
        return 0;
    } else cout << "YES" << lf;

    const string COLOUR = "RGB";

    vector<string> G(N);
    for(int i = 0; i < N; ++i) {
        G[i].assign(M, COLOUR[i % 3]);
    }

    int r = K / (M - L + 1) + (L - 1);
    int c = K % (M - L + 1) + (L - 1);

    char fi = r < N ? G[r][c] : '?';
    char se = r + 1 < N ? G[r + 1][0] : '?';

    for(; r < N; ++r) {
        for(; c < M; ++c) {
            if(G[r][c] == fi || G[r][c] == se) {
                G[r][c] = COLOUR[(r + 1) % 3];
            }
        }

        c = 0;
    }

    for(const auto &s: G) {
        cout << s << lf;
    }
}
