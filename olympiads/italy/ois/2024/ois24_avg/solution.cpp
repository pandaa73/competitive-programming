#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, k; cin >> n >> k;

    ll avg = n*k, sum = 0;
    vector<int> v(n);
    for(auto &x: v) 
        cin >> x, sum += x;

    if(sum == avg) {
        cout << '0' << endl;
        return 0;
    }

    if(sum < avg) {
        cout << '1' << endl;
        return 0;
    }

    sort(rall(v));
    int cnt = 0;
    for(auto x: v) {
        sum -= (x-1), ++cnt;
        if(sum <= avg) break;
    }

    cout << cnt << endl;
    return 0;
}