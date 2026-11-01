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

    int root;

    vector<int> ord(N);
    vector<int> F(N), V(N);
    for(int i = 0; i < N; ++i) {
        cin >> F[i] >> V[i];

        ord[V[i]] = i;
    }

    int ans = 0;
    for(int i = N - 1; i >= 0; i--) {
        infof("======= Fixing %d =======", i);

        int v = ord[i];
        while(F[v] >= 0) {
            infof("v = %d: F = %d | V = %d | VF = %d",
                    v, F[v], V[v], V[F[v]]);

            if(V[F[v]] > V[v]) break;

            ans++;
            swap(V[v], V[F[v]]);
            swap(ord[V[v]], ord[V[F[v]]]);

            v = F[v];
        }
    }

    cout << ans << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    for(int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": ", solve();
}
