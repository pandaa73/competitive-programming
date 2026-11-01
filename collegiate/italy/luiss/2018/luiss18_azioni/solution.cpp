#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;

    int mxd = 0;
    int last; cin >> last;
    for(int i = 1; i < n; ++i) {
        int x; cin >> x;

        mxd = max(mxd, max(x, last) - min(x, last));

        last = x; 
    }

    cout << mxd << lf;
}