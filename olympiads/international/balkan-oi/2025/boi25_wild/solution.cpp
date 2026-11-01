#include <bits/stdc++.h>
#include <chrono>
#include <cstdlib>
#include <random>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node(void): pri(0), l(0), r(0), sz(0), x(0), mx(INT_MIN), mn(INT_MAX) {}
    Node(int x): pri(rng()), l(0), r(0), sz(1), x(x), mx(x), mn(x) {}

    int pri;
    int l, r;

    int sz;

    int x;
    int mx;
    int mn;
};

vector<Node> T(1);

int make_node(int k) {
    T.emplace_back(k);
    return T.size() - 1;
}

int pull(int v) {
    if(!v) return 0;

    int l = T[v].l, r = T[v].r;

    T[v].sz = T[l].sz + 1 + T[r].sz;
    T[v].mx = max({T[l].mx, T[v].x, T[r].mx});
    T[v].mn = min({T[l].mn, T[v].x, T[r].mn});

    return v;
}

int merge(int l, int r) {
    if(!l || !r) return l ? l : r;

    if(T[l].pri > T[r].pri) {
        T[l].r = merge(T[l].r, r);
        return pull(l);
    } else {
        T[r].l = merge(l, T[r].l);
        return pull(r);
    }
}

pii split(int v, int i) {
    if(!v) return {0, 0};

    if(T[T[v].l].sz >= i) {
        auto [l, r] = split(T[v].l, i);
        T[v].l = r;
        return {l, pull(v)};
    } else {
        auto [l, r] = split(T[v].r, i - T[T[v].l].sz - 1);
        T[v].r = l;
        return {pull(v), r};
    }
}

int find(int v, int i) {
    int lsz = T[T[v].l].sz;
    if(i == lsz) return T[v].x;

    return i < lsz ? find(T[v].l, i) : find(T[v].r, i - lsz - 1);
}

int rotaterdup(int v) {
    if(T[v].sz <= 1) return v;

    auto [l, r] = split(v, T[v].sz - 1);
    T[r].x = T[r].mn = T[r].mx = T[l].mx;
    return merge(r, l);
}

int dorotaterdup(int v, int l, int r) {
    if(r - l == 1) return v;
    if(l == 0 && r == T[v].sz) {
        return rotaterdup(v);
    }

    if(l == 0) {
        auto [vl, vr] = split(v, r);
        rotaterdup(vl);
        return merge(vl, vr);
    } else if(r == T[v].sz) {
        auto [vl, vr] = split(v, l);
        rotaterdup(vr);
        return merge(vl, vr);
    } else {
        auto [vt, vr] = split(v, r);
        auto [vl, vm] = split(vt, l);
        rotaterdup(vm);
        return merge(vl, merge(vm, vr));
    }
}

map<int, int> rg, s;

void try_merge_range(int l) {
    auto it = rg.find(l);
    assert(it != rg.end());

    auto [_l, li] = *it;
    if(T[li].mn == T[li].mx) s.erase(l);

    it = next(it);
    auto [m, mi] = *it;

    if(next(it) == rg.end()) return;
    if(T[li].mn < T[mi].mx) return;

    it = next(it);
    auto [r, _ri] = *it;

    li = merge(li, mi);

    it = rg.erase(prev(it)), s.erase(m);

    prev(it)->se = li;
    if(T[li].mx != T[li].mn) {
        s[l] = li;
    } else s.erase(l);
}

void split_range(int l, int m) {
    auto it = rg.find(l);
    assert(it != rg.end());

    auto [_l, li] = *it;

    if(l == m || l + T[li].sz == m) return;

    auto [lv, mv] = split(li, m - l);

    it->se = lv;
    rg[m] = mv;

    if(T[lv].mx != T[lv].mn) {
        s[l] = lv;
    } else s.erase(l);

    if(T[mv].mx != T[mv].mn) {
        s[m] = mv;
    } else s.erase(m);
}

void init(int N, vector<int> A) {
    int l = 0, v = make_node(A[0]);
    for(int i = 1; i < N; ++i) {
        if(A[i] > A[i - 1]) {
            rg[l] = s[l] = v;
            v = make_node(A[i]);
            l = i;
        } else {
            v = merge(v, make_node(A[i]));
        }
    }

    rg[l] = s[l] = v;
    rg[N] = s[N] = 0;
}

void change(int p, int x) {
    auto it = prev(rg.upper_bound(p));
    auto [l, _v] = *it;

    split_range(l, p);
    split_range(p, p + 1);

    auto v = rg[p];

    T[v].x = T[v].mx = T[v].mn = x;

    try_merge_range(p);
    if(l < p) {
        try_merge_range(l);
    } else if(it != rg.begin()) {
        it = prev(it);
        try_merge_range(it->fi);
    }
}

void perturb(int ql, int qr) {
    qr += 1;

    auto it = s.upper_bound(ql);
    if(it != s.begin()) it = prev(it);

    stack<int> upd;
    for(; it->fi < qr; it = next(it)) {
        auto [l, v] = *it;
        int r = l + T[v].sz;

        v = dorotaterdup(v, max(l, ql) - l, min(r, qr) - l);
        upd.emplace(l);
    }

    while(!upd.empty()) {
        auto l = upd.top(); upd.pop();

        try_merge_range(l);
    }
}

int calc(int p) {
    auto [l, v] = *prev(rg.upper_bound(p));

    return find(v, p - l);
}

// SAMPLE GRADER. DO NOT MODIFY BELOW THIS LINE

#ifndef EVAL
int main() {
    ios::sync_with_stdio(0);
	cin.tie(0);

    int N, Q; cin >> N >> Q;
    vector<int> A(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    init(N, std::move(A));

    for (int i = 0; i < Q; i++){
        int type; cin >> type;
        if (type == 1) {
            int p, x; cin >> p >> x;
            change(p, x);
        } else if (type == 2) {
            int l, r; cin >> l >> r;
            perturb(l, r);
        } else {
            int p; cin >> p;
            cout << calc(p) << "\n";
        }
    }
}
#endif
