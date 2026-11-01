#include <bits/stdc++.h>
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

int add(int a, int b) {
    int x = a + b;
    if(x >= MOD) {
        return x - MOD;
    } else return x;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

template<size_t N>
using Matrix = array<array<int, N>, N>;

template<size_t N>
Matrix<N> mul(const Matrix<N> &a, const Matrix<N> &b) {
    Matrix<N> c = {};

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                chadd(c[i][j], mul(a[i][k], b[k][j]));
            }
        }
    }

    return c;
};

template<size_t N>
void chmul(Matrix<N> &a, const Matrix<N> &b) {
    a = mul(a, b);
}

template<size_t N>
Matrix<N> fexp(Matrix<N> b, int e) {
    Matrix<N> a = {};
    for(int i = 0; i < N; ++i) {
        a[i][i] = 1;
    }

    while(e > 0) {
        if(e&1) chmul(a, b);

        e >>= 1;
        chmul(b, b);
    }

    return a;
}

int progetti(int N, int K) {
    Matrix<5> m = {};

    m[0][0] = 1;
    for(int i = 1; i < K; ++i) {
        m[0][i] = 1;
        m[i][i - 1] = 1;
    }

    m = fexp(m, N);

    return m[0][0];
}

#ifdef LOCAL
static FILE *fr, *fw;

// Declaring variables
static int N;
static int K;
static int risultato;

// Declaring functions
int progetti(int N, int K);

int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
    fscanf(fr, "%d %d", &N, &K);

	// Calling functions
	risultato = progetti(N, K);

	// Writing output
    fprintf(fw, "%d\n", risultato);

	fclose(fr);
	fclose(fw);
	return 0;
}
#endif
