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

constexpr int INF = 1e6;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    vector G(N, vector<int>(M));
    for(auto &v: G) for(auto &x: v) cin >> x;

    vector d(N, vector<int>(M));
    auto check = [&](int m) -> bool {
        for(auto &v: d) fill(all(v), K + 1);
        deque<pii> q; q.emplace_back(0, 0); d[0][0] = 0;

        auto try_push = [&](int i, int j, int h, int x) -> void {
            if(i < 0 || i >= N) return;
            if(j < 0 || j >= M) return;

            bool b = abs(G[i][j] - h) > m;

            x += b;

            if(d[i][j] <= x) return;
            d[i][j] = x;

            if(b) {
                q.emplace_back(i, j);
            } else q.emplace_front(i, j);
        };

        while(!q.empty()) {
            auto [i, j] = q.front(); q.pop_front();

            if(i == N - 1 && j == M - 1) return 1;

            try_push(i - 1, j, G[i][j], d[i][j]);
            try_push(i + 1, j, G[i][j], d[i][j]);
            try_push(i, j - 1, G[i][j], d[i][j]);
            try_push(i, j + 1, G[i][j], d[i][j]);
        }

        return 0;
    };

    int l = -1, r = INF;
    while(r - l > 1) {
        int m = (l + r) / 2;

        if(check(m)) {
            r = m;
        } else l = m;
    }

    cout << r << lf;
}
