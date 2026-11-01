#include <bits/stdc++.h>
#include <queue>
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr ll G = 10 * 2; // * 2 so that we don't need to divide K0 by 2

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll N, M, V; cin >> N >> M >> V;

    ll K0 = M * V * V;

    infof("K0 = %lld", K0);

    vector<ll> H(N);
    for(auto &x: H) cin >> x;

    vector<int> ans(N, N - 1);

    ll K = 0;

    priority_queue<array<ll, 2>> q;
    q.push({-K0, 0});
    infof("%d: q.push(%lld)", 0, K0);

    for(int i = 1; i < N; ++i) {
        K += M * G * (H[i - 1] - H[i]);

        infof("===============");
        infof("%d: reached with K = %d", i, K);

        while(!q.empty() && q.top()[0] > K) {
            auto [k, j] = q.top(); q.pop();

            ans[j] = i - 1;
        }

        q.push({K - K0, i});
        infof("%d: q.push(%lld)", i, K - K0);
    }

    for(auto x: ans)
        cout << x << " ";
    cout << lf;
}
