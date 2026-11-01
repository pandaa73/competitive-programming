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

vector<int> fact;

int add(int a, int b) {
    int x = a + b;

    return x < MOD ? x : x - MOD;
}

void chadd(int &a, int b) {
    a = add(a, b);
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
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

int inv(int x) {
    return fexp(x, MOD - 2);
}

int choose(int n, int k) {
    return mul(fact[n], inv(mul(fact[k], fact[n - k])));
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    fact.resize(N + 1); fact[0] = 1;
    for(int i = 1; i <= N; ++i) {
        fact[i] = mul(fact[i - 1], i);
    }

    sort(all(V));

    vector<pii> U; U.reserve(N);

    U.emplace_back(1, V[0]);
    for(int i = 1; i < N; ++i) {
        if(V[i] == U.back().se) {
            U.back().fi += 1;
        } else U.emplace_back(1, V[i]);
    }

    sort(rall(U));
    U.emplace_back(0, 0);

    int x = 1, y = U[0].fi;
    for(int i = 1; i < U.size(); ++i) {
        if(U[i - 1].fi == U[i].fi) continue;

        for(; y > U[i].fi; y--) {
            int t = 0;
            for(int j = 0; j < i; ++j) {
                int c = choose(U[j].fi, y);

                chadd(t, add(c, mul(t, c)));
            }

            chadd(x, t);
        }
    }

    cout << x << lf;
}
