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

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;

    priority_queue<int> pq;
    while(n--) {
        int x; cin >> x;
        pq.push(-x);
    }

    int ans = 0;
    while(pq.size() > 1) {
        int x = pq.top(); pq.pop();
        x += pq.top(); pq.pop();

        ans -= x;
        pq.push(x);
    }

    cout << ans << lf;
}
