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

    vector<string> V(N);
    for(auto &x: V) cin >> x;

    int mx = 0;
    vector W(N, vector<array<int, 4>>(M));
    for(int i = N - 1; i >= 0; i--) {
        for(int j = M - 1; j >= 0; j--) {
            if(i + 1 < N && V[i][j] == V[i + 1][j])
                W[i][j][0] = 1 + W[i + 1][j][0];
            if(j + 1 < M && V[i][j] == V[i][j + 1])
                W[i][j][1] = 1 + W[i][j + 1][1];
            if(i + 1 < N && j + 1 < M && V[i][j] == V[i + 1][j + 1])
                W[i][j][2] = 1 + W[i + 1][j + 1][2];

            mx = max({mx, W[i][j][0], W[i][j][1], W[i][j][2]});
        }
    }

    for(int i = 1; i < N; ++i) {
        for(int j = M - 2; j >= 0; j--) {
            if(V[i][j] == V[i - 1][j + 1])
                W[i][j][3] = 1 + W[i - 1][j + 1][3];

            mx = max(mx, W[i][j][3]);
        }
    }

    cout << mx + 1 << lf;
}
