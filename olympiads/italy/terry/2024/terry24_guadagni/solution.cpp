#include <algorithm>
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

void solve(void) {
    int N, K, L; cin >> N >> K >> L;

    vector<int> V(N);
    for(auto &x: V) cin >> x;

    int i = K, t = V[0];
    auto calc = [&](int pos) -> int {
        return pos - t;
    };

    auto calc_r = [&](int pos) -> int {
        return pos + t;
    };

    while(i < L) {
        auto it = upper_bound(all(V), i);

        assert(it != V.begin());

        auto pit = prev(it);
        if(*pit - i < K) i += K;

        if(it != V.end() && calc(*it) < i) {
            i += K;
            continue;
        }

        int r = L;
        if(it != V.end())
            r = calc(*it);

        t += r - *pit - 1;
        i = r + K;
    }

    cout << t << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
