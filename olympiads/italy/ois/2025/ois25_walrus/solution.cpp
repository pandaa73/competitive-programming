#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    int n; cin >> n;
    string s; cin >> s;

    int cnt = 0;

    int sz = 0;
    char last = '-';

    vector<int> v;
    for(auto c: s) {
        if(last == '-' && c == '.')
            ++cnt, sz = 0;

        if(last == '.' && c == '-')
            v.push_back(sz);

        ++sz;
        last = c;
    }

    if(last == '.')
        v.push_back(sz);
    sort(v.rbegin(), v.rend());


    int ans = 0;
    for(int i = 0; i < v.size(); ++i)
        ans = max(ans, 1 + i + v[i]/2);

    cout << cnt _ ans << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}
