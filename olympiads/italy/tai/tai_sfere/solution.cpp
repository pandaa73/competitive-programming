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

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr ll MAXH = 1e13;

vec<int> V;
vec<ll> H, P;

struct SegTree {
    SegTree(void) {}
    SegTree(int N): N(N), T(2 * N) {
        for(int i = 0; i < N; ++i) {
            T[i + N] = H[V[i]];
        }

        for(int i = N - 1; i > 0; i--) {
            T[i] = T[i << 1] + T[i << 1 | 1];
        }
    }

    void point_set(int n, int x) {
        T[n += N] = H[x];

        for(n >>= 1; n > 0; n >>= 1) {
            T[n] = T[n << 1] + T[n << 1 | 1];
        }
    }

    ll range_sum(int l, int r) {
        ll x = 0;
        for(l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if(l&1) x += T[l++];
            if(r&1) x += T[--r];
        }

        return x;
    }

    int N;
    vec<ll> T;
};

SegTree st;

void inizio(int N, int M, int sfere[]) {
    uniform_int_distribution<ll> dist(0, MAXH);

    V.resize(N);
    H.resize(N);

    for(int i = 0; i < N; ++i) {
        V[i] = sfere[i] - 1;
        H[i] = dist(timmy_loves_gambling);
    }

    P.resize(N);
    P[0] = H[0];
    for(int i = 1; i < N; ++i) {
        P[i] = P[i - 1] + H[i];
    }

    st = SegTree(N);
}

void modifica(int p, int x) {
    st.point_set(p, x - 1);
}

bool verifica(int l, int r) {
    r += 1;

    return st.range_sum(l, r) == P[r - l - 1];
}

#ifdef LOCAL

int main() {
    const int MAXN = 1e5;
    const int MAXM = 1e5;

	int sfere[MAXN], N, M;
	cin>>N>>M;
	for(int i=0;i<N;i++)
		cin>>sfere[i];
	inizio(N, M, sfere);
	for(int i=0;i<M;i++){
		int tipo, a, b;
		cin>>tipo>>a>>b;
		if(tipo==1)
			cout<<(int)verifica(a,b) << lf;
		else modifica(a,b);
	}
	return 0;
}

#endif /* LOCAL */
