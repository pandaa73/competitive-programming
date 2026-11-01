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
    
    vector<int> v(n), p(n), c(n);
    for(auto &x: v) cin >> x;
    for(auto &x: p) cin >> x;
    for(auto &x: c) cin >> x;

    int money = 0, m = 0, g = 0;
    for(int i = 0; i < n; ++i) {
        if(c[i] >= v[i] - p[i]) {
            money += c[i];
            continue;
        }

        if(money < p[i]) {
            m += p[i] - money;
            money = p[i];
        }

        money -= p[i];
        g += v[i];
    }

    g += money - m;

    cout << g _ m << lf;
}