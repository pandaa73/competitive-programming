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

void Colora(int N, int Q, vector<int> &A, vector<int> &B, vector<int> &C,
        vector<int> &murale) {
    vec<int> p(N + 1);
    iota(all(p), 0);

    auto find = [&](int n, auto &&find) -> int {
        return p[n] == n ? n : p[n] = find(p[n], find);
    };

    for(int qi = Q - 1; qi >= 0; qi--) {
        int l = A[qi];
        for(l = find(l, find); l <= B[qi]; l = find(l, find)) {
            murale[l] = C[qi];
            p[l] = l + 1;
        }
    }
}

#ifdef LOCAL

int main(){
  int N, Q;
  cin >> N >> Q;
  vector <int> A(Q, 0), B(Q, 0), C(Q, 0), murale(N, 0);
  for(int i = 0; i < Q; i++){
    cin >> A[i] >> B[i] >> C[i];
  }
  Colora(N, Q, A, B, C, murale);
  for(int i = 0; i < N; i++){
    cout << murale[i] << " ";
  }
  cout << '\n';
  return 0;
}

#endif /* LOCAL */
