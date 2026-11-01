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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

//constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr int MAXPRINT = 31;

int query(const vector<bool> &qry);
void answer(int a, int b);

int find_odd(int N, int l, int r, const vector<int> &s) {
    infof("... find_odd(...)");
    infof("... - N = %d | rg = [%d, %d)", N, l, r);
    infor("... - s:");

    if(s.size() <= MAXPRINT) {
        for(auto x: s) {
            infor(" %d", x);
        }
    } else infor(" ...");

    infof("");

    while(r - l > 1) {
        int m = (l + r) / 2;

        vector<bool> qry(N);
        for(int ll = l; ll < m; ++ll) {
            qry[s[ll]] = 1;
        }

        if(query(qry)&1) {
            r = m;
        } else l = m;
    }

    return s[l];
}

pii solve_even(int N, const int LOG, const vector<pii> &ed) {
    infof("===== solve_even =====");
    infof("N = %d | LOG = %d | ed = ...", N, LOG);

    int bits = 0;
    int bit  = 0;

    for(int lg = 0; lg < LOG; ++lg) {
        const int pow = 1 << lg;

        vector<bool> qry(N);

        for(int i = 0; i < N; ++i) {
            qry[i] = i&pow;
        }

        int k = pow * (query(qry)&1);

        bits |= k;
        if(bit == 0) bit = k;
    }

    infof("bits = %d", bits);

    vector<int> s;
    for(int i = 0; i < N; ++i) {
        if((i&bit) == bit) {
            s.emplace_back(i);
        }
    }

    int a = find_odd(N, 0, s.size(), s);
    int b = a ^ bits;

    return {a, b};
}

pii solve_odd(int N, const int LOG, const vector<pii> &ed) {
    infof("===== solve_odd =====");
    infof("N = %d | LOG = %d | ed = ...", N, LOG);

    const int pow = 1 << LOG;

    vector<int> s(N); iota(all(s), 0);

    int a = find_odd(N, 0, pow, s);
    int b = find_odd(N, pow, N, s);

    return {a, b};
}

#ifndef LOCAL
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<pii> ed(N - 1);
    for(auto &[u, v]: ed) {
        cin >> u >> v;
        u--, v--;
    }

#else
void solve(int N, vector<pii> ed) {
#endif

    infof("======= solve(%d, ...) =======", N);

    const int LOG = 31 - __builtin_clz(N - 2); // ceil(LOG(N - 1)) - 1
    const int pow = 1 << LOG;

    vector<bool> qry(N - 1);
    for(int i = 0; i < pow; ++i) {
        qry[i] = 1;
    }

    auto [x, y] = (query(qry)&1 ? solve_odd : solve_even)(N - 1, LOG, ed);

    infof("... Found edges: %d -- %d", x, y);

    vector<vector<int>> adj(N);
    for(auto [u, v]: ed) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> d1(N), d2(N);
    auto dfs = [&](int v, int f, vector<int> &d, auto &&dfs) -> void {
        for(auto u: adj[v]) {
            if(u == f) continue;

            d[u] = 1 + d[v];
            dfs(u, v, d, dfs);
        }
    };

    auto [a, b] = ed[x];
    auto [c, d] = ed[y];

    dfs(a, -1, d1, dfs);
    dfs(b, -1, d2, dfs);

    int u = d1[c] > d2[c] ? a : b;
    int v = d1[c] > d1[d] ? c : d;

    answer(u + 1, v + 1);
}

#ifndef LOCAL
int query(const vector<bool> &qry) {
    cout << "?";
    for(auto x: qry) {
        cout << " " << (int)x;
    }

    cout << ff;

    int ans; cin >> ans;
    return ans;
}

void answer(int a, int b) {
    cout << "!" _ a _ b << ff;
}
#else

namespace {

static constexpr int MAXQ = 31;
static int Q = 0;

static int N;
static int A, B;
static vector<int> path;

int answer_query(const vector<bool> &qry) {
    infor("Query %2d: ?", Q);

    if(qry.size() <= MAXPRINT) {
        for(auto x: qry) {
            infor(" %d", x);
        }
    } else infor(" ...");

    if(++Q > MAXQ) {
        infof("");
        printf("Too many queries.\n");
        exit(0);
    }

    int ans = 0;

    int n = path.size();
    for(int i = 1; i < n; ++i) {
        ans += qry[path[i]] != qry[path[i - 1]];
    }

    if(qry[path[0]]) {
        infor(" (A)");
    }

    if(qry[path.back()]) {
        infor(" (B)");
    }

    infof(" -> %d", ans);

    return ans;
}

void answer_answer(int a, int b) {
    if(A > B) swap(A, B);
    if(a > b) swap(a, b);

    if(a != A || b != B) {
        printf("Wrong answer.\nFound (%d, %d), expected (%d, %d).\n",
                a, b, A, B);
        exit(0);
    }

    printf("OK. %d queries.\n", Q);
}

}

int query(const vector<bool> &qry) {
    return ::answer_query(qry);
}

void answer(int a, int b) {
    return ::answer_answer(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> ::N;
    cin >> ::A >> ::B;

    vector<pii> ed(N - 1);
    for(auto &[u, v]: ed) {
        cin >> u >> v;
        u--, v--;
    }

    vector<vector<pii>> adj(N);
    for(int i = 0; i < N - 1; ++i) {
        auto [u, v] = ed[i];

        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }

    auto dfs = [&](int v, int f, auto &&dfs) -> bool {
        if(v == ::B - 1) return 1;

        for(auto [u, id]: adj[v]) {
            if(u == f) continue;

            if(dfs(u, v, dfs)) {
                ::path.emplace_back(id);
                return 1;
            }
        }

        return 0;
    };

    dfs(::A - 1, -1, dfs);

    assert(path.size() >= 2 && "A and B should have a distance of at least 2.");

    infor("path:");
    for(auto x: path) {
        infor(" %d", x);
    }

    infof("");

    solve(N, ed);
}
#endif
