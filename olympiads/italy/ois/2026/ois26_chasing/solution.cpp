#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
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
using fl = double;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    auto print = [&](fl T) -> void {
        cout << (T < 0 ? -1 : (ll)ceil(T)) << lf;

        exit(0);
    };

    fl Dx, Dy, Ds; cin >> Dx >> Dy >> Ds;
    fl Bx, By, Bs; cin >> Bx >> By >> Bs;

    char dir; cin >> dir;

    if(dir == 'U' || dir == 'D') {
        swap(Dx, Dy);
        swap(Bx, By);

        if(dir == 'U') {
            dir = 'R';
        } else dir = 'L';
    }

    fl d = dir == 'R' ? 1 : -1;

    fl T0 = abs(Dy - By) / Ds;

    Bx += T0 * Bs * d;

    if(Bx == Dx) print(T0);

    fl T1;
    if((Dx > Bx) == (d > 0)) {
        T1 = abs(Dx - Bx) / (Ds + Bs);
    } else {
        if(Bs >= Ds) print(-1);

        T1 = abs(Dx - Bx) / (Ds - Bs);
    }

    print(T0 + T1);
}
