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

ll revenue(int N, int K, vector<ll> A) {
    sort(all(A));

    vector<ll> pfx(N + 1, 0);
    for(int i = 0; i < N; ++i)
        pfx[i + 1] = A[i] + pfx[i];

    vector<ll> V(N);
    for(int i = 0; i < N; ++i)
        V[i] = abs(A[i]);

    sort(rall(V));

    ll ans = 0;

    int l = 0, r = N;
    for(auto q: V) {
        while(l < N && A[l] < -q) l++;
        while(r > 0 && A[r - 1] > q) r--;

        ll x = pfx[r] - pfx[l] + q * (N - r - l - K);

        ans = max(ans, x);
    }

    return ans;
}
