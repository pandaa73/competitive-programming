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
    int v[n]; for(auto &x: v) cin >> x;

    int prev1 = 0, prev2 = 0, skip = 0;
    for(int i = 0; i < n; ++i) {
        int curr;
        if(skip) {
            if(prev1 + v[i] <= prev2 + v[i - 1])
                curr = prev1 + v[i], skip = 0;
            else curr = prev2 + v[i - 1];
        } else curr = prev1, skip = 1;

        prev2 = prev1;
        prev1 = curr;
    }

    cout << prev1 << lf;
}