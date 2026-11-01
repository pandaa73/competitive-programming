#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

bool heights(int N, vector<int> Z, vector<int> &H) {
    H[0] = Z[0];
    for(int i = 1; i < N - 1; ++i) {
        H[i] = Z[i - 1] >= Z[i] ? Z[i] : Z[i - 1];
    }
    H[N - 1] = Z[N - 2];

    bool ok = 1;
    for(int i = 0; i < N - 1; ++i) {
        ok &= Z[i] == max(H[i], H[i + 1]);
    }

    return ok;
}

#ifdef LOCAL
int main() {
    // decommenta queste due righe per leggere da / scrivere su file
    // uncomment these two lines to read from / write to file
    // assert(freopen("input.txt", "r", stdin));
    // assert(freopen("output.txt", "w", stdout));

    int N;
    cin >> N;

    vector<int> Z(N - 1), H(N);
    for (int &z: Z) {
        cin >> z;
    }

    bool found = heights(N, Z, H);

    if (!found) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int h: H) {
            cout << h << " ";
        }
        cout << "\n";
    }
}
#endif
