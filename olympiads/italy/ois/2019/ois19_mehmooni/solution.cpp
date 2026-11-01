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

    int n; cin >> n;

    vector<tuple<int, bool>> v;
    for(int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        v.push_back({a, 0});
        v.push_back({b, 1});
    }

    sort(v.begin(), v.end());

    ll ans = 0;
    int cnt = 1;
    for(auto [t, x]: v) {
        cnt -= x;

        ans += cnt;

        if(!x) ++cnt;
    }

    cout << ans << lf;
}