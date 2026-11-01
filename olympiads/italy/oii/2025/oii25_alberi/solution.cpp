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

long long carica(int N, int K, vector<int> A) {
    ll sum = accumulate(all(A), 0LL);

    ll mn = sum;

    sum += K;
    for(int i = N - 2; i >= 0; i--) {
        sum += K;
        sum -= A[i];

        mn = min(mn, sum);
    }

    return mn;
}

#ifndef EVAL

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (int &a: A) cin >> a;

    cout << carica(N, K, A) << endl;

    return 0;
}

#endif
