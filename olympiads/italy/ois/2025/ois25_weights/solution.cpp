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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    set<int> s;
    vec<int> cnt_s(N + 1);

    s.emplace(1);
    cnt_s[1] = N;

    set<int> t;
    vec<ll> cnt_t(N + 1);

    t.emplace(0);
    cnt_t[0] = (ll)N * (N - 1) / 2;

    auto add = [&](int x, int k) -> void {
        if(cnt_t[x] == 0) {
            t.emplace(x);
        } else if(cnt_t[x] == -k) {
            t.erase(x);
        }

        cnt_t[x] += k;
    };

    auto update = [&](int a, int b) -> void {
        cnt_s[a] -= 1;
        cnt_s[b] -= 1;

        if(cnt_s[a] == 0) s.erase(a);
        if(cnt_s[b] == 0) s.erase(b);

        add(abs(a - b), -1);

        for(auto x: s) {
            add(abs(a - x), -cnt_s[x]);
            add(abs(b - x), -cnt_s[x]);
            add(abs(a + b  - x), +cnt_s[x]);
        }

        cnt_s[a + b] += 1;
        if(cnt_s[a + b] == 1) s.emplace(a + b);
    };

    auto query = [&](ll K) -> int {
        ll k = 0;

        for(auto x: t) {
            k += cnt_t[x];

            if(K < k) return x;
        }

        assert(0 && "query: unreachable");
    };

    for(int q = 0; q < Q; ++q) {
        int type; cin >> type;

        if(type == 1) {
            int a, b; cin >> a >> b;

            update(a, b);
        } else {
            ll K; cin >> K;

            cout << query(K - 1) << lf;
        }
    }
}
