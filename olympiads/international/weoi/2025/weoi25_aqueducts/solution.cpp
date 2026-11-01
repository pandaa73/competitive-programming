#include <bits/stdc++.h>
#include <chrono>
#include <random>
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

vector<int> count(int N, vector<int> S, vector<int> P) {
    vector<int> ord(N); iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return S[i] > S[j];
    });

    vector<int> ans(N);

    int mn_1 = -1, mn_2 = -1;

    int cnt = 0;
    for(auto i: ord) {
        infof("%d: mn = %d, %d | cnt = %d", i, mn_1, mn_2, cnt);

        if(mn_1 < 0) {
            mn_1 = i;

            ans[i]--;
            cnt++;

            continue;
        }

        if(mn_2 < 0) {
            if(P[mn_1] < P[i]) {
                mn_2 = i;
                ans[mn_1]++;
                continue;
            }

            mn_2 = mn_1;
            mn_1 = i;

            ans[i]--;
            cnt++;

            continue;
        }

        if(P[mn_1] < P[i]) {
            if(P[mn_2] < P[i]) continue;

            mn_2 = i;

            ans[mn_1]++;

            continue;
        }

        mn_2 = mn_1;
        mn_1 = i;

        ans[i]--;
        cnt++;
    }

    for(auto &x: ans)
        x += cnt;

    return ans;
}
