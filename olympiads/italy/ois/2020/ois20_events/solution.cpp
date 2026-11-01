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

    vector<int> a(n), b(m);
    for(auto &x: a) cin >> x;
    for(auto &x: b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int cnt = 0;

    for(int i = 0, j = 0; i < a.size() && j < b.size(); ++i) {
        while(j < b.size() && a[i] >= b[j]) ++j;
        if(j >= b.size()) break;

        ++cnt, ++j;
    }

    cout << cnt << lf;
}
