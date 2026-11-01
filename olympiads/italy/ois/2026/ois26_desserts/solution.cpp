#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
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
constexpr int MAXN = 1e6+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<int> A(N), B(N);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    vector<int> pfx(2 * MAXN + 2);
    for(int i = 0; i < N; ++i) {
        pfx[A[i] + MAXN + 1] += (B[i] == K);
    }

    for(int i = 1; i < pfx.size(); ++i) {
        pfx[i] += pfx[i - 1];
    }

    int Q; cin >> Q;
    while(Q--) {
        int l, r, k; cin >> l >> r >> k;

        l += MAXN, r += MAXN + 1;

        cout << (pfx[r] - pfx[l] >= k ? "YES" : "NO") << lf;
    }
}
