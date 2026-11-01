#include <bits/stdc++.h>
using namespace std;

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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr ll INF = 1e18;

struct Lift {
    ll aa, ab;
    ll ba, bb;

    void debug(void) {
        if(!IS_DEBUG) return;

        infof("aa = {} | ab = {} | ba = {} | bb = {}",
            aa, ab, ba, bb);
    }
};

Lift add(const Lift &a, const Lift &b) {
    Lift x;

    x.aa = min(a.aa + b.aa, a.ab + b.ba);
    x.ab = min(a.aa + b.ab, a.ab + b.bb);
    x.ba = min(a.ba + b.aa, a.bb + b.ba);
    x.bb = min(a.ba + b.ab, a.bb + b.bb);

    return x;
}

void chadd(Lift &a, const Lift &b) {
    a = add(a, b);
}

vector<int> d;
vector<vector<int>> lift;
vector<vector<Lift>> lift_up;
vector<vector<Lift>> lift_down;

void init(int N, int C, vector<int> A, vector<int> B, vector<int> U,
        vector<int> V) {
    d = vector<int>(N);
    lift = vector(LOG, vector<int>(N));
    lift_up = vector(LOG, vector<Lift>(N));
    lift_down = vector(LOG, vector<Lift>(N));

    vector<vector<int>> adj(N);
    for(int i = 0; i < N - 1; ++i) {
        adj[U[i]].emplace_back(V[i]);
        adj[V[i]].emplace_back(U[i]);
    }

    auto dfs = [&](int v, auto &&dfs) -> void {
        infof("===== dfs({}) =====", v);
        for(int lg = 0; lg < LOG - 1; ++lg) {
            int u = lift[lg][v];
            lift[lg + 1][v] = lift[lg][u];

            lift_up[lg + 1][v] = add(lift_up[lg][v], lift_up[lg][u]);
            lift_down[lg + 1][v] = add(lift_down[lg][u], lift_down[lg][v]);
        }

        for(auto u: adj[v]) {
            if(u == lift[0][v]) continue;

            d[u] = 1 + d[v];
            lift[0][u] = v;

            Lift &up = lift_up[0][u], &down = lift_down[0][u];

            up.aa = min(A[u], B[u] + C);
            up.ab = min(A[u] + B[v], B[u] + C);
            up.ba = min(A[u], C);
            up.bb = min(A[u] + B[v], C);

            down.aa = min(A[v], B[v] + C);
            down.ab = min(A[v] + B[u], B[v] + C);
            down.ba = min(A[v], C);
            down.bb = min(A[v] + B[u], C);

            dfs(u, dfs);
        }
    };

    dfs(0, dfs);
}

long long query(int X, int Y) {
    infof("===== query({}, {}) =====", X, Y);
    auto get_lca = [&](int u, int v) -> int {
        if(d[u] < d[v]) swap(u, v);

        int lg = 0;
        int k = d[u] - d[v];
        while(k > 0) {
            if(k&1) u = lift[lg][u];

            lg += 1;
            k >>= 1;
        }

        if(u == v) return u;

        for(lg = LOG - 1; lg >= 0; lg--) {
            if(lift[lg][u] != lift[lg][v]) {
                u = lift[lg][u];
                v = lift[lg][v];
            }
        }

        return lift[0][u];
    };

    int lca = get_lca(X, Y);

    infof("lca = {}", lca);

    Lift x;
    x.aa = 0;
    x.ab = INF;
    x.ba = INF;
    x.bb = INF;

    int lg, k;

    lg = 0;
    k = d[X] - d[lca];
    while(k > 0) {
        if(k&1) {
            infof("...   push_up: lg = {} | X = {}", lg, X);
            infor("... - lift: "); lift_down[lg][X].debug();
            infor("... -    x: "); x.debug();

            chadd(x, lift_up[lg][X]);
            X = lift[lg][X];
        }

        lg += 1;
        k >>= 1;
    }

    stack<pii> s;

    lg = 0;
    k = d[Y] - d[lca];
    while(k > 0) {
        if(k&1) {
            s.emplace(lg, Y);
            Y = lift[lg][Y];
        }

        lg += 1;
        k >>= 1;
    }

    while(!s.empty()) {
        auto [lg, Y] = s.top(); s.pop();

        infof("... push_down: lg = {} | Y = {}", lg, Y);
        infor("... - lift: "); lift_down[lg][Y].debug();
        infor("... -    x: "); x.debug();

        chadd(x, lift_down[lg][Y]);
    }

    return x.aa;
}

#ifdef LOCAL
int main() {
  ios_base::sync_with_stdio(false);
  int N, Q, C;
  cin >> N >> Q >> C;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  vector<int> B(N);
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }

  vector<int> U(N - 1), V(N - 1);
  for (int i = 0; i < N - 1; i++) {
    cin >> U[i] >> V[i];
  }

  init(N, C, A, B, U, V);

  for (int i = 0; i < Q; i++) {
    int X, Y;
    cin >> X >> Y;
    cout << query(X, Y) << endl;
  }
  return 0;
}
#endif
