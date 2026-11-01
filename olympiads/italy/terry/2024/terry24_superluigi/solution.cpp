#include <bits/stdc++.h>
using namespace std;

/* ඞඞ flag[10] ඞඞ */

#define ff endl
#define lf "\n"
#define _ << " " <<

using ll = long long;

constexpr int N = 1e3+7;
constexpr int M = 1e4+7;
constexpr int MOD = 1e9+7;

vector<int> dp[N];
vector<int> heights[N];

#define height(i, j) (h[i] + d[i]*j)

void solve(void) {  
    int n, m; cin >> n >> m;

    int h[n], d[n];
    for(auto &x: h) cin >> x;
    for(auto &x: d) cin >> x;

    for(int i = 0; i < n; ++i) {
        dp[i].resize(m);
        heights[i].resize(m);

        for(int j = 0; j < m; ++j) {
            heights[i][j] = height(i, j);
        }
    }

    for(int i = 0; i < m; ++i) {
        dp[0][i] = height(0, i);
    }

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            auto it = upper_bound(heights[i-1].begin(), heights[i-1].end(), height(i, j));

            int up = it-heights[i-1].begin();
            int down = it-heights[i-1].begin()-1;
            if(up == m) up = 1;

            // cout << up _ down _ m << ff;

            // cout << ia _ ib << " ";

            // if(ia != -1) cout << height(i-1, ia) << " ";
            // if(ib != -1) cout << height(i-1, ib) << " ";
            // cout << height(i, j) << lf;

            dp[i][j] = INT_MAX;

            if(up != -1) dp[i][j] = min(dp[i][j], dp[i-1][up] + abs(height(i, j)-height(i-1, up)));
            if(down != -1) dp[i][j] = min(dp[i][j], dp[i-1][down] + abs(height(i, j)-height(i-1, down)));
        }
    }

    int mn = INT_MAX;
    for(int i = 0; i < m; ++i)
        mn = min(mn, dp[n-1][i]);

    cout << mn;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve(), cout << ff;
}