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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

bool attack(int);

int N, K;
vec<vec<int>> dp;

void init(int N, int K) {
    ::N = N;
    ::K = K;

    dp = vec<vec<int>>(K + 1, vec<int>(1));

    for(int q = 1; dp[K][q - 1] < N; ++q) {
        dp[0].emplace_back(0);
        for(int k = 1; k <= K; ++k) {
            dp[k].emplace_back(dp[k - 1][q - 1] + 1 + dp[k][q - 1]);
        }
    }
}

int new_pokemon(void) {
    infof("======= new_pokemon =======");
    int k = K, q = dp[0].size() - 1;

    int p = 0;
    while(k > 0 && q > 0 && p < N) {
        infof("===== ({}, {}) =====", k, q);
        int c = min(N - 1, p + dp[k - 1][q - 1]);
        bool b = attack(c);

        if(b) {
            p = c + 1;
        } else k -= 1;

        q -= 1;
    }

    return p;
}

#ifdef LOCAL

namespace {

FILE *fin, *fout;
static int N, K, Q, S, life_left, count_attack;
static int *ans, *calls;

// void init(int, int);
// int new_pokemon();

bool do_attack(int P) {
    infor("... attack({})", P);

    if (P < 0 || P >= N || life_left == 0) {
        fprintf(fout, "Illecit call to function attack\n");
        exit(0);
    }

    ++count_attack;
    if(count_attack > N) {
        fprintf(fout, "Function attack called too many times\n");
        exit(0);
    }
    if (P < S) {
        infof(" -> 1");
        return true;
    }

    infof(" -> 0");
    --life_left;
    return false;
}

int grade() {
    // fin = fopen("input.txt", "r");
    // fout = fopen("output.txt", "w");
    fin = stdin;
    fout = stdout;

    assert(fscanf(fin, "%d%d%d", &N, &K, &Q) == 3);
    ans = (int *)malloc(Q * sizeof(int));
    calls = (int *)malloc(Q * sizeof(int));

    init(N, K);

    for (int k = 0; k < Q; k++) {
        assert(fscanf(fin, "%d", &S) == 1);
        life_left = K;
        count_attack = 0;
        ans[k] = new_pokemon();
        calls[k] = count_attack;
    }

    for (int k = 0; k < Q; k++)
        fprintf(fout, "%d %d\n", ans[k], calls[k]);

    fclose(fin);
    fclose(fout);

    return EXIT_SUCCESS;
}

}

bool attack(int P) { return do_attack(P); }

int main(void) {
    return grade();
}
#endif
