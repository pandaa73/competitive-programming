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

    vector<int> v(n);
    for(auto &x: v) cin >> x;

    vector<array<int, 2>> sus(n, {-1});

    queue<array<int, 3>> q;
    for(int i = 0; i < n; ++i)
        q.push({i, (i + 1) % n, v[i]});

    array<int, 3> psh = {0, 0, 0};
    while(q.size() > 1) {
        auto [v, u, e] = q.front(); q.pop();

        e += psh[2];

        if(e < 10) {
            q.push({psh[0], u, e});
            psh = {u, u, 0};

            continue;
        }

        e -= 10;
        psh[2] = e;
        psh[1] = u;

        if(psh[0] == psh[1]) break;
    }

    cout << q.front()[1] + 1 << lf;
}