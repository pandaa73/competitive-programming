#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;

    vector<int> A(N), B(N);
    for(auto &x: A) cin >> x;
    for(auto &x: B) cin >> x;

    for(int i = 0; i < N; ++i) {
        if(abs(A[i] - B[i]) <= K)
            continue;

        cout << "NO" << lf;
        return 0;
    }

    cout << "YES" << lf;
}
