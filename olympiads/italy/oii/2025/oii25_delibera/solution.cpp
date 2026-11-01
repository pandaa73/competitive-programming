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

constexpr double PHI = 1.6180339887;

bool chiedi(vector<int> S, int x);

int delibera(int N) {
    auto search = [&](int l, int r, vector<int> vals, auto &&search) -> int {
        int n = vals.size();

        if(n == 1) return vals[0];

        int m = l + (r - l) / PHI;

        infof("============= search(%d, %d, vals) =============", l, r);
        infor("vals:", 0);
        for(auto x: vals)
            infor(" %d", x);
        infos("");

        infof("[%d, %d): m = %d", l, r, m);

        vector<int> qry_l(m - l); iota(all(qry_l), l);

        vector<int> vals_l, vals_r;
        for(int i = 0; i < n; ++i)
            (chiedi(qry_l, vals[i]) ? vals_l : vals_r).push_back(vals[i]);

        if(vals_l.size() == m - l - 1)
            return search(l, m, vals_l, search);

        vector<int> qry_r(r - m); iota(all(qry_r), m);
        for(auto x: vals_l)
            if(chiedi(qry_r, x)) return x;

        return search(m, r, vals_r, search);
    };

    vector<int> vals(N); iota(all(vals), 0);

    return search(0, N + 1, vals, search);
}

#ifndef EVAL

namespace {
int N;
vector<int> A;
int queries = 0;
}  // namespace

bool chiedi(vector<int> S, int x) {
    queries++;

    infos("-------");
    infof("chiedi(S, %d)", x);
    infor("... S =", 0);
    for(auto x: S)
        infor(" %d", x);
    infos("");

    if (x < 0 || x >= N) {
        cout << "Invalid query" << endl;
        exit(0);
    }
    sort(S.begin(), S.end());
    if (!S.empty() && (S.front() < 0 || S.back() >= N + 1)) {
        cout << "Invalid query" << endl;
        exit(0);
    }
    if (unique(S.begin(), S.end()) != S.end()) {
        cout << "Invalid query" << endl;
        exit(0);
    }

    bool b = false;

    for (int idx : S)
        if (A[idx] == x) b = true;

    infof("... ret = %d", (int)b);

    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 0; tc < T; ++tc) {
        cin >> N;

        A.assign(N + 1, 0);
        for (int i = 0; i < A.size(); ++i) {
            if (!(cin >> A[i])) {
                cout << "Invalid instance" << endl;
                return 0;
            }
        }

        if (N <= 0) {
            cout << "Invalid instance" << endl;
            return 0;
        }
        vector<int> freq(N, 0);
        for (int v : A) {
            if (v < 0 || v >= N) {
                cout << "Invalid instance" << endl;
                return 0;
            }
            freq[v]++;
        }

        int expected_value = -1;
        int twice = 0;
        for (int v = 0; v < N; ++v) {
            if (freq[v] == 2) {
                twice++;
                expected_value = v;
            } else if (freq[v] != 1) {
                cout << "Invalid instance" << endl;
                return 0;
            }
        }
        if (twice != 1) {
            cout << "Invalid instance" << endl;
            return 0;
        }

        queries = 0;

        int got = delibera(N);

        if (got != expected_value)
            cout << "Wrong answer. Got " << got << ", expected " << expected_value << endl;
        else
            cout << "Correct. " << queries << " queries." << endl;
    }

    return 0;
}

#endif
