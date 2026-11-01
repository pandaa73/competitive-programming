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

    int n, q; cin >> n >> q;
 
    vector<int> v(n, -1), w(n);

    set<int> fr;
    for(int i = 0; i < n; ++i)
        fr.insert(i);

    int ans = 0;

    auto board = [&](int k) {
        int i = *fr.begin();

        if(i > k) i = k;
        else fr.erase(i);

        w[k] = i;
        while(v[i] > -1) {
            int l = v[i];

            v[i] = k;
            w[l] = l;

            i = k = l;

            ans++;
        }

        v[i] = k;
        if(fr.find(i) != fr.end())
            fr.erase(i);
    };

    auto leave = [&](int k) {
        fr.insert(w[k]);

        w[k] = v[w[k]] = -1;
    };

    for(int i = 0; i < q; ++i) {
        char c; cin >> c;
        int k; cin >> k;

        switch(c) {
            case 'b':
                board(k);
                break;
            case 'l':
                leave(k);
                break;
            default:
                assert(0);
        }
    }

    cout << ans << lf;
}