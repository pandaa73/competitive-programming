#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

constexpr int MOD = 1e9+7;
constexpr int N = 2e5+7;
int dsu[N];

int find(int v) {
    return (dsu[v] < 0 ? v : dsu[v] = find(dsu[v]));
}

void unite(int a, int b) {
    a = find(a), b = find(b);

    if(a == b) return;
    if(a > b) swap(a, b);

    dsu[a] += dsu[b];
    dsu[b] = a;
}

int main() {
    fill(dsu, dsu+N, -1);

    int r, c, n;
    cin >> r >> c >> n;

    array<int, 2> p[n];
    for(auto& [x, y]: p) cin >> x >> y;

    map<int, int> mpx, mpy;
    map<int, int> mpdx, mpdy;
    for(int i = 0; i < n; ++i) {
        auto [x, y] = p[i];

        if(mpx.find(x) != mpx.end())
            unite(mpx[x], i);
        else mpx[x] = i;

        if(mpy.find(y) != mpy.end())
            unite(mpy[y], i);
        else mpy[y] = i;

        if(mpdx.find(x+y) != mpdx.end())
            unite(mpdx[x+y], i);
        else mpdx[x+y] = i;

        if(mpdy.find(x-y) != mpdy.end())
            unite(mpdy[x-y], i);
        else mpdy[x-y] = i;
    }

    int ans = 1;
    for(int i = 0; i < n; ++i)
        ans = (dsu[i] < 0 ? (ans << 1)%MOD : ans);

    cout << ans << endl;
}