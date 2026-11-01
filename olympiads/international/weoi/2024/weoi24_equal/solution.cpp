#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

using ll = long long;

bool compare(int i, int j);
void add(vector<int> S, long long X);

void make_all_equal(int N, int Q_add, int Q_compare) {
    vector<int> q;

    int LOG  = 19;
    int LOGN = 31 - __builtin_clz(N);

    for(int it = 0; it < LOGN; ++it) {
        int pow = 1 << it;

        q.clear();

        for(int i = 0; i < N; i += pow << 1)
            for(int j = i; j < i + pow; ++j)
                q.push_back(j);

        for(int lg = LOG; lg >= 0; lg--)
            add(q, 1LL << lg);

        q.clear();

        for(int i = 0; i < N; i += pow << 1) {
            if(compare(i, i + pow)) continue;

            for(int j = i; j < i + pow; ++j)
                q.push_back(j);
        }

        if(!q.empty())
            add(q, 1);
    
        LOG++;
    }
}
