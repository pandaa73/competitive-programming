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
    int N, K; cin >> N >> K;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    int ans = 0;

    priority_queue<int> q;
    for(int i = 0; i < N; ++i, K--) {
        if(K == 0) {
            if(q.empty()) break;

            ans++;
            K += q.top();

            q.pop();
        }

        if(V[i] > 0) q.push(V[i]);
    }

    if(K == 0) {
        if(q.empty())
            ans = -1;
        else ans++;
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
