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

constexpr ll INF = 1e18;

constexpr int START = 0;
constexpr int STOP = 1;

struct MonotonicLineMap {
    MonotonicLineMap(int N) {
        m.emplace(N, INF);
    }

    void push(int p, ll x) {
        auto it = m.lower_bound(p);

        if constexpr(IS_DEBUG) assert(it != m.end());

        if(x > it->se + (it->fi - p)) return;

        while(it != m.begin()) {
            it = prev(it);

            if(it->se >= INF) break;
            if(it->se < x + (p - it->fi)) break;

            it = m.erase(it);
        }

        m.emplace(p, x);
    }

    void kill(int l, int r, int T) {
        auto it = m.lower_bound(l);

        if constexpr(IS_DEBUG) assert(it != m.end());

        while(it->fi < r && it->se <= INF + T) {
            it = m.erase(it);
        }

        it = m.lower_bound(r);
        while(it != m.begin()) {
            it = prev(it);

            if(it->fi < l || it->se > INF + T) break;

            it = m.erase(it);
        }

        if(T >= 0) {
            m[l] = max(m[l], INF + T);
            m[r - 1] = max(m[r - 1], INF + T);
        }
    }

    void reset(int l, int r, int T) {
        auto itl = m.find(l);
        if(itl != m.end() && itl->se == INF + T) m.erase(itl);

        auto itr = m.find(r - 1);
        if(itr != m.end() && itr->se == INF + T) m.erase(itr);
    }

    ll query(int p) {
        auto it = m.lower_bound(p);

        if constexpr(IS_DEBUG) assert(it != m.end());

        return it->se + (it->fi - p);
    }

    map<int, ll> m;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K, M; cin >> N >> K >> M;

    vector<array<int, 5>> events;
    for(int i = 0; i < M; ++i) {
        int l, r; cin >> l >> r;
        int s, e; cin >> s >> e;

        if(s == 0 && l <= K && K <= r) {
            cout << -1 << lf;
            return 0;
        }

        events.push_back({s, START, e + 1, l, r});
        events.push_back({e + 1, STOP, e + 1, l, r});
    }

    sort(all(events));

    bool pushed = 0;
    MonotonicLineMap L(N), R(N);
    for(auto [T, t, T_end, l, r]: events) {
        if(!pushed && T > 0) {
            infof("===== Pushing Start =====");
            L.push(K, 0);
            R.push(N - K - 1, 0);

            pushed = 1;
        }

        infof("===== Processing Event at T = {} =====", T);
        infof("type = \"{}\" | T_end = {}", t == START ? "start" : "stop",
            T_end);

        infof("L: {}", L.m);
        infof("R: {}", R.m);

        int la = l, ra = r + 1;
        int lb = N - r - 1, rb = N - l;

        infof("range L: [{}, {})", la, ra);
        infof("range R: [{}, {})", lb, rb);

        if(t == START) {
            ll x = L.query(la - 1);
            ll y = R.query(lb - 1);

            infof("x = {} | y = {}", x, y);

            L.kill(la, ra, T_end);
            R.kill(lb, rb, T_end);

            if(x < INF) {
                if(la > 0) L.push(la - 1, x);
                if(rb < N) R.push(rb, x);
            }

            if(y < INF) {
                if(lb > 0) R.push(lb - 1, y);
                if(ra < N) L.push(ra, y);
            }
        } else {
            L.reset(la, ra, T_end);
            R.reset(lb, rb, T_end);
        }
    }

    infof("===== Finished Processing Events =====");
    infof("L: {}", L.m);
    infof("R: {}", R.m);

    ll x = INF;

    for(auto [k, v]: L.m) x = min(x, v);
    for(auto [k, v]: R.m) x = min(x, v);

    cout << (x < INF ? x : -1) << lf;
}
