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

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

vec<int> counting_sort(int N, const vec<int> &V) {
    vec<int> c(N), p(N);
    for(int i = 0; i < N; ++i) c[V[i]] += 1;
    for(int i = N - 2; i >= 0; i--) c[i] += c[i + 1];
    for(int i = N - 1; i >= 0; i--) p[--c[V[i]]] = i;

    return p;
}

variant<bool, vector<pair<int, int>>> find_numbering(int N, vector<int> A) {
    if(accumulate(all(A), 0) > 2 * N - 2) return false;

    auto p = counting_sort(N, A);

    vec<pii> ed;

    int ii = 0;
    vec<int> active, tmp;
    vec<vec<int>> s(N), t(N);
    for(int d = N - 1; d > 0; d--) {
        for(auto n: active) {
            swap(s[n], t[n]);
            s[n].clear();
        }

        for(; ii < N && A[p[ii]] >= d; ++ii) {
            int i = p[ii];
            active.emplace_back(i);
            t[i].emplace_back(i);
        }

        sort(all(active), [&](int i, int j) -> bool {
            return t[i].size() > t[j].size();
        });

        int u = -1, sz = 0;
        for(int jj = 0; jj < active.size(); ++jj) {
            int v = active[jj];

            if(sz == 0) {
                if(u >= 0) {
                    tmp.emplace_back(u);
                }

                u = v;
                sz = t[u].size();
                continue;
            }

            int n1 = t[u].back();
            t[u].pop_back();

            int n2 = t[v].back();
            t[v].pop_back();

            s[u].emplace_back(n1);
            s[u].emplace_back(n2);

            ed.emplace_back(n1, n2);

            for(auto n: t[v]) {
                t[u].emplace_back(n);
            }

            t[v].clear();
            t[v].shrink_to_fit();
            s[v].shrink_to_fit();

            sz = t[u].size();
        }

        if(sz > 0) return false;

        if(u >= 0) {
            tmp.emplace_back(u);
        }

        swap(active, tmp);
        tmp.clear();
    }

    return ed;
}

#ifdef LOCAL

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  auto result = find_numbering(N, A);
  if (holds_alternative<bool>(result)) {
    if (get<bool>(result)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  } else {
    cout << "YES\n";
    cout << (int)get<vector<pair<int, int>>>(result).size() << "\n";
    for (int i = 0; i < (int)get<vector<pair<int, int>>>(result).size(); ++i) {
      cout << get<vector<pair<int, int>>>(result)[i].first << " " << get<vector<pair<int, int>>>(result)[i].second << "\n";
    }
  }

  return 0;
}

#endif
