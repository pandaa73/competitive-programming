#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e4+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    unordered_map<int, int> calc;
    calc[1] = 1;

    auto coll = [&](int x, auto &&coll) {
        if(calc[x]) return;

        int y;
        if(x&1)
            y = 3 * x + 1;
        else y = x / 2;

        coll(y, coll);

        calc[x] = calc[y] + 1; 
    };

    constexpr int MAX_DEPTH = 128;

    unordered_map<int, int> palc;
    palc[1] = 1;

    auto poll = [&](int x, int d, auto &&poll) {
        if(palc[x]) return;
        if(d == MAX_DEPTH) {
            palc[x] = -1;
            return;
        }

        int y;
        if(x&1)
            y = 5 * x + 1;
        else y = x / 2;

        poll(y, d + 1, poll);

        palc[x] = (palc[y] + 1 <= 0 ? -1 : palc[y] + 1);
    };

    int l, r; cin >> l >> r;

    int ans = 0;
    for(; l <= r; ++l) {
        coll(l, coll), poll(l, 0, poll);

        if(palc[l] < calc[l] && palc[l] > 0)ans++;
    }

    cout << ans << lf;
}