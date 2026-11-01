#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 32749;

using ll = long long;

struct matrix_t {
    int mat[2][2];
    matrix_t(void) {
        memset(mat, 0x00, sizeof(mat));
    }

    matrix_t operator*(const matrix_t &other) {
        matrix_t ans;

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k < 2; ++k) {
                    ans.mat[i][j] += this->mat[i][k] * other.mat[k][j];
                    ans.mat[i][j] %= MOD;
                }
            }
        }

        return ans;
    };

    matrix_t operator+(const matrix_t &other) {
        matrix_t ans;

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                ans.mat[i][j] = this->mat[i][j] + other.mat[i][j];
                ans.mat[i][j] %= MOD;
            }
        }

        return ans;
    };
};

matrix_t fexp(matrix_t m, int e) {
    matrix_t ans;
    ans.mat[0][0] = ans.mat[1][1] = 1;

    while(e > 0) {
        if(e&1) ans = ans * m;

        e >>= 1;
        m = m * m;
    }

    return ans;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;

    matrix_t m;

    m.mat[0][0] = 3, m.mat[0][1] = 2;
    m.mat[1][0] = 3, m.mat[1][1] = 3;

    m = fexp(m, n);

    cout << m.mat[0][0] % MOD _ m.mat[1][0] % MOD;   
}