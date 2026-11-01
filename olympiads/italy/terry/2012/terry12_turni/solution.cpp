#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> K >> N;

    vector<array<int, 2>> V(N);
    for(auto &[l, r]: V) cin >> l >> r;

    sort(all(V), [&](const array<int, 2> &a, const array<int, 2> &b) -> bool {
        return a[0] < b[0];
    });

    int ans = 0;
    for(int r = 0, i = 0; r < K; ++ans) {
        int mx = 0;
        for(; i < N && V[i][0] <= r; ++i)
            mx = max(mx, V[i][1]);

        r = mx + 1;
    }

    cout << ans << lf;
}