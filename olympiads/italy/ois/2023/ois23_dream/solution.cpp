#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
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

constexpr int LOG = 6;
constexpr int MOD = 666'013;
constexpr int MAXN = 1e5+7;

int add(int a, int b) {
    return (a + b) % MOD;
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
    int ans = 1;
    while(e > 0) {
        if(e&1) chmul(ans, b);

        e >>= 1;
        chmul(b, b);
    }

    return ans;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int K, X; cin >> K >> X;

    const int K0 = K;

    int ans = mul(K, add(1, fexp(10, X - 1)));

    for(int lg = 0; lg < LOG; ++lg) {
        int w = fexp(10, X / 2 + lg) + fexp(10, X / 2 - lg - 1);

        int x = K % 10;
        K /= 10;

        int p = fexp(10, lg);

        int a = mul(45, mul(K, p));
        int b = mul(x * (x - 1) / 2, p);
        int c = mul(x, K0 % p);

        int y = add(a, add(b, c));

        chadd(ans, mul(w, y));

        infof("lg = %d: (%d, %d) -> w = %d | y = %d", lg, K, x, w, y);

        if(K == 0) break;
    }

    cout << ans << lf;
}
