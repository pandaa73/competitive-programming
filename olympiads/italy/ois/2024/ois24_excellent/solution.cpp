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

    if(n == 1) {
        cout << "-1" << endl;
        return 0;
    }

    if(n&1) {
        cout << "111";
        for(int i = 0; i < (n-3)/2; ++i)
            cout << "15";
        
        cout << endl; return 0;
    }

    for(int i = 0; i < n/2; ++i)
        cout << "15";
    
    cout << endl; return 0;
}