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

constexpr int INF = 2e9;

struct SegTree {
    SegTree(int N, vector<int> &V): N(N), mn(2 * N, INF) {
        for(int i = 0; i < N; ++i)
            mn[i + N] = V[i];

        for(int i = N - 1; i > 0; i--)
            mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
    }

    void remove(int i) {
        mn[i += N] = INF;

        for(i >>= 1; i > 0; i >>= 1)
            mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
    }

    int find_first(int i, int x) {
        int l = i + N, r = 2 * N;

        int vl = -1, vr = -1;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) vl < 0 && mn[l] <= x ? vl = l++ : l++;
            if(r&1) mn[--r] <= x ? vr = r : 0;
        }

        int v = vl < 0 ? vr : vl;
        if(v < 0) return -1;

        while(v < N) if(mn[v <<= 1] > x) v++;

        return v - N;
    }

    int N;
    vector<int> mn;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> P(N);
    for(auto &x: P) cin >> x;

    vector<array<int, 2>> ranges;
    for(int i = 0; i < N; ++i) {
        if(P[i] <= i) continue;

        if(P[P[i]] != i) {
            cout << "NO" << lf;
            return 0;
        }

        ranges.push_back({i, P[i]});
    }

    vector<int> V(N, INF);
    for(auto [l, r]: ranges) V[l] = r;

    SegTree st(N, V);

    vector<int> pos(N, -1);
    vector<vector<int>> ops;

    auto dfs = [&](int l, auto &&dfs) -> void {
        int r = V[l];

        ops[pos[l]].push_back(l);
        ops[pos[l]].push_back(r);

        st.remove(l);
        int nxt = st.find_first(l, r);

        if(nxt < 0) return;

        pos[nxt] = pos[l];

        dfs(nxt, dfs);
    };

    for(int i = 0; i < ranges.size(); ++i) {
        auto [l, r] = ranges[i];

        if(pos[l] >= 0) continue;

        pos[l] = ops.size();
        ops.push_back({});

        dfs(l, dfs);
    }

    cout << "YES" << lf;

    cout << ops.size() << lf;

    for(auto &v: ops) {
        cout << v.size();

        for(auto x: v)
            cout << " " << x;
        cout << lf;
    }
}
