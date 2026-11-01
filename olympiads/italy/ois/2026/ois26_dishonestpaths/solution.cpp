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

constexpr int LOG = 20;
constexpr int MOD = 998244353;
constexpr int MAXN = 1e5+7;

int add(int a, int b) {
    int x = (a + b);

    if(x >= MOD)
        return x - MOD;
    return x;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return ((ll)a * b) % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

template<size_t N, size_t M = N>
struct Matrix {
    Matrix(void) {
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
                mtx[i][j] = 0;
    }

    Matrix(initializer_list<initializer_list<int>> init) {
        assert(init.size() == N);

        int i = 0;
        for(auto &v: init) {
            assert(v.size() == M);

            int j = 0;

            for(auto &x: v)
                mtx[i][j++] = x;

            i++;
        }
    }

    array<int, M> &operator[](int idx) {
        assert(0 <= idx && idx < N);

        return mtx[idx];
    }

    static Matrix id(void) {
        assert(N == M);

        Matrix ans;

        for(int i = 0; i < N; ++i)
            ans[i][i] = 1;

        return ans;
    }

    void print(int id = -1) {
        infof("----- Matrix -----");
        infof("--- id = %5d ---", id);

        for(int i = 0; i < N; ++i) {
            infor("\t%9d", mtx[i][0]);
            for(int j = 1; j < M; ++j)
                infor(" %9d", mtx[i][j]);
            infof("");
        }

        infof("----- xirtaM -----");
    }

    array<array<int, M>, N> mtx;
};

template<size_t N, size_t K, size_t M>
Matrix<N, M> mul(Matrix<N, K> a, Matrix<K, M> b) {
    Matrix<N, M> c;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            for(int k = 0; k < K; ++k)
                chadd(c[i][j], mul(a[i][k], b[k][j]));
        }
    }

    return c;
}

template<size_t N>
void chmul(Matrix<N> &a, Matrix<N> b) {
    a = mul(a, b);
}

template<size_t N>
Matrix<N> pow(Matrix<N> dp, size_t exp) {
    Matrix<N> ans = Matrix<N>::id();

    while(exp > 0) {
        if(exp&1) chmul(ans, dp);

        exp >>= 1;
        chmul(dp, dp);
    }

    return ans;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll N, M; cin >> N >> M;

    vector<ll> idx;
    map<ll, bitset<2>> bad;
    for(int i = 0; i < M; ++i) {
        ll u, v; cin >> u >> v;
        u--, v--;

        if(u > v) swap(u, v);

        idx.push_back(u);
        bad[u][v - u - 1] = 1;
    }

    sort(all(idx));
    idx.resize(unique(all(idx)) - idx.begin());

    const Matrix<3> mtx = {
        {1, 1, 1},
        {1, 0, 0},
        {0, 1, 0}
    };

    Matrix<3, 1> dp = {
        {1},
        {0},
        {0}
    };

    auto i = N - 1;
    while(!idx.empty()) {
        auto u = idx.back();

        if(u < i) dp = mul(pow(mtx, i - u - 1), dp), i = u + 1;

        for(auto v = u; v >= max(0LL, u - 1); i = v--) {
            if(v >= i) continue;

            Matrix<3, 1> new_dp;
            new_dp[1][0] = dp[0][0];
            new_dp[2][0] = dp[1][0];

            if(!bad[v][0])
                chadd(new_dp[0][0], dp[0][0]);
            if(!bad[v][1])
                chadd(new_dp[0][0], dp[1][0]);
            if(!bad[v][1] && !bad[v + 1][0] && !bad[v + 1][1])
                chadd(new_dp[0][0], dp[2][0]);

            swap(dp, new_dp);
        }

        idx.pop_back();
    }

    dp = mul(pow(mtx, i), dp);

    cout << dp[0][0] << lf;
}
