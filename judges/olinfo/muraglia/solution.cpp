#include <bits/stdc++.h>
using namespace std;
// flag[10]

struct SegTree {
    SegTree() {}
    SegTree(vector<int>& arr) {
        this->arr = arr;
        st.resize(4*arr.size());
        Build(1, 0, arr.size());
    }

    void Build(int v, int l, int r) {
        if(r-l == 1) {
            st[v] = arr[l];
            return;
        }

        int m = (l+r)/2;
        Build(2*v, l, m);
        Build(2*v+1, m, r);

        st[v] = max(st[2*v], st[2*v+1]); 
    }

    void Update(int pos, int x, int v, int l, int r) {
        if(r-l == 1) {
            st[v] = x;
            arr[pos] = x;
            return;
        }

        int m = (l+r)/2;
        if(m > pos) Update(pos, x, 2*v, l, m);
        else Update(pos, x, 2*v+1, m, r);

        st[v] = max(st[2*v], st[2*v+1]);
    }

    int PGE(int pos, int x, int v, int l, int r) {
        if(l > pos) return -1;
        if(r-l == 1) return l;

        int m = (l+r)/2, sx = -1, dx = -1;
        if(st[2*v+1] > x) dx = PGE(pos, x, 2*v+1, m, r);
        if(dx != -1) return dx;
        if(st[2*v] > x) return PGE(pos, x, 2*v, l, m); 

        return -1;
    }

    int NGE(int pos, int x, int v, int l, int r) {
        if(r <= pos) return -1;
        if(r-l == 1) return l;

        int m = (l+r)/2, sx = -1, dx = -1;
        if(st[2*v] > x) sx = NGE(pos, x, 2*v, l, m);
        if(sx != -1) return sx;
        if(st[2*v+1] > x) return NGE(pos, x, 2*v+1, m, r);

        return -1;
    }

    vector<int> st;
    vector<int> arr;
} st;

void inizializza(int N, vector<int> H) { 
    st.arr = H;
    st.st.resize(4*N);
    st.Build(1, 0, N);
}

void cambia(int x, int h) { st.Update(x, h, 1, 0, st.arr.size()); }
pair<int, int> chiedi(int x) {
    int l = st.PGE(x, st.arr[x], 1, 0, st.arr.size());
    if(l == -1) l = 0;

    int r = st.NGE(x, st.arr[x], 1, 0, st.arr.size());
    if(r == -1) r = st.arr.size()-1;

    return {l, r}; 
}