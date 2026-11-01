#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

#define h(x) (sus == x ? (sus = -1, x + 1) : x)

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    int a, c; cin >> a >> c;

    auto f = [&](int r, int g, int b){
        return a * (r * r + g * g + b * b) + c * min({r, g, b});
    };

    int r, g, b; cin >> r >> g >> b;

    string ans[] = {
        "RED",
        "GREEN",
        "BLUE"
    };

    int mx = r, mxc = 0;
    if(g > mx) mx = g, mxc = 1;
    if(b > mx) mx = b, mxc = 2;

    int mn = r, mnc = 0;
    if(g < mn) mn = g, mnc = 1;
    if(b < mn) mn = b, mnc = 2;

    int sus;
    
    sus = mx;
    int mxf = f(h(r), h(g), h(b));

    sus = mn;
    int mnf = f(h(r), h(g), h(b));

    cout << ans[(mxf > mnf ? mxc : mnc)] << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve();
}