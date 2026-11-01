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

#ifndef DEBUG

constexpr int MAXN = 3e3+7;

#else

constexpr int MAXN = 16;

#endif

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    vector<bitset<MAXN>> kpl(N + 1), kpr(N + 1);
    kpl[0][0] = 1;
    kpr[N][0] = 1;

    for(int i = 0; i < N; ++i) {
        int j = N - i - 1;

        int x = V[i];
        int y = V[j];

        kpl[i + 1] = kpl[i] | kpl[i] << x;
        kpr[j] = kpr[j + 1] | kpr[j + 1] << y;
    }

    #ifdef DEBUG

    infof("knapsack-left:");
    infor("i: ");
    for(int i = 0; i < MAXN; ++i)
        infor("%X", MAXN - i - 1);
    infof("");
    for(int i = 0; i <= N; ++i) {
        infor("%d: ", i);
        cerr << kpl[i] << lf;
    }
    infof("");

    infof("knapsack-right:");
    infor("i: ");
    for(int i = 0; i < MAXN; ++i)
        infor("%X", MAXN - i - 1);
    infof("");
    for(int i = 0; i <= N; ++i) {
        infor("%d: ", i);
        cerr << kpr[i] << lf;
    }
    infof("");
    #endif

    for(int i = 0; i < N; ++i) {
        bool b = 0;

        for(int x = 0; x <= K; ++x) {
            int y = K - x;

            b |= kpl[i][x] && kpr[i + 1][y];
        }

        cout << (b ? "NO" : "YES") << lf;
    }
}
