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
constexpr int MAXN = 1e5+7;

constexpr int MIN_M = 50;
constexpr int MIN_B = 80;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    int ans = 0;

    int B = 0, M = 0;
    for(int i = 0; i < N; ++i) {
        if(M >= MIN_M) {
            ans++;
            M -= MIN_M;
        } else if(B >= MIN_B) {
            ans++;
            B -= MIN_B;
        }

        int x; cin >> x;
        char c; cin >> c;

        (c == 'M' ? M : B) += x;
    }

    cout << ans << lf;
}
