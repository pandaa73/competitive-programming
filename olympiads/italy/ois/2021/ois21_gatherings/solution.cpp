#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k; cin >> n >> k;

    ll ans = 0;

    queue<int> q;
    while(n--) {
        int x; cin >> x;

        while(!q.empty() && x - q.front() >= k) q.pop();

        ans += q.size();
        q.push(x);
    }

    cout << ans << lf;
}
