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

    int a, b; cin >> a >> b;
    int c, d; cin >> c >> d;

    int m1, m2;

    m1 = 60 * a + b;
    m2 = 60 * c + d;

    if(m2 < m1) m2 += 24 * 60;

    int m = m2 - m1;

    cout << m / 60 _ m % 60 << lf;
}