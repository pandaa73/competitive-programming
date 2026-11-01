#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

template<typename T>
void chmin(T &a, const T b) {
    a = min(a, b);
}

template<typename T>
void chmax(T &a, const T b) {
    a = max(a, b);
}

void solve(void) {
    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    int a = 0, b = 0;
    for(auto x: V) {
        a += x;
        chmin(b, a);
    }

    b = abs(b);

    a = b;
    for(auto x: V) {
        a += x;
        chmax(b, a);
    }

    static int t = 1;

    cout << "Case #" << t++ << ":" _ b << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
