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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> F(N);
    for(auto &x: F) cin >> x;

    vector<bool> vis(N);
    deque<array<int, 2>> q; q.push_back({0, 0});
    while(!q.empty()) {
        auto [d, v] = q.front(); q.pop_front();

        if(vis[v]) continue;
        vis[v] = 1;

        if(v == N - 1) return cout << d << lf, 0;

        q.push_front({d, F[v]});
        if(v - 1 >= 0) q.push_back({d + 1, v - 1});
        if(v + 1  < N) q.push_back({d + 1, v + 1});
    }

    assert(0);
}
