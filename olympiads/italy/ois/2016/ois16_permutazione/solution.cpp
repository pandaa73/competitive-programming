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

const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int K; cin >> K;

    string S = "";

    int l = 0, r = 25;
    for(int i = 1; i < K; ++i) {
        S += ALPHA[i&1 ? l++ : r--];
    }

    while(l <= r) {
        S += ALPHA[K&1 ? l++ : r--];
    }

    cout << S << lf;
}
