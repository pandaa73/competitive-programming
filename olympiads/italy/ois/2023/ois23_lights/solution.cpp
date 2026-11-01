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
    int v[n]; for(auto &x: v) cin >> x;

    int l = 0, r = 1;
    int count[k], colours = 1;
    memset(count, 0x00, sizeof(count));
    count[v[0]] = 1;

    int mn = INT_MAX;
    while(r < n) {
        if(!count[v[r]]++) colours++;

        while(l < r && count[v[l]] > 1)
            count[v[l]]--, l++;

        r++;
        if(colours == k) mn = min(mn, r - l);
    }

    cout << mn << lf;
}