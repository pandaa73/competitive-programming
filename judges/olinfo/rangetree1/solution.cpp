#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree {
    SegTree(int n) : st(4*n, {0, 0}) {}
    void update(int v, int l, int r, int ql, int qr, bool lz) {
        auto& [val, lzy] = st[v]; if(lz) {
            val = r-l-val; lzy ^= 1;
        } if(l >= qr || r <= ql) return;

        if(r-l == 1) { val ^= 1; return; }
        if(l >= ql && r <= qr) {
            val = r-l-val; 
            lzy ^= 1;
            return;
        }

        int m = (l+r)/2;
        update(2*v, l, m, ql, qr, lzy);
        update(2*v+1, m, r, ql, qr, lzy);

        lzy = 0; val = st[2*v].first + st[2*v+1].first;
    }

    int query(int v, int l, int r, int ql, int qr, bool lz) {
        auto& [val, lzy] = st[v]; if(lz) {
            val = r-l-val; lzy ^= 1;
        } if(l >= qr || r <= ql) return 0;

        if(r-l == 1) return val;
        if(l >= ql && r <= qr) return val;

        int m = (l+r)/2;
        int sx = query(2*v, l, m, ql, qr, lzy);
        int dx = query(2*v+1, m, r, ql, qr, lzy);

        lzy = 0; return sx + dx;
    }

    vector<pair<int, bool>> st;
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q; cin >> n >> q;
    SegTree st(n); for(int i = 0; i < q; ++i) {
        int t, a, b; cin >> t >> a >> b;
        switch(t) {
            case 0: st.update(1, 0, n, a, b+1, 0); break;
            case 1: cout << st.query(1, 0, n, a, b+1, 0) << endl; break;
        }
    }
}