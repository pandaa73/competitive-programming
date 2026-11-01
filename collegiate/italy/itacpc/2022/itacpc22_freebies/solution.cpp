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

constexpr int INF = INT_MAX;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vec<int> P(N);
    for(auto &x: P) cin >> x;

    sort(all(P));

    int X, Y; cin >> X >> Y;

    int M; cin >> M;

    vec<pii> V(M);
    for(auto &[x, y]: V) {
        cin >> x >> y;
    }

    vec<int> c(N), d(N);
    for(int i = 0; i < N; ++i) {
        d[i] = X + abs(Y - P[i]);
    }

    for(auto [x, y]: V) {
        auto p = lower_bound(all(P), y) - P.begin();

        int dl = p > 0 ? x + abs(y - P[p - 1]) : INF;
        int dr = p < N ? x + abs(y - P[p]) : INF;

        int dd = min(dl, dr);
        p -= dd == dl;

        if(dd <= d[p]) c[p] += 1;
    }

    cout << *min_element(all(c)) << lf;
}
