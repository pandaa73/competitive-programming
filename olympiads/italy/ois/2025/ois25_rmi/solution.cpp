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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int X, Y, N; cin >> X >> Y >> N;

    int S = X + Y;

    vec<int> A(N), B(N);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    int n = 1, m = N + 1;

    sort(rall(A)), sort(all(B));
    for(int i = 0, j = 0; i < N; ++i) {
        while(j < N && A[i] + B[j] <= S) j += 1;

        if(j == N) break;

        j += 1;
        n += 1;
    }

    swap(A, B);
    for(int i = 0, j = 0; i < N; ++i) {
        while(j < N && A[i] + B[j] > S) j += 1;

        if(j == N) break;

        j += 1;
        m -= 1;
    }

    cout << m _ n << lf;
}
