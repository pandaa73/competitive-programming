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

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    #ifndef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int N; cin >> N;

    string A, B; cin >> A >> B;

    string S = A + "$" + B + B;
    const int M = S.size();

    int l = 1;
    vec<int> z(M);
    for(int i = 1; i < M; ++i) {
        if(i >= l + z[l]) l = i;
        z[i] = z[i - l];
        while(i + z[i] < M && S[i + z[i]] == S[z[i]]) z[i] += 1;
        if(i + z[i] > l + z[l]) l = i;
    }

    bool ok = 0;
    for(int i = N + 1; i < M; ++i) {
        ok |= z[i] == N;
    }

    cout << ok << lf;
}
