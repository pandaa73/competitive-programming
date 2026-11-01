#include <bits/stdc++.h>
using namespace std;
// flag[10]

void Solve() {
    int n; cin >> n;

    long long mcm = 1;
    for(int i = 0; i < n; ++i) {
        long long x; cin >> x;
        mcm *= x/__gcd(x, mcm);
    }

    cout << mcm;
}

int main() {
    freopen("territoriali/input.txt", "r", stdin);
    freopen("territoriali/output.txt", "w", stdout);

    int t; cin >> t;
    for(int i = 0; i < t; ++i) cout << "Case #" << i+1 << ":", Solve(), cout << "\n";
}