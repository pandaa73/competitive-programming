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

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;

    vector<int> fib(2);
    fib[0] = fib[1] = 1;

    int k = 1;
    while(fib.back() <= n)
        fib.push_back(fib[k - 1] + fib[k++]);

    vector<bool> v;
    for(k--; k >= 0; k--) {
        if(fib[k] > n) 
            v.push_back(0);
        else v.push_back(1), n -= fib[k];
    }

    for(int i = v.size() - 1; i >= 0; i--)
        cout << v[i];
    cout << lf;
}