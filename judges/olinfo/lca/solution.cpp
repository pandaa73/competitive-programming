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
    Lift(void): sum(0), min(INF), pfx(0), sfx(0), max(0) {}

    ll sum;
    ll min;

    ll pfx;
    ll sfx;
    ll max;
};

Lift add(const Lift &a, const Lift &b) {
    Lift x;

    x.sum = a.sum + b.sum;
    x.min = min(a.min, b.min);

    x.pfx = max(a.pfx, a.sum + b.pfx);
    x.sfx = max(b.sfx, b.sum + a.sfx);
    x.max = max({a.max, b.max, a.sfx + b.pfx});

    return x;
}

void chadd(Lift &a, const Lift &b) {
    a = add(a, b);
}

vector<int> d;
vector<vector<int>> lift;
vector<vector<Lift>> lift_val;

void inizia(int N, int T, int A[], int B[], int C[]) {
    d = vector<int>(N);
    lift = vector(LOG, vector<int>(N));
    lift_val = vector(LOG, vector<Lift>(N));

    vector<vector<pll>> adj(N);
    for(int i = 0; i < N - 1; ++i) {
        adj[A[i]].emplace_back(B[i], C[i]);
        adj[B[i]].emplace_back(A[i], C[i]);
    }

    auto dfs = [&](int v, auto &&dfs) -> void {
        for(int lg = 0; lg < LOG - 1; ++lg) {
            int u = lift[lg][v];
            lift[lg + 1][v] = lift[lg][u];

            lift_val[lg + 1][v] = add(lift_val[lg][v], lift_val[lg][u]);
        }

        for(auto [u, w]: adj[v]) {
            if(u == lift[0][v]) continue;

            d[u] = 1 + d[v];
            lift[0][u] = v;

            Lift &val = lift_val[0][u];

            val.sum = w;
            val.min = w;

            val.pfx = val.max = val.sfx = max(w, 0LL);

            dfs(u, dfs);
        }
    };

    dfs(0, dfs);
}

int get_lca(int u, int v) {
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
}

long long int distanza1(int u, int v) {
    int lca = get_lca(u, v);

    return d[u] + d[v] - 2 * d[lca];
}

long long int distanza2(int u, int v) {
    int lca = get_lca(u, v);

    ll x = 0;
    for(int lg = LOG - 1; lg >= 0; lg--) {
        int a = lift[lg][u], b = lift[lg][v];

        if(d[a] >= d[lca]) {
            x += lift_val[lg][u].sum;
            u = a;
        }

        if(d[b] >= d[lca]) {
            x += lift_val[lg][v].sum;
            v = b;
        }
    }

    return x;
}

long long int minimo(int u, int v) {
    int lca = get_lca(u, v);

    ll x = INF;
    for(int lg = LOG - 1; lg >= 0; lg--) {
        int a = lift[lg][u], b = lift[lg][v];

        if(d[a] >= d[lca]) {
            x = min(x, lift_val[lg][u].min);
            u = a;
        }

        if(d[b] >= d[lca]) {
            x = min(x, lift_val[lg][v].min);
            v = b;
        }
    }

    return x;
}

long long int massimo(int u, int v) {
    int lca = get_lca(u, v);

    Lift x, y;
    for(int lg = LOG - 1; lg >= 0; lg--) {
        int a = lift[lg][u], b = lift[lg][v];

        if(d[a] >= d[lca]) {
            chadd(x, lift_val[lg][u]);
            u = a;
        }

        if(d[b] >= d[lca]) {
            chadd(y, lift_val[lg][v]);
            v = b;
        }
    }

    return max({x.max, y.max, x.sfx + y.sfx});
}

#ifdef LOCAL
static FILE *fr, *fw;

// Declaring variables
static int N;
static int Q;
static int T;
static int* A;
static int* B;
static int* C;
static int* U;
static int* V;
static long long int* res;

// Declaring functions
void inizia(int N, int T, int A[], int B[], int C[]);
long long int distanza1(int u, int v);
long long int distanza2(int u, int v);
long long int minimo(int u, int v);
long long int massimo(int u, int v);
void run(int Q, int T, int U[], int V[], long long int res[]);

// Functions ad-hoc for this grader
void run(int Q, int T, int U[], int V[], long long res[]) {
  for (int i = 0; i < Q; i++) {
    if (T == 0)
      res[i] = distanza1(U[i], V[i]);
    else if (T == 1)
      res[i] = distanza2(U[i], V[i]);
    else if (T == 2)
      res[i] = minimo(U[i], V[i]);
    else if (T == 3)
      res[i] = massimo(U[i], V[i]);
    else
      assert(!"Invalid value for T");
  }
}

int main() {
    fr = stdin;
    fw = stdout;

	// Reading input
	fscanf(fr, " %d %d %d", &N, &Q, &T);
	A = (int*)malloc((N-1) * sizeof(int));
	B = (int*)malloc((N-1) * sizeof(int));
	C = (int*)malloc((N-1) * sizeof(int));
	for (int i0 = 0; i0 < N-1; i0++) {
		fscanf(fr, " %d %d %d", &A[i0], &B[i0], &C[i0]);
	}
	U = (int*)malloc((Q) * sizeof(int));
	V = (int*)malloc((Q) * sizeof(int));
	for (int i0 = 0; i0 < Q; i0++) {
		fscanf(fr, " %d %d", &U[i0], &V[i0]);
	}

	// Calling functions
	inizia(N, T, A, B, C);
	res = (long long int*)malloc((Q) * sizeof(long long int));
	run(Q, T, U, V, res);

	// Writing output
	for (int i0 = 0; i0 < Q; i0++) {
		fprintf(fw, "%lld ", res[i0]);
	}
	fprintf(fw, "\n");

    fclose(fr);
    fclose(fw);
    return 0;
}
#endif
