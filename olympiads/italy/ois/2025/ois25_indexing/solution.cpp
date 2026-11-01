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

    string S, T; cin >> S >> T;

    const int N = max(S.size(), T.size());

    S.resize(N + 1, 'a' - 1);
    T.resize(N + 1, 'a' - 1);

    string ans = "";

    int i = 0;
    for(; i < N; ++i) {
        if(S[i] == T[i]) {
            ans.push_back(S[i]);
        } else break;
    }

    if(S[i] + 1 < T[i] || T[i + 1] > 'a' - 1) {
        ans.push_back(S[i] + 1);
        cout << ans << lf;
        return 0;
    }

    if(S[i] == 'a' - 1) {
        ans.push_back('a');
        if(T[i] == 'a' && T[i + 1] == 'a' - 1) {
            cout << -1 << lf;
        } else cout << ans << lf;

        return 0;
    }

    ans.push_back(S[i]);
    ans.push_back('z');
    for(i += 1; i < N && S[i] == 'z'; ++i) {
        ans.push_back('z');
    }

    cout << ans << lf;
}
