#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 10;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int ask(int i, int j) {
    cout << "?" _ i + 1 _ j + 1 << ff;

    int x; cin >> x;
    return x;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> rep(LOG, -1);
    for(int i = 0; i < N; ++i)
        rep[ask(i, i)] = i;

    vector<int> ans(N);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < LOG; ++j) {
            int x = ask(i, rep[j]);

            ans[i] |= (x == j) << j;
        }
    }

    cout << "!";
    for(auto x: ans)
        cout << " " << x;
    cout << ff;
}
