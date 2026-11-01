#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

const vec<int> A = {
    6, 2, 5, 5, 4, 5, 6, 3, 7, 6
};

const vec<int> C = {
    6, 8, 13, 18, 22, 27, 33, 36, 43, 49
};

const vec<int> D = {
    0, 2, 7, 12, 16, 21, 27, 30, 37, 43
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ll N; cin >> N;

    ll x = 0;
    for(ll pow = 1; pow <= N;) {
        x -= pow * A[0];

        ll a = N / pow / 10;
        ll b = N % pow;
        ll c = (N / pow) % 10;

        x += C[9] * a * pow;

        if(c > 0) {
            x += C[c - 1] * pow;
        }

        x += A[c] * (b + 1);
        pow *= 10;
    }

    cout << x + A[0] << lf;
}
