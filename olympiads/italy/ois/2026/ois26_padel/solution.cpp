#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

void solve(void) {
    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x, x--;

    int mx = 0;
    for(int j = 0; j < N; ++j) {
        array<int, 2> pt = {};

        int cnt = 0;
        for(int i = j; i < N; ++i) {
            pt[V[i]]++;

            auto [y, x] = minmax(pt[0], pt[1]);

            if(x < 4 || x - y < 2) continue;

            cnt++;
            pt = {};
        }

        mx = max(mx, cnt);
    }

    cout << mx << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
