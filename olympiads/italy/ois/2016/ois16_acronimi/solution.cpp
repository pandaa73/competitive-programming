#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int M = 1e2+7;
constexpr int MOD = 1e9+7;

using ll = long long;

ll dp[N][M];

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string a, b; cin >> a >> b;

    int n = b.size(), m = a.size();    

    for(int i = n - 1; i >= 0; i--)
        dp[i][m - 1] = dp[i + 1][m - 1] + (b[i] == a[m - 1]);

    for(int j = m - 2; j >= 0; j--) {
        for(int i = n - 2; i >= 0; i--) {
            dp[i][j] = dp[i + 1][j];

            if(b[i] == a[j]) dp[i][j] = (dp[i][j] + dp[i + 1][j + 1]) % MOD;
        }
    }

    cout << dp[0][0] << lf;
}