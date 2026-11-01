#include <bits/stdc++.h>
#include <iomanip>
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    constexpr int N = 3;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    set<array<int, 2>> s;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j)
            s.insert({min(V[i], V[j]), max(V[i], V[j])});
    }

    cout << s.size() << lf;
}
