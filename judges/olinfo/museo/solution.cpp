#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

struct SegTree {
    SegTree(void);
    SegTree(vector<int> &);

    void update(int, int);
    int find_mx(int, int);

    size_t N;
    vector<int> st;
};

SegTree::SegTree(void) : N(0), st(0) {}
SegTree::SegTree(vector<int> &v) : N(v.size()), st(2 * (N + 1), INT_MIN) {
    for(int i = 0; i < N; ++i)
        st[i + N] = v[i];

    for(int i = N - 1; i > 0; i--)
        st[i] = max(st[2 * i], st[2 * i + 1]);
}

void SegTree::update(int q, int x) {
    for(st[q += N] = x; q > 1; q /= 2)
        st[q / 2] = max(st[q], st[q ^ 1]);
}

int SegTree::find_mx(int l, int r) {
    int mx = INT_MIN;

    for(l += N, r += N; l < r; l /= 2, r /= 2) {
        if(l&1) mx = max(mx, st[l++]);
        if(r&1) mx = max(mx, st[--r]);
    }

    return mx;
}

SegTree st;

void inizia(int N, vector<int> A) { new (&st) SegTree(A); }
void aggiorna(int P, int X) { st.update(P, X); }
int massimo(int L, int R) { return st.find_mx(L, R + 1); }
