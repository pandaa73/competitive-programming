#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    if(n > m) {
        cout << -1 << lf;
        return 0;
    }

    for(int i = 0; i < m; ++i)
        cout << '.';
    cout << lf;

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(i == j + 1)
                cout << '#';
            else cout << '.';
        }

        cout << lf;
    }
}
