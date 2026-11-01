#include <algorithm>
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
using i128 = __int128;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

void solve(void) {
    int N; cin >> N;

    vector<ll> A(N), B(N), C(N);
    for(int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i] >> C[i];
    }

    int mxa = max_element(all(A)) - A.begin();
    int mxb = max_element(all(B)) - B.begin();

    int M = N - 1;
    vector<int> ans = {mxa};

    if(mxa != mxb) {
        M -= 1;
        ans.emplace_back(mxb);
    }

    vector<int> ord; ord.reserve(N - 1);
    for(int i = 0; i < N; ++i) {
        if(i != mxa && i != mxb) {
            ord.emplace_back(i);
        }
    }

    vector<vector<int>> adj(N + 1);

    sort(all(ord), [&](int i, int j) -> bool {
        return A[i] > A[j];
    });

    ord.emplace_back(N);
    M += 1;

    for(int i = 0; i + 1 < M; i += 2) {
        int a = ord[i + 0], b = ord[i + 1];

        adj[a].emplace_back(b);
        adj[b].emplace_back(a);

        infof("A: %2d -- %2d", a, b);
    }

    ord.pop_back();
    sort(all(ord), [&](int i, int j) -> bool {
        return B[i] > B[j];
    });

    ord.emplace_back(N);

    for(int i = 0; i + 1 < M; i += 2) {
        int a = ord[i + 0], b = ord[i + 1];

        adj[a].emplace_back(b);
        adj[b].emplace_back(a);

        infof("B: %2d -- %2d", a, b);
    }

    C.emplace_back(0);

    vector<bool> vis(N);
    vector<int> odd, even;
    auto dfs = [&](int v, auto &&dfs) -> pair<pll, bool> {
        vis[v] = 1;

        pair<pll, bool> ret = {{0, 0}, 0};
        for(auto u: adj[v]) {
            if(vis[u]) continue;

            ret = dfs(u, dfs);
        }

        ret.second ^= 1;
        if(ret.second) {
            odd.emplace_back(v);
            ret.first.first += C[v];
        } else {
            even.emplace_back(v);
            ret.first.second += C[v];
        }

        return ret;
    };

    infof("... mxa = %lld | mxb = %lld", mxa, mxb);

    vis[mxa] = vis[mxb] = 1;
    for(int i = 0; i < N; ++i) {
        if(vis[i]) continue;

        odd.clear();
        even.clear();

        auto [p, _b] = dfs(i, dfs);
        auto [o, e] = p;

        infof("===== i = %d =====", i);
        infor(" odd:");
        for(auto i: odd) {
            infor(" %2d", i);
        }
        infof(" | sum = %lld", o);
        infor("even:");
        for(auto i: even) {
            infor(" %2d", i);
        }
        infof(" | sum = %lld", e);

        for(auto j: (o > e ? odd : even)) {
            if(j < N) ans.emplace_back(j);
        }
    }

#ifdef DEBUG
    ll a = 0, b = 0, c = 0;
    for(int i = 0; i < N; ++i) {
        a += A[i], b += B[i], c += C[i];
    }

    a -= a/2, b -= b/2, c -= c/2;

    infof("Expected: A = %lld | B = %lld | C = %lld", a, b, c);

    a = 0, b = 0, c = 0;
    for(auto i: ans) {
        a += A[i], b += B[i], c += C[i];
    }

    infof("   Found: A = %lld | B = %lld | C = %lld", a, b, c);
#endif

    cout << ans.size() << lf;
    for(auto x: ans) {
        cout << x << " ";
    }

    cout << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
