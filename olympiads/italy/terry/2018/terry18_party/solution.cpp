#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int MOD = 1e9+7;
constexpr int MAXN = 3e2+7;
constexpr int MAXC = 2e2+7;

using ll = long long;

void solve(void) {
    int N; cin >> N;

    int sum = 0;
    while(N--) {
        int x; cin >> x;
        if(x > 0) sum += x;
    }

    cout << sum << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    for(int i = 1; i <= t; ++i)
        cout << "Case #" << i << ": ", solve();
}
