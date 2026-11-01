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

#endif

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int INF = 1e9;

struct Taxi {
    int t0, x0, y0, x1, y1;
    Taxi() {}
};

struct Node {
    Node(void): p(0), ch({0, 0}) {}
    Node(int x, int d): Node() {
        this->x = x;
        this->d = d;
    }

    int p;
    array<int, 2> ch;

    int x, d;
};

vec<Node> T(1);

template<typename... Args>
int make_node(Args... args) {
    T.emplace_back(args...);
    return T.size() - 1;
}

void set_child(int p, int n, bool s) {
    T[p].ch[s] = n;
    if(n) T[n].p = p;
}

int dir(int n) {
    int p = T[n].p;
    if(!p) return -1;
    return T[p].ch[0] == n ? 0 : T[p].ch[1] == n ? 1 : -1;
}

void rotate(int n) {
    int p = T[n].p, g = T[p].p;
    int s = dir(n), t = dir(p);

    set_child(p, T[n].ch[s ^ 1], s ^ 0);
    set_child(n, p, s ^ 1);
    if(~t) set_child(g, n, t);

    T[n].p = g;
}

void splay(int n) {
    while(~dir(n)) {
        int p = T[n].p, g = T[p].p;
        int s = dir(n), t = dir(p);

        if(~t) rotate(s == t ? p : n);
        rotate(n);
    }
}

void access(int m) {
    int n = 0, p = m;
    for(; p; n = p, p = T[n].p) {
        splay(p);
        T[p].ch[1] = n;
    }

    splay(m);
}

void link(int n, int p) {
    assert(n);
    assert(p);

    access(n), access(p);
    T[n].p = p;
}

void cut(int n) {
    assert(n);

    access(n);
    int m = T[n].ch[0];
    T[m].p = T[n].ch[0] = 0;
}

int find_first(int n, int x) {
    access(n);

    int ans = 0, s = n;
    while(n) {
        s = n;

        if(T[n].x > x) {
            ans = n;
            n = T[n].ch[1];
        } else {
            n = T[n].ch[0];
        }
    }

    splay(n);
    splay(s);
    return ans;
}

vector<int> incrocia(int N, int M, vector<Taxi> V, vector<Taxi> H) {
    vec<vec<pii>> diag(3 * N + 1);
    priority_queue<pii, vec<pii>, greater<pii>> q;
    for(int i = 1; i <= M; ++i) {
        auto [t, x0, y0, x1, y1] = V[i - 1];

        int d = x0 + y0 + N - t;

        diag[d].emplace_back(x0, make_node(x0, d));

        q.emplace(y0, i);
        q.emplace(y1, -i);
    }

    for(int d = 0; d <= 3 * N; ++d) {
        diag[d].emplace_back(INF, make_node(INF, d));
        sort(all(diag[d]));
        for(int i = 0; i < (int)diag[d].size() - 1; ++i) {
            link(diag[d][i].se, diag[d][i + 1].se);
        }
    }

    vec<int> ans(M), ord(M);
    iota(all(ord), 1);
    sort(all(ord), [&](int i, int j) -> bool {
        return H[i - 1].y0 < H[j - 1].y0;
    });

    for(auto i: ord) {
        auto [t, x0, y0, x1, y1] = H[i - 1];
        int d = x0 + y0 + N - t;

        while(!q.empty() && q.top().fi < y0) {
            auto [_t, n] = q.top();
            q.pop();

            bool add = n > 0;
            n = abs(n);

            auto it = upper_bound(all(diag[T[n].d - add]), (pii){T[n].x, n});

            cut(n);
            link(n, it->se);
        }

        auto it = upper_bound(all(diag[d]), (pii){x0, INF});

        int n = find_first(it->se, x1);
        if(n == 0) {
            ans[i - 1] = x1 - x0;
        } else {
            ans[i - 1] = (x1 - x0) + (d - T[n].d);
        }
    }

    return ans;
}

// GRADER DI ESEMPIO, NON MODIFICARE

#ifndef EVAL

int main() {
    int N;
    int M;
    cin >> N;
    cin >> M;

    std::vector<Taxi> V(M), H(M);

    for (Taxi &taxi: V) {
        cin >> taxi.t0;
        cin >> taxi.x0;
        cin >> taxi.y0;
        cin >> taxi.x1;
        cin >> taxi.y1;
    }

    for (Taxi &taxi: H) {
        cin >> taxi.t0;
        cin >> taxi.x0;
        cin >> taxi.y0;
        cin >> taxi.x1;
        cin >> taxi.y1;
    }

    vector<int> ans = incrocia(N, M, V, H);

    for (int x: ans) {
        cout << x << '\n';
    }
}
#endif
