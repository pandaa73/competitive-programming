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

constexpr int LOGC = 30;
constexpr int LOGK = 18;

struct ORQueue {
    int get(void) {
        return (s.empty() ? 0 : s.top().fi) | (t.empty() ? 0 : t.top().fi);
    }

    void push(int x) {
        int y = s.empty() ? 0 : s.top().fi;
        s.emplace(x | y, x);
    }

    void pop(void) {
        if(t.empty()) {
            int y = 0;
            while(!s.empty()) {
                auto [_o, x] = s.top(); s.pop();
                y |= x;
                t.emplace(y, x);
            }
        }

        if(!t.empty()) t.pop();
    }

    void clear(void) {
        while(!s.empty()) s.pop();
        while(!t.empty()) t.pop();
    }

    stack<pii> s, t;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<int> V(2 * N);
    for(int i = 0; i < N; ++i) {
        cin >> V[i]; V[i + N] = V[i];
    }

    ORQueue q;
    vector lift(LOGK, vector<int>(N));
    auto check = [&](int b) -> bool {
        q.clear();

        for(int l = 0, r = 0; l < N; ++l) {
            q.pop();

            for(; r <= l + N && (q.get()&b) != b; ++r) {
                q.push(V[r]);
            }

            lift[0][l] = r;
        }

        for(int lg = 0; lg < LOGK - 1; ++lg) {
            for(int i = 0; i < N; ++i) {
                int r = i + N + 1;

                int j = lift[lg][i];
                if(j <= i + N) {
                    if(j >= N) j -= N;
                    int k = lift[lg][j];
                    if(j < lift[lg][i]) k += N;
                    if(k <= j + N) r = k;
                }

                lift[lg + 1][i] = r;
            }
        }

        for(int i = 0; i < N; ++i) {
            int x = N;
            int lg = 0, k = K, j = i;
            while(k >= 0) {
                if(k == 0) return 1;
                if(k&1) {
                    j = lift[lg][j];
                    if(j > i + x) break;
                    if(j >= N) j -= N, x -= N;
                }

                lg += 1;
                k >>= 1;
            }
        }

        return 0;
    };

    int b = 0;
    for(int lg = LOGC; lg >= 0; lg--) {
        int pow = 1 << lg;

        if(check(b | pow)) b |= pow;
    }

    cout << b << lf;
}
