#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int add(int a, int b) {
    int x = a + b;

    if(x >= MOD) {
        return x - MOD;
    } else return x;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return ((ll)a * b) % MOD;
}

void chmul(int &a, int b) {
    a = mul(a, b);
}

int fexp(int b, int e) {
    int x = 1;

    while(e > 0) {
        if(e&1) chmul(x, b);

        e >>= 1;
        chmul(b, b);
    }

    return x;
}

int inv(int n) {
    return fexp(n, MOD - 2);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> fact(2 * N + 1); fact[0] = 1;
    for(int i = 1; i <= 2 * N; ++i) {
        fact[i] = mul(i, fact[i - 1]);
    }

    auto catalan = [&](int n) -> int {
        return mul(fact[2 * n], inv(mul(fact[n], fact[n + 1])));
    };

    cout << add(fact[N], MOD - catalan(N)) << lf;
}
