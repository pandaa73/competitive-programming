#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int fotosintesi(int N, string S) {
    map<array<int, 2>, int> mp;

    int mx = 0;
    array<int, 3> cnt;
    for(int i = 0; i < N; ++i) {
        cnt[S[i] - 'A']++;

        array<int, 2> k = {cnt[0] - cnt[1], cnt[0] - cnt[2]};

        if(mp.find(k) == mp.end())
            mp[k] = i;
        else mx = max(mx, i - mp[k]);
    }

    return mx;
}
