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
constexpr int ROOT = 512;

struct MinQueue {
    MinQueue(void): in(0), out(0) {}

    void push(ll x) {
        while(!q.empty() && q.back().fi >= x) {
            q.pop_back();
        }

        q.emplace_back(x, in++);
    }

    void pop(void) {
        while(!q.empty() && q.front().se <= out) {
            q.pop_front();
        }

        out += 1;
    }

    ll top(void) {
        return q.empty() ? INF : q.front().fi;
    }

    int in, out;
    deque<pair<ll, int>> q;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> V(N - 1);
    for(auto &x: V) cin >> x;

    vector<MinQueue> dp(ROOT + 1);
    for(int i = N - 2; i >= 0; i--) {
        for(int j = 1; j < ROOT; ++j) {
            if(i + j >= N - 1) {
                dp[j].push(0LL);
                continue;
            }

            ll x = min(dp[j].top() + 1, dp[j + 1].top() + 1 + V[i]);

            dp[j].push(x);
            dp[j].pop();
        }
    }

    cout << dp[1].top() + 1 << lf;
}
