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

    int A, B, C; cin >> A >> B >> C;
    int D, E, F; cin >> D >> E >> F;

    cout << (max(A, D) + max(B, E) + max(C, F))
        - (min(A, D) + min(B, E) + min(C, F)) << lf;
}
