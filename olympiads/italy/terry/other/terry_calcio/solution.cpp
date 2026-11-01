#include <bits/stdc++.h>
using namespace std;
// flag[10]

const int N = 7e3+1;

int v[N][N];
int p[N][N];

void Solve() {
    int n, m; cin >> n >> m;
    int k, a, b; cin >> k >> a >> b;
    for(int i = 0; i < k; ++i) {
        int x, y; cin >> x >> y;
        v[x][y]++;
    }

    for(int i = 0; i < n; ++i) {
        int ln = 0;
        for(int j = 0; j < m; ++j) {
            ln += v[i][j];
            if(i > 0) p[i+1][j+1] = p[i][j+1];
            p[i+1][j+1] += ln;
        }
    }

    int mn = INT_MAX;
    for(int i = a; i <= n; ++i) {
        for(int j = b; j <= m; ++j) {
            mn = min(p[i][j]+p[i-a][j-b]-p[i][j-b]-p[i-a][j], mn);
        }
    }

    cout << mn;

    for(int i = 0; i < n; ++i) {
        fill(v[i], v[i]+m, 0);
        fill(p[i], p[i]+m+1, 0);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i) cout << "Case #" << i << ": ", Solve(), cout << endl;
}
