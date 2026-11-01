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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

void intrappola(int X);
bool ispeziona(vector<int> V);

void acchiappa(int N, vector<int> U, vector<int> V) {
    vec<vec<int>> adj(N);
    for(int e = 0; e < N - 1; ++e) {
        adj[U[e]].emplace_back(V[e]);
        adj[V[e]].emplace_back(U[e]);
    }

    vec<int> sz(N);
    auto calc_sz = [&](int u, int p, auto &&calc_sz) -> void {
        sz[u] = 1;
        for(auto v: adj[u]) {
            if(v == p) continue;
            calc_sz(v, u, calc_sz);
            sz[u] += sz[v];
        }
    };

    auto find_centroid = [&](int u, int p, auto &&find_centroid) -> int {
        for(auto v: adj[u]) {
            if(v == p) continue;

            if(sz[v] > N/2) {
                return find_centroid(v, u, find_centroid);
            }
        }

        return u;
    };

    calc_sz(0, N, calc_sz);
    int c = find_centroid(0, N, find_centroid);

    vec<int> odd;
    vec<int> p(N);
    auto dfs = [&](int u, int o, auto &&dfs) -> void {
        if(o) odd.emplace_back(u);

        sz[u] = 1;
        for(auto v: adj[u]) {
            if(v == p[u]) continue;

            p[v] = u;

            dfs(v, o ^ 1, dfs);

            sz[u] += sz[v];
        }
    };

    p[c] = N;
    dfs(c, 0, dfs);

    vec<vec<int>> nadj(N);
    for(int u = 0; u < N; ++u) {
        for(auto v: adj[u]) {
            if(v == p[u] || sz[v] == 1) continue;
            nadj[u].emplace_back(v);
        }
    }

    for(int n = 0; n < N; ++n) {
        sort(all(nadj[n]), [&](int u, int v) -> bool {
            return sz[u] > sz[v];
        });
    }

    auto get_subtree = [&](int u, vec<int> &t, auto &&get_subtree) -> void {
        t.emplace_back(u);
        for(auto v: adj[u]) {
            if(v == p[u]) continue;
            get_subtree(v, t, get_subtree);
        }
    };

    auto solve = [&](int u, auto &&solve) -> void {
        if(u != c) intrappola(u);

        if(nadj[u].empty()) return;
        if(nadj[u].size() == 1) return solve(nadj[u][0], solve);

        vec<int> t;
        get_subtree(nadj[u][0], t, get_subtree);

        bool first = ispeziona(t);
        intrappola(u);

        if(first) return solve(nadj[u][0], solve);

        int l = 1, r = nadj[u].size();
        while(r - l > 1) {
            int m = (l + r) / 2;

            t.clear();
            for(int e = l; e < m; ++e) {
                get_subtree(nadj[u][e], t, get_subtree);
            }

            if(ispeziona(t)) {
                r = m;
            } else {
                l = m;
            }

            intrappola(u);
        }

        solve(nadj[u][l], solve);
    };

    if(ispeziona(odd)) {
        intrappola(c);
    } else if(adj[c].size() != nadj[c].size()) {
        intrappola(c);
        intrappola(c);
    }

    solve(c, solve);
}

#ifdef LOCAL

namespace {
    vector<vector<int>> adj;
    int N, R, S;
    bool win;

    mt19937 rng;

    void build(vector<int> &U, vector<int> &V) {
        adj.resize(N);
        for(int i=0; i<N-1; i++) {
            adj[U[i]].push_back(V[i]);
            adj[V[i]].push_back(U[i]);
        }
    }

    void move() {
        // S = adj[S][rng()%adj[S].size()];
        printf("Where would you like to move? [");
        for(int i = 0; i < adj[S].size(); ++i) {
            printf("%d%c", adj[S][i], ",]"[i == adj[S].size() - 1]);
        }
        printf(": ");
        fflush(stdout);
        cin >> S;
    }

    void end() {
        if(win) cout << "Successful. " << R << " queries.\n";
        else cout << "Unsuccessful.\n";
        exit(0);
    }
}

void acchiappa(int N, vector<int> U, vector<int> V);

void intrappola(int X) {
    printf("Query %d: intrappola(%d)\n", R, X);
    R++;

    win = (X == S);
    if(win) end();

    move();
}

bool ispeziona(vector<int> V) {
    printf("Query %d: ispeziona([", R);
    for(int i = 0; i < V.size(); ++i) {
        printf("%d%c", V[i], ",]"[i == V.size() - 1]);
    }
    printf(")\n");
    R++;

    bool res = false;
    for(auto x:V) res |= (x == S);

    move();

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> S;

    vector<int> U(N-1), V(N-1);

    for(int i=0; i<N-1; i++)
        cin >> U[i] >> V[i];

    build(U, V);

    R = 0;
    win = false;

    acchiappa(N, U, V);

    end();
}

#endif /* LOCAL */
