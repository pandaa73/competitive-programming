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

struct MaxQueue {
    MaxQueue(void): s(0), t(0) {}

    void push(int x) {
        while(!q.empty() && q.back().fi <= x) {
            q.pop_back();
        }

        q.emplace_back(x, t++);
    }

    void pop(void) {
        while(!q.empty() && q.front().se <= s) {
            q.pop_front();
        }

        s += 1;
    }

    int top(void) {
        return q.empty() ? 0 : q.front().fi;
    }

    int s, t;
    deque<pii> q;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int N, K; cin >> N >> K;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    MaxQueue s, t;
    for(int i = 0; i < K; ++i) {
        s.push(V[i]);
        t.push(-V[i]);
    }

    int mn = s.top() + t.top();
    for(int i = K; i < N; ++i) {
        s.pop();
        s.push(V[i]);

        t.pop();
        t.push(-V[i]);

        mn = min(mn, s.top() + t.top());
    }

    cout << mn << lf;
}
