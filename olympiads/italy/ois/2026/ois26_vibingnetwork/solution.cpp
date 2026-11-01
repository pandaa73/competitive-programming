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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, T, K; cin >> N >> T >> K;

    vector<int> V(T);
    for(auto &x: V) cin >> x;

    const int thresh = 67 * N;

    int j = -1;
    for(int i = 0; i < T; ++i) {
        if(100 * V[i] < thresh) { j = -1; continue; }

        if(j < 0 && i < T - K + 1) j = i + 1;

        if(i - j + 2 >= K) break;
    }

    cout << j << lf;
}
