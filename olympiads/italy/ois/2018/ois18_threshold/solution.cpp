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

    int cnt[101];
    memset(cnt, 0x00, sizeof(cnt));

    while(n--) {
        int x; cin >> x;

        cnt[x]++;
    }

    int ans = 0;
    for(int i = 100; i >= 0; i--) {
        ans += cnt[i];
        cout << ans << " "; 
    }

    cout << lf;
}

