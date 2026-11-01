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
    /* range set; */
    /* range add; */
    /* range sum; */
    /* range min; */
    /* range lower_bound. */

    void init(int size, vector<ll> &V) {
        N = size;
        H = 31 - __builtin_clz(N);

        sz.resize(N);
        lz.resize(N);
        zero.resize(N);

        mn.resize(2 * N);
        sum.resize(2 * N);

        for(int i = 0; i < N; ++i)
            mn[i + N] = sum[i + N] = V[i];

        for(int i = N - 1; i > 0; i--) {
            mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
            sum[i] = sum[i << 1] + sum[i << 1 | 1]; 

            sz[i] = i << 1 >= N ? 2 : sz[i << 1] + sz[i << 1 | 1]; 
        }
    }

    void apply(int v, ll x, bool s) {
        if(v >= N) {
            if(s)
                mn[v] = sum[v] = x;
            else mn[v] = sum[v] += x;

            return;
        }

        if(s) {
            lz[v] = x;
            zero[v] = 1;
        
            mn[v] = x;
            sum[v] = x * sz[v];

            return;
        }

        lz[v] += x;

        mn[v] += x;
        sum[v] += x * sz[v];
    }

    void propagate(int v) {
        for(int h = H; h > 0; h--) {
            int i = v >> h;

            apply(i << 1, lz[i], zero[i]);
            apply(i << 1 | 1, lz[i], zero[i]);

            lz[i] = zero[i] = 0;
        }
    }

    void build(int i) {
        for(i >>= 1; i > 0; i >>= 1) {
            apply(i << 1, lz[i], zero[i]);
            apply(i << 1 | 1, lz[i], zero[i]);

            lz[i] = zero[i] = 0;

            mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
            sum[i] = sum[i << 1] + sum[i << 1 | 1];
        }
    }

    void range_set(int l, int r, ll x) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, x, 1);
            if(r&1) apply(--r, x, 1);
        }

        build(l0), build(r0);
    };

    void range_add(int l, int r, ll x) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        propagate(l0), propagate(r0);

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) apply(l++, x, 0);
            if(r&1) apply(--r, x, 0);
        }

        build(l0), build(r0);
    }

    ll range_sum(int l, int r) {
        ll ans = 0;
        l += N, r += N;

        propagate(l), propagate(r - 1);
            
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans += sum[l++];
            if(r&1) ans += sum[--r];
        }

        return ans;
    }

    ll range_min(int l, int r) {
        ll ans = LLONG_MAX;

        l += N, r += N;
        propagate(l), propagate(r - 1);

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans = min(ans, mn[l++]);
            if(r&1) ans = min(ans, mn[--r]);
        }

        return ans;
    }

    int lower_bound(int l, int r, ll x) {
        l += N, r += N;
        propagate(l), propagate(r - 1);

        int vl = -1, vr = -1;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) if(mn[l++] <= x) {
                vl = l - 1;
                break;
            }
            if(r&1) if(mn[--r] <= x) vr = r;
        }

        int v = vl < 0 ? vr : vl;

        if(v < 0) return -1;

        while(v < N) {
            apply(v << 1, lz[v], zero[v]);
            apply(v << 1 | 1, lz[v], zero[v]);

            lz[v] = zero[v] = 0;
    
            v <<= 1;

            if(mn[v] > x)
                v++;
        }

        return v - N;
    }

    int N;
    int H;
    vector<ll> lz;
    vector<ll> mn;
    vector<ll> sum;
    vector<int> sz;
    vector<bool> zero;
};

SegTree st;

void init(vector<long long> a) {
    st.init(a.size(), a);
}

void set_range(int l, int r, long long x) {
    st.range_set(l, r, x);
}

void add(int l, int r, long long x) {
    st.range_add(l, r, x);
}

long long get_sum(int l, int r) {
    return st.range_sum(l, r);
}

long long get_min(int l, int r) {
    return st.range_min(l, r);
}

int lower_bound(int l, int r, long long x) {
    return st.lower_bound(l, r, x);
}
