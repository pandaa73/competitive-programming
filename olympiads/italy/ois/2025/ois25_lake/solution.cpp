#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M; cin >> N >> M;

    vector<string> V(N);
    for(auto &x: V) cin >> x;

    int ans = 0;
    for(int i = 1; i < N - 1; ++i) {
        for(int j = 1; j < M - 1; ++j) {
            if(V[i][j] == '.') continue;
                
            ans += 4;

            ans -= V[i - 1][j] == '#';
            ans -= V[i + 1][j] == '#';
            ans -= V[i][j - 1] == '#';
            ans -= V[i][j + 1] == '#';
        }
    }

    cout << ans << lf;
}
