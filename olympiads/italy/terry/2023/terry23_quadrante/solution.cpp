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

void solve(void) {
    int N; cin >> N;

    vector<pii> V(N);
    for(auto &[x, y]: V) cin >> x >> y;

    auto check = [&](int m) -> bool {
        vector<pii> A(V.begin(), V.begin() + m);
        sort(all(A));

        for(int i = 1; i < m; ++i) {
            if(A[i].se < A[i - 1].se) return 0;
        }

        return 1;
    };

    int l = 1, r = N + 1;
    while(r - l > 1) {
        int m = (l + r) / 2;

        if(check(m)) {
            l = m;
        } else r = m;
    }

    static int t = 1;
    cout << "Case #" << t++ << ":" _ l << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
