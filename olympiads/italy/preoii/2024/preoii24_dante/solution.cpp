#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int rimembra(int N, int K, vector<int> V) {
    if(K == 0) {
        int ans = 0;
        int curr = V[0];
        for(int i = 1; i < N; ++i) {
            if(V[i] == 1) curr++;
            else ans = max(ans, curr), curr = 0;
        }

        ans = max(ans, curr);

        return ans;
    }

    int l = 0, r = 0;
    for(int i = 0; i < K; ++i, ++r)
        while(V[r]) ++r;

    // cerr << l _ r << lf;

    int ans = 0;
    for(r--; r < N; ++l, ++r) {
        while(r < N - 1 && V[r + 1]) ++r;

        ans = max(ans, r - l);
        // cerr << l _ r << lf;

        while(l < r && V[l]) ++l;
    }

    return ans + 1;
}
