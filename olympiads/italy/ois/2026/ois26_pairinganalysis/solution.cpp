#include <bits/stdc++.h>
using namespace std;

/* ========================================================================== */
/*    https://gist.github.com/jakobkogler/c320233e9275f3b6badc12988e9e9e47    */
/* ========================================================================== */

namespace NTT {
    const int mod = 998244353;
    const int root = 15311432;
    const int root_1 = 469870224;
    const int root_pw = 1 << 23;

    long long inverse(long long x, int mod) {
        long long res = 1;
        int e = mod - 2;
        while (e) {
            if (e & 1)
                res = res * x % mod;
            x = x * x % mod;
            e >>= 1;
        }
        return res;
    }

    void fft(vector<int> & a, bool invert) {
        int n = a.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            int wlen = invert ? root_1 : root;
            for (int i = len; i < root_pw; i <<= 1)
                wlen = (int)(1LL * wlen * wlen % mod);

            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len / 2; j++) {
                    int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                    a[i+j] = u + v < mod ? u + v : u + v - mod;
                    a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                    w = (int)(1LL * w * wlen % mod);
                }
            }
        }

        if (invert) {
            int n_1 = inverse(n, mod);
            assert(1LL * n_1 * n % mod == 1);
            for (int & x : a)
                x = (int)(1LL * x * n_1 % mod);
        }
    }


    vector<int> multiply(vector<int> const& a, vector<int> const& b) {
        vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] = (int)(1LL * fa[i] * fb[i] % mod);
        fft(fa, true);
        return fa;
    }
}

/* ========================================================================== */
/*    https://gist.github.com/jakobkogler/c320233e9275f3b6badc12988e9e9e47    */
/* ========================================================================== */

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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, Q; cin >> N >> Q;

    string S; cin >> S;

    vector<int> A(N), T(N), G(N), C(N);
    for(int i = 0; i < N; ++i) {
        switch(S[i]) {
            case 'A': A[i]         = 1; break;
            case 'T': T[N - i - 1] = 1; break;
            case 'G': G[i]         = 1; break;
            case 'C': C[N - i - 1] = 1; break;
            default: assert(0);
        }
    }

    auto AT = NTT::multiply(A, T);
    auto GC = NTT::multiply(G, C);

    vector<ll> pfx(N + 1);
    for(int K = 1; K < N; ++K) {
        pfx[K + 1] = pfx[K]
            + AT[N - K - 1]
            + AT[N + K - 1]
            + GC[N - K - 1]
            + GC[N + K - 1];
    }

    while(Q--) {
        int l, r; cin >> l >> r;
        r++;

        cout << pfx[r] - pfx[l] << lf;
    }
}
