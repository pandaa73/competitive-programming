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

    map<string, int> m = {
        {"espresso", 1},
        {"espresso-doppio", 2},
        {"cappuccino", 1},
        {"affogato", 2},
        {"dead-eye", 3},
        {"irish-coffee", 2},
    };

    int N; cin >> N;

    int s = 0;
    for(int i = 0; i < N; ++i) {
        string S; cin >> S;

        s += m[S];
    }

    cout << (s + 1) / 2 << lf;
}
