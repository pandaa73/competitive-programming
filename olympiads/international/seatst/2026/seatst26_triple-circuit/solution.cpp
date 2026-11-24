#include <bits/stdc++.h>
using namespace std;

#include <cassert>

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

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int MAXN = 128;

constexpr int NOT = 0;
constexpr int  OR = 1;
constexpr int AND = 2;

const array<string, 3> PORTS = {
    "NOT", "OR", "AND"
};

struct Port {
    Port(void) {}
    Port(int t, int a, int b = -1): t(t), a(a), b(b) {}

    int t;
    int a, b;
};

vec<Port> T;

template<typename... Args>
int add_port(Args... args) {
    T.emplace_back(args...);
    return MAXN + T.size() - 1;
}

int build_tree(vec<int> po) {
    int N = po.size();

    vec<int> pa(N);
    vec<int> no(N), na(N);

    N >>= 1;
    for(int n = 0; n < N; ++n) {
        no[n] = add_port(OR, po[n << 1], po[n << 1 | 1]);
        na[n] = add_port(AND, po[n << 1], po[n << 1 | 1]);
    }

    swap(po, no);
    swap(pa, na);

    while(N > 1) {
        N >>= 1;

        for(int n = 0; n < N; ++n) {
            if(N > 1) no[n] = add_port(OR, po[n << 1], po[n << 1 | 1]);
            int a = add_port(AND, po[n << 1], po[n << 1 | 1]);
            int b = add_port(OR, pa[n << 1], pa[n << 1 | 1]);
            na[n] = add_port(OR, a, b);
        }

        swap(po, no);
        swap(pa, na);
    }

    return pa[0];
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N = MAXN;


    N >>= 1;
    vec<int> vo(N);

    for(int n = 0; n < N; ++n) {
        vo[n] = add_port(OR, n << 1, n << 1 | 1);
    }

    vec<int> ro(8, -1), co(8, -1);
    for(int n = 0; n < N; ++n) {
        int r = n / 8;
        int c = n % 8;

        ro[r] = ro[r] < 0 ? vo[n] : add_port(OR, vo[n], ro[r]);
        co[c] = co[c] < 0 ? vo[n] : add_port(OR, vo[n], co[c]);
    }

    int r = build_tree(ro);
    int c = build_tree(co);

    add_port(OR, r, c);

    cout << T.size() << lf;
    for(auto [t, a, b]: T) {
        cout << PORTS[t] _ a;
        if(t > 0) cout _ b;
        cout << lf;
    }
}
