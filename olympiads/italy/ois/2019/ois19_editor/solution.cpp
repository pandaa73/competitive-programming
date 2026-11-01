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

    int n; cin >> n;

    int ans = 0;

    bool it = 0, bo = 0;
    for(int i = 0; i < n; ++i) {
        char c; cin >> c;
        if(c < 'a') {
            ans += !bo;
            bo = 1;
        } else bo = 0;

        if(c == 'i' || c == 'I') {
            ans += !it;
            it = 1;
        } else it = 0;
    }

    cout << ans << lf;
}