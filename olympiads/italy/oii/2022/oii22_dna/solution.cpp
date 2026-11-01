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

bool test(string T);

string analizza(int N) {
    int l = 1, r = N + 1;
    while(l < r) {
        int m = (l + r) / 2;

        if(test(string(m, '1')))
            l = m + 1;
        else r = m;
    }

    string S(--l, '1');
    if(S.empty()) return(string(N, '0'));

    int guess = l;
    while(S.size() < N) {
        bool b = !test(S + "0");

        S.push_back(b + '0');

        if(b)
            guess++;
        else guess = 0;

        if(guess > l) break;
    }

    S.resize(S.size() - guess);

    if(S.size() == N) return S;

    do {
        S += "1";
    } while(guess-- && test(S));

    S.pop_back();
    if(S.size() == N) return S;

    S = "0" + S;

    while(S.size() < N) {
        bool b = !test("0" + S);

        S = string(1, b + '0') + S;
    }

    return S;
}
