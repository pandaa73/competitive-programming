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

constexpr int MOD = 1e9 + 7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int K, N; cin >> K >> N;

    vec<int> V(N);
    for(auto &x: V) {
        cin >> x;
        x -= 1;
    }

    vec<int> pi(N);
    for(int i = 1; i < N; ++i) {
        int j = pi[i - 1];
        while(j > 0 && V[i] != V[j]) {
            j = pi[j - 1];
        }

        pi[i] = j + (V[i] == V[j]);
    }

    vec<int> dp(N + 1);

    int pow = K;
    for(int i = 1; i <= N; ++i) {
        dp[i] = add(pow, dp[pi[i - 1]]);
        chmul(pow, K);

        cout << dp[i] << lf;
    }
}
