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

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M, K; cin >> N >> M >> K;

    vec<int> V(N);
    for(auto &x: V) cin >> x;

    stack<int> s;
    int k = 0, cnt = 0;
    for(int i = 0; i < M; ++i) {
        if(V[i]) {
            k += 1;
        } else {
            s.emplace(i);
        }
    }

    auto fix = [&](void) -> void {
        while(k < K) {
            k += 1;
            cnt += 1;

            V[s.top()] = 1;
            s.pop();
        }
    };

    fix();

    for(int i = M; i < N; ++i) {
        k -= V[i - M];
        if(V[i]) {
            k += 1;
        } else {
            s.emplace(i);
        }

        fix();
    }

    cout << cnt << lf;
}
