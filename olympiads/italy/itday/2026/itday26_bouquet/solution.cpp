#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int componi(int N, int J, vector<int> F) {
    sort(all(F));

    int ans = 0;
    for(int i = 1; i < N; ++i) {
        ll d = F[i] - F[i - 1];

        if(d * i > J) {
            return F[i - 1] + J / i;

            break;
        }

        J -= d * i;
    }

    return F[N - 1] + J / N;
}

#ifdef LOCAL
int main() {

    int N, J;
    cin >> N >> J;

    vector<int> F(N);
    for (int &f: F) cin >> f;

    cout << componi(N, J, F) << endl;
}
#endif
