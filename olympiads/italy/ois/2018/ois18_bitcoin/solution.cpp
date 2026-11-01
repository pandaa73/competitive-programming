#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;
using ld = long double;

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, price; cin >> n >> price;

    ld x = 0;
    ld bit = 1;
    for(int i = 0; i < n; ++i) {
        int d; cin >> d;

        if(d < 0 && bit != 0) {
            x = bit * price;
            bit = 0;
        }

        if(d > 0 && x != 0) {
            bit = x / price;
            x = 0;
        }

        price += d;
    }

    if(bit != 0) {
        x = bit * price;
        bit = 0;
    }

    cout << x << lf;
}