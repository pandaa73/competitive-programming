#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    int n, k; cin >> n >> k;

    vector<int> s;

    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        if(s.empty() || x != s.back()) s.push_back(x);
        else s.pop_back();
    }

    cout << s.empty() << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}