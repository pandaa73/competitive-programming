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

    int l = 0;
    for(int i = 0; i < n; ++i) {
        string s; cin >> s;
        if(l + s.length() > k) {
            l = s.length() + 1;
            cout << lf << s << " ";

            continue;
        }

        l += s.length() + 1;
        cout << s << " ";
    }

    cout << lf;
}