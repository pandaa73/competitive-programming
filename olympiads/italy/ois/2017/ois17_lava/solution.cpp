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

constexpr int INF = 1e9;

constexpr int  NONE = 0;
constexpr int    UP = 1;
constexpr int  DOWN = 2;
constexpr int  LEFT = 1;
constexpr int RIGHT = 2;

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

    vector d(N, vec<int>(M, INF));

    queue<pii> q;

    d[0][0] = 0;
    q.emplace(0, 0);

    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        int l = d[r][c];

        const vec<int> vdr = {-2, -1, 0, 1, 2};
        const vec<int> vdc = {-2, -1, 0, 1, 2};

        for(auto dr: vdr) {
            for(auto dc: vdc) {
                if(abs(dr) + abs(dc) > 2) continue;

                r += dr;
                c += dc;

                if(r >= 0 && r < N && c >= 0 && c < M && G[r][c] == '.' &&
                        l + 1 < d[r][c]) {
                    d[r][c] = l + 1;
                    q.emplace(r, c);
                }

                r -= dr;
                c -= dc;
            }
        }
    }

    cout << d[N - 1][M - 1] << lf;
}
