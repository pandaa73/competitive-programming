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

    string a, b; cin >> a >> b;

    ll av[4] = {0}, bv[4] = {0};

    for(int i = 0, j = 0; i < a.size(); ++i) {
        if(a[i] == '.') {
            ++j; continue;
        }

        av[j] = av[j] * 10 + a[i] - 0x30;
    }

    for(int i = 0, j = 0; i < b.size(); ++i) {
        if(b[i] == '.') {
            ++j; continue;
        }

        bv[j] = bv[j] * 10 + b[i] - 0x30;
    }

    ll ax = 0, bx = 0;
    ll pow = 1;
    for(int i = 3; i >= 0; i--, pow *= 256) {
        ax += pow * av[i];
        bx += pow * bv[i];
    }

    cout << 1 + bx - ax << lf;
}