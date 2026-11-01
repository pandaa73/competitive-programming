#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

void solve(void) {
    string S; cin >> S;
    const int N = S.size();
    S.push_back('$');

    vector<string> V; V.reserve(N);

    vector<int> A(26), B(26);
    for(int i = 0; i < N; ++i) {
        int j = S[i] - 'a';

        if(S[i] == S[i + 1]) {
            V.emplace_back(2, S[i]);

            B[j] += 1;
            i += 1;
        } else {
            V.emplace_back(1, S[i]);

            A[j] += 1;
        }
    }

    bool ok = 1;
    for(int i = 0; i < 26; ++i) {
        ok &= A[i] <= 1;
        ok &= B[i] <= 1;
    }

    if(!ok) {
        cout << -1 << lf;
        return;
    }

    for(const auto &s: V) {
        cout << s << " ";
    }

    cout << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
