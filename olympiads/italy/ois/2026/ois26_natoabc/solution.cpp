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

const array<int, 26> len = {
    5, 5, 7, 5, 4, 7,
    4, 5, 5, 7, 4, 4,
    4, 8, 5, 4, 6, 5,
    6, 5, 7, 6, 7, 4,
    6, 4
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string S; cin >> S;

    const int N = S.size();

    string T = "";
    for(int i = 0; i < N; i += len[S[i] - 'a']) {
        T.push_back(S[i]);
    }

    cout << T << lf;
}
