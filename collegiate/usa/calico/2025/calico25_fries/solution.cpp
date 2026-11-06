// Does not solve the last bonus test set (L <= 5000)

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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int MAXC = 1250;
constexpr int MOD = 1e9+7;

int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
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

template<int N, int M>
using Matrix = array<array<int, M>, N>;

template<int N, int O, int M>
Matrix<N, M> mul(const Matrix<N, O> &A, const Matrix<O, M> &B) {
    Matrix<N, M> mtx = {};

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            for(int k = 0; k < O; ++k) {
                chadd(mtx[i][j], mul(A[i][k], B[k][j]));
            }
        }
    }

    return mtx;
}

template<int N>
void chmul(Matrix<N, N> &A, const Matrix<N, N> &B) {
    A = mul<N, N, N>(A, B);
}

template<int N>
Matrix<N, N> fexp(Matrix<N, N> mtx, int e) {
    Matrix<N, N> ans = {};
    for(int i = 0; i < N; ++i) {
        ans[i][i] = 1;
    }

    while(e > 0) {
        if(e&1) {
            chmul<N>(ans, mtx);
        }

        e >>= 1;
        chmul<N>(mtx, mtx);
    }

    return ans;
}

void solve(void) {
    int N, K; cin >> N >> K;

    string S; cin >> S;

    int l = 0;
    vec<int> A(MAXC + 1), B(MAXC + 1);

    for(int i = 0; i < N; ++i) {
        if(S[i] == '(') {
            l += 1;
        } else if(S[i] == ')') {
            l -= 1;
        } else if(S[i] == 'O') {
            A[l] += 1;
        } else {
            B[l] += 1;
        }
    }

    Matrix<MAXC + 1, MAXC + 1> mtx = {};

    mtx[0][0] = 1;
    for(int i = 1; i <= MAXC; ++i) {
        mtx[0][i] = B[i];
        mtx[1][i] = A[i];
    }

    for(int i = 2; i <= MAXC; ++i) {
        mtx[i][i - 1] = 1;
    }

    mtx = fexp<MAXC + 1>(mtx, K);

    Matrix<MAXC + 1, 1> base = {};

    base[0][1] = 1;

    cout << mul<MAXC + 1, MAXC + 1, 1>(mtx, base)[0][0] << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) {
        solve();
    }
}
