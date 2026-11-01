#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    const int N = 26;
    int M; cin >> M;

    vec<int> dg(N);
    vec<vec<int>> adj(N);
    for(int e = 0; e < M; ++e) {
        char u, d, v; cin >> u >> d >> v;
        if(d == '<') swap(u, v);
        u -= 'a', v -= 'a';

        dg[v] += 1;
        adj[u].emplace_back(v);
    }

    queue<int> q;
    for(int n = 0; n < N; ++n) {
        if(dg[n] == 0) {
            q.emplace(n);
        }
    }

    while(!q.empty()) {
        auto u = q.front();
        q.pop();

        for(auto v: adj[u]) {
            if(--dg[v] == 0) {
                q.emplace(v);
            }
        }
    }

    bool ok = 1;
    for(int n = 0; n < N; ++n) {
        ok &= dg[n] == 0;
    }

    cout << (string)":" + "()"[ok] << lf;
}
