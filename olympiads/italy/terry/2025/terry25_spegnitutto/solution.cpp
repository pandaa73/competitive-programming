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

void solve(void) {
    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    int cnt = 0;
    for(int i = 0; i < N - 1; ++i) {
        if(!V[i]) continue;

        cnt++;

        V[i] = V[i + 1] = 0;
    }

    if(V[N - 1]) cnt++;

    cout << cnt << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    for(int i = 1; i <= T; ++i)
        cout << "Case #" << i << ": ", solve();
}
