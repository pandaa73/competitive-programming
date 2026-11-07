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

struct Node {
    Node(void): ch({}), x(0) {}
    Node(int x): ch({}), x(x) {}

    int x;
    array<int, 2> ch;
};

vec<Node> T(1);

template<typename... Args>
int make_node(Args... args) {
    T.emplace_back(args...);
    return T.size() - 1;
}

bool side(int n, int p) {
    return T[n].ch[1] == p;
}

int next(int n, int p) {
    return T[n].ch[!side(n, p)];
}

pii rev(pii L) {
    return {L.se, L.fi};
}

pii merge(pii L, pii R) {
    T[L.se].ch[side(L.se, 0)] = R.fi;
    T[R.fi].ch[side(R.fi, 0)] = L.se;
    return {L.fi, R.se};
}

vector<int> fold(int N, vector<int> A, vector<int> X) {
    const int M = A.size();

    vec<int> ans;
    ans.reserve(N);

    vec<pii> V(N);
    for(int n = 0; n < N; ++n) {
        V[n].fi = V[n].se = make_node(n);
    }

    int xor_t = 0;
    bool flip = false;
    vec<bool> flipped(N);

    auto get = [&](int n) -> pii {
        if(flipped[n] != flip) {
            flipped[n] = flip;
            V[n] = rev(V[n]);
        }

        return V[n];
    };

    int l = 0, r = N;
    for(int ii = 0; ii < M; ++ii) {
        int t = A[ii] ^ xor_t, x = X[ii];

        if(x > (r - l) - x) {
            t ^= 3;
            xor_t ^= 2;

            x = (r - l) - x;
            flip ^= 1;
        }

        if(t == 0) {
            l += x;
            for(int i = 0; i < x; ++i) {
                V[l + i] = merge(get(l + i), rev(get(l - i - 1)));
            }
        } else if(t == 1) {
            l += x;
            for(int i = 0; i < x; ++i) {
                V[l + i] = merge(rev(get(l - i - 1)), get(l + i));
            }
        } else if(t == 2) {
            r -= x;
            for(int i = 0; i < x; ++i) {
                V[r - i - 1] = merge(get(r - i - 1), rev(get(r + i)));
            }
        } else if(t == 3) {
            r -= x;
            for(int i = 0; i < x; ++i) {
                V[r - i - 1] = merge(rev(get(r + i)), get(r - i - 1));
            }
        }
    }

    for(int n = get(l).se, p = 0; n > 0;) {
        ans.emplace_back(T[n].x);
        int t = next(n, p);
        p = n, n = t;
    }

    return ans;
}

#ifdef LOCAL

vector<int> fold(int N, vector<int> T, vector<int> X);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<int> T(M), X(M);
  for (int i = 0; i < M; i++) {
    cin >> T[i] >> X[i];
  }

  vector<int> res = fold(N, T, X);
  for (size_t i = 0; i < res.size(); i++) {
    cout << res[i] << " \n"[i + 1 == res.size()];
  }

  return 0;
}

#endif /* LOCAL */
