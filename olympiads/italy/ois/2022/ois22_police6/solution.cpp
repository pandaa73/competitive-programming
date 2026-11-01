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

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#else

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll N, M, L; cin >> N >> M >> L;

    vector<ll> V(N);
    for(auto &x: V) cin >> x;

    map<ll, int> m;
    for(auto x: V) {
        m[x - M] += 1;
        m[x + M + 1] -= 1;
    }

    int x = N, y = 0;
    for(auto [k, v]: m) {
        if(k > L) break;
        if(k > 0) x = min(x, y);

        y += v;
    }

    cout << min(x, y) << lf;
}
