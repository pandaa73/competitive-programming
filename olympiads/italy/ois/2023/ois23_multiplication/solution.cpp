#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

void solve(void) {
    int n; cin >> n;

    bitset<10> digits;

    int it = 0;
    for(int i = n; digits.count() < 10; i += n, ++it) {
        int k = i;
        
        while(k > 0) {
            digits.set(k % 10);

            k /= 10;
        }
    }

    cout << it << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--) solve(); 
}