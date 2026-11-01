#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 64;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

vector<vector<char>> solve(ll K) {
    constexpr int N = 200;

    vector<vector<char>> ans(N, vector<char>(N, '#'));
    
    for(int i = 0; i < N; ++i)
        ans[0][i] = ans[N - 1][i] = '.';

    for(int lg = 1; lg < LOG; ++lg) {
        for(int i = 0; i < lg; ++i) {
            int j = N - (3 * lg) - 1 + i;

            ans[2 * i][j]
                = ans[2 * i][j + 1]
                = ans[2 * i + 1][j]
                = ans[2 * i + 1][j + 1]
                = '.';
        }
    }

    auto fill = [&](int i, int j) -> void {
        for(; i < N; ++i) ans[i][j] = '.';
    };

    int i = 0;
    while(K > 0) {
        if(K&1) fill(2 * i, N - 2 * i - 1);

        ++i;
        K >>= 1;
    }

    return ans;
}
