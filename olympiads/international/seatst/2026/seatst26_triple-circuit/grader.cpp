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

vec<Port> ports;

template<typename... Args>
int add_port(Args... args) {
    ports.emplace_back(args...);
    return MAXN + ports.size() - 1;
}

void solve(void) {
    int x, y, z; cin >> x >> y >> z;

    assert(x >= 0 && ((x < y && y < z) || (y < 0 && z < 0)));

    vec<int> mem(MAXN + ports.size(), 0);
    mem[x] = 1;
    if(y >= 0) mem[y] = mem[z] = 1;

    for(int p = 0; p < ports.size(); ++p) {
        auto [t, a, b] = ports[p];
        int x;
        switch(t) {
            case NOT:
                x = ~mem[a];
                break;
            case OR:
                x = mem[a] | mem[b];
                break;
            case AND:
                x = mem[a] & mem[b];
                break;
            default:
                assert(0 && "unreachable");
        }

        mem[p + MAXN] = x;
    }

    int X = mem.back(), Y = y < 0 ? 0 : 1;

    if(X == Y) {
        println("OK. Expected {}, found {}. [{}, {}, {}]", Y, X, x, y, z);
    } else {
        println("WA. Expected {}, found {}. [{}, {}, {}]", Y, X, x, y, z);
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        string t; cin >> t;
        if(t == "NOT") {
            int a; cin >> a;
            add_port(NOT, a);
        } else if(t == "OR") {
            int a, b; cin >> a >> b;
            add_port(OR, a, b);
        } else if(t == "AND") {
            int a, b; cin >> a >> b;
            add_port(AND, a, b);
        }
    }

    int T; cin >> T;
    while(T--) {
        solve();
    }
}
