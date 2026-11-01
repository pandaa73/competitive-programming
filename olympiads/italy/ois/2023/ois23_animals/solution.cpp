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

    int n; cin >> n;

    vector<int> v(n);
    for(auto &x: v) cin >> x;

    vector<int> a;
    a.push_back(v[0]);

    for(int i = 1; i < n; ++i) {
        vector<int> nw;
        for(int j = 0; j < a.size(); ++j) {
            if(a[j] >= v[i]) nw.push_back(a[j]);
        }
        
        nw.push_back(v[i]);
        a = nw;
    }

    cout << a.size() << endl;
    return 0;
}