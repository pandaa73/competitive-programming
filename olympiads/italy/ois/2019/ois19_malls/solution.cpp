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

    vector<int> v(n);
    for(auto &x: v) cin >> x;

    sort(v.begin(), v.end());

    int mx = v[0], ans = 0;

    int sus = k - v[n - 1];
    if(k - v[n - 1] > mx)
        mx = sus, ans = k;

    for(int i = 0; i < n - 1; ++i) {
        int m = (v[i] + v[i + 1]) / 2;

        sus = m - v[i];
        if(m - v[i] > mx)
            mx = sus, ans = m;
    }

    cout << ans << lf;
}