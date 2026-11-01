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

    int prev; cin >> prev;
    if(prev == -1) prev = 0;

    int sum = prev;
    for(int i = 1; i < n; ++i) {
        int x; cin >> x;

        if(x == -1) x = prev;
        else prev = x;
        
        sum += x;
    }

    cout << sum << lf;
}