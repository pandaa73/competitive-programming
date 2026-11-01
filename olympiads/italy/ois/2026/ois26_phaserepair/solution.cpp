#include <bits/stdc++.h>
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

    int N, M; cin >> N >> M;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    sort(all(V));

    int bs = V[0], be = V[N - 1], mn = V[N - 1] - V[0];
    for(int i = 1; i < N; ++i)
        if(V[i - 1] + M - V[i] < mn)
            mn = V[i - 1] + M - V[i], bs = V[i], be = V[i - 1];

    cout << mn << lf;
    for(; bs != be; bs = (bs + 1) % M)
        cout << bs << " ";
    cout << lf;
}
