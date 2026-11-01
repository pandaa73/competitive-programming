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

    int n, k; cin >> n >> k;

    ll ans1 = 0, ans2 = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        if(x < k) {
            ans2 += x;
            continue;
        }

        if(x == 11 * k) {
            ans1 += 11;
            continue;
        }

        if(x > 11 * k) {
            ans1 += 10;
            ans2 += x - 10 * k;
            continue;
        }

        ans1 += x / k;
        ans2 += x % k;
    }

    cout << ans1 _ ans2 << lf;
}