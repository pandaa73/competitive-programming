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

struct History {
    int t;
    int a, b;

    int u, v;
    int dsu_v;
    int par_v;
};

struct DSUQueue {
    DSUQueue(int N): dsu(N, -1), par(N, 0) {}

    array<int, 2> find(int v) {
        if(dsu[v] < 0)
            return {v, 0};

        auto [u, p] = find(dsu[v]);

        return {u, p ^ par[v]};
    }

    bool join(int a, int b, int t = 0) {
        auto [u, par_a] = find(a);
        auto [v, par_b] = find(b);

        if(dsu[u] > dsu[v])
            swap(u, v); // no need to swap the rest!

        history.push({t, a, b, u, v, dsu[v], par[v]});

        if(u == v) {
            if(par_a == par_b)
                return history.pop(), 0;
            return 1;
        }

        dsu[u] += dsu[v];
        dsu[v] = u;
        par[v] = par_a ^ 1 ^ par_b;

        return 1;
    }

    void rollback(const History &op) {
        auto [t, a, b, u, v, dsu_v, par_v] = op;

        if(u == v) return;

        dsu[u] -= dsu_v;
        dsu[v] = dsu_v;
        par[v] = par_v;
    }

    void pop(void) {
        if(history.empty()) return;

        int cnt_A = 0, cnt_B = 0;
        stack<array<int, 2>> sA, sB;

        auto op = history.top(); history.pop();

        rollback(op);

        if(op.t == 0) {
            sB.push({op.a, op.b});
            cnt_B++;
        } else {
            A--;
            return;
        }

        while(!history.empty() && (A == 0 || (cnt_A < A && cnt_A < cnt_B))) {
            op = history.top(); history.pop();

            rollback(op);

            if(op.t == 0) {
                cnt_B++;
                sB.push({op.a, op.b});
            } else {
                cnt_A++;
                sA.push({op.a, op.b});
            }
        }

        if(sA.empty()) {
            while(!sB.empty())
                sA.push(sB.top()), sB.pop();

            A = sA.size();
        }

        while(!sB.empty()) {
            auto [a, b] = sB.top(); sB.pop();

            join(a, b, 0);
        }

        while(!sA.empty()) {
            auto [a, b] = sA.top(); sA.pop();

            join(a, b, 1);
        }

        A--;
        rollback(history.top()); history.pop();
    }

    vector<int> dsu;
    vector<int> par;

    int A;
    stack<History> history;
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<array<int, 2>> ed(M);
    for(auto &[u, v]: ed) cin >> u >> v, u--, v--;

    DSUQueue dsu(N);

    ll ans = 0;
    for(int l = 0, r = 0; l < M; ++l) {
        while(r < M && dsu.join(ed[r][0], ed[r][1])) r++;

        ans += r - l;

        dsu.pop();
    }

    cout << ans << lf;
}
