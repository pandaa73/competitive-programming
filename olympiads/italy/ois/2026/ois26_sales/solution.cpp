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

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

template<typename T>
void chmax(T &a, T b) {
    a = max(a, b);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    int M; cin >> M;
    vector<int> A(M), B(M);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    vector<int> W(N + 1);
    for(int i = 0; i < M; ++i) {
        chmax(W[A[i]], B[i]);
    }

    for(int i = N - 1; i >= 0; i--) {
        chmax(W[i], W[i + 1]);
    }

    int ans = 1, x = 0;
    for(int i = 0, j = -1; i < N; ++i) {
        x += V[i];

        if(x <= W[i - j]) continue;

        ans++;
        x = V[i];
        j = i - 1;
    }

    cout << ans << lf;
}
