#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int MOD = 1e9+7;
constexpr int MAXN = 2e6+7;

using ll = long long;

int sbugiarda(int N, vector<int> H) {
    vector<int> pge(N, -1), nge(N, -1);
    vector<int> pce(N, -1);

    stack<array<int, 2>> s1, s2;
    for(int i = 0; i < N; ++i) {
        int j = N - i - 1;

        auto x = H[i], y = H[j];

        while(!s1.empty() && s1.top()[0] < x)
            nge[s1.top()[1]] = i, s1.pop();
        s1.push({x, i});

        while(!s2.empty() && s2.top()[0] < y)
            pge[s2.top()[1]] = j, s2.pop();
        if(!s2.empty() && s2.top()[0] == y) pce[s2.top()[1]] = j;
        s2.push({y, j});
    }

    vector<int> sx(N, 0);
    for(int i = 0; i < N; ++i) {
        if(nge[i] < 0) continue;

        sx[nge[i]] = max(sx[nge[i]], sx[i] + 1);
    }

    vector<int> dx(N, 0);
    for(int i = N - 1; i >= 0; i--) {
        if(pge[i] < 0) continue;

        dx[pge[i]] = max(dx[pge[i]], dx[i] + 1);
    }

    int ans = 0;
    for(int i = 0; i < N; ++i)
        ans = max(ans, sx[i] + 1 + dx[i]);

    for(int i = 0; i < N; ++i) {
        if(pce[i] == -1) {
            sx[i]++;
            continue;
        }

        ans = max(ans, sx[pce[i]] + 1 + dx[i]);
        sx[i] = max(1 + sx[i], sx[pce[i]]);
    }

    return ans;
}
