#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

constexpr int ROOT = 64;

void solve(void) {
    int N, M, K; cin >> N >> M >> K;

    infof("N = %d | M = %d | K = %d", N, M, K);

    vector V(N, vector<bitset<2 * ROOT>>(M));

    vector<int> A(K), B(K), C(K);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;
    for(auto &x: C) cin >> x;

    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < B[i]; ++j)
            V[A[i]][j][2 * ROOT - 1] = 1;
        for(int j = C[i] + 1; j < M; ++j)
            V[A[i]][j][2 * ROOT - 1] = 1;
    }

    auto add_vel = [&](int x, int y, int k) -> void {
        if(y < 0 || y >= M) return;

        V[x][y][0] = V[x][y][k] = 1;
    };

    add_vel(0, M/2, ROOT);

    for(int x = 0; x < N; ++x) {
        for(int y = 0; y < M; ++y) {
            if(!V[x][y][0] || V[x][y][2 * ROOT - 1]) continue;

            if(x == N - 1) return (void)(cout << "YES" << lf);

            for(int k = 2; k < 2 * ROOT - 2; ++k) {
                if(!V[x][y][k]) continue;

                int z = y + k - ROOT;

                add_vel(x + 1, z - 1, k - 1);
                add_vel(x + 1, z + 0, k + 0);
                add_vel(x + 1, z + 1, k + 1);
            }
        }
    }

    cout << "NO" << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
