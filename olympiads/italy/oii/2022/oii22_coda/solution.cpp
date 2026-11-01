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

vector<int> cucina(int N, int K, int X, vector<int> H) {
    vector<int> cnt(X);
    for(auto x: H) cnt[x]++;
    
    int empty = 0, last = 0;
    
    vector<int> ans(X);
    for(int i = X - 1; i >= 0; i--) {
        empty = min(K, empty + 1);
        
        int x = min(cnt[i], empty);
        
        last += x;
        empty -= x;
        
        ans[i] = last;
    }
    
    return ans;
}