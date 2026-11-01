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

template<typename T>
using vec = vector<T>;

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

mt19937 timmy_loves_gambling(73);

using Grid = vec<vec<int>>;

const vec<pair<int, Grid>> BASE = {
    // ----- 0x0 ----- //
    {0, {
    }},

    // ----- 1x1 ----- //
    {0, {
        {0},
    }},

    // ----- 2x2 ----- //
    {0, {
        {0, 0},
        {0, 0},
    }},

    // ----- 3x3 ----- //
    {1, {
        {1, 1, 1},
        {0, 1, 0},
        {0, 0, 0},
    }},

    // ----- 4x4 ----- //
    {4, {
        {2, 2, 2, 3},
        {1, 2, 3, 3},
        {1, 1, 4, 3},
        {1, 4, 4, 4},
    }},

    // ----- 5x5 ----- //
    {6, {
        {1, 2, 2, 2, 3},
        {1, 1, 2, 3, 3},
        {1, 4, 0, 3, 5},
        {4, 4, 6, 5, 5},
        {4, 6, 6, 6, 5},
    }},

    // ----- 6x6 ----- //
    {8, {
        {6, 7, 7, 8, 8, 8},
        {6, 6, 7, 7, 8, 5},
        {6, 3, 4, 4, 5, 5},
        {3, 3, 2, 4, 4, 5},
        {3, 1, 2, 2, 0, 0},
        {1, 1, 1, 2, 0, 0},
    }},

    // ----- 7x7 ----- //
    {12, {
        { 1,  2,  2,  2,  3,  3,  4},
        { 1,  1,  2,  3,  3,  4,  4},
        { 1,  5,  5,  6,  6,  6,  4},
        { 5,  5,  7,  7,  6,  8,  8},
        { 9,  7,  7,  0,  8,  8, 10},
        { 9,  9, 11, 12, 12, 10, 10},
        { 9, 11, 11, 11, 12, 12, 10},
    }},

    // ----- N/A ----- //
    {0, {
    }},

    // ----- N/A ----- //
    {0, {
    }},

    // ----- 10x10 ----- //
    {25, {
        { 1,  1,  2,  2,  2,  3,  4,  4,  4,  5},
        { 6,  1,  1,  2,  3,  3,  3,  4,  5,  5},
        { 6,  6,  7,  7,  8,  9,  9,  9,  5, 10},
        { 6,  7,  7, 11,  8,  8,  9, 12, 10, 10},
        {13, 13, 11, 11, 11,  8, 12, 12, 12, 10},
        {14, 13, 13, 15, 15, 16, 17, 18, 18, 18},
        {14, 14, 15, 15, 16, 16, 17, 17, 18, 19},
        {14, 20, 21, 21, 16, 22, 22, 17, 19, 19},
        {20, 20, 23, 21, 21, 24, 22, 22, 25, 19},
        {20, 23, 23, 23, 24, 24, 24, 25, 25, 25},
    }},
};

const vec<pair<int, Grid>> BASE2 = {
    // ----- 4x10 ----- //
    {10, {
        { 1,  1,  1,  2,  2,  3,  3,  4,  4,  5},
        { 6,  1,  2,  2,  3,  3,  4,  4,  5,  5},
        { 6,  6,  7,  7,  8,  8,  9,  9, 10,  5},
        { 6,  7,  7,  8,  8,  9,  9, 10, 10, 10},
    }},

    // ----- 10x4 ----- //
    {10, {
        { 5,  5,  5, 10},
        { 4,  5, 10, 10},
        { 4,  4,  9, 10},
        { 3,  4,  9,  9},
        { 3,  3,  8,  9},
        { 2,  3,  8,  8},
        { 2,  2,  7,  8},
        { 1,  2,  7,  7},
        { 1,  1,  6,  7},
        { 1,  6,  6,  6},
    }},
};

void paste(int x, int y, int &M, vec<vec<int>> &G,
        const pair<int, vec<vec<int>>> &T) {
    const int R = T.se.size();
    const int C = T.se[0].size();

    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            G[x + i][y + j] = T.se[i][j] == 0 ? 0 : T.se[i][j] + M;
        }
    }

    M += T.fi;
}

void fill_border(const int N, int &M, vec<vec<int>> &G,
        const int off_x = 0, const int off_y = 0) {
    if(N <= 7) return;

    int sz = (N - 5) / 2;

    G[off_x + 0][off_y + 0] = G[off_x + 1][off_y + 0]
        = G[off_x + 1][off_y + 1] = G[off_x + 2][off_y + 0]
        = M + 1;

    G[off_x + 0][off_y + 1] = G[off_x + 0][off_y + 2]
        = G[off_x + 0][off_y + 3] = G[off_x + 1][off_y + 2]
        = M + 2;

    G[off_x + N - 3][off_y + N - 1] = G[off_x + N - 2][off_y + N - 2]
        = G[off_x + N - 2][off_y + N - 1] = G[off_x + N - 1][off_y + N - 1]
        = M + 3;

    G[off_x + N - 2][off_y + N - 3] = G[off_x + N - 1][off_y + N - 4]
        = G[off_x + N - 1][off_y + N - 3] = G[off_x + N - 1][off_y + N - 2]
        = M + 4;

    M += 4;

    for(int x = 0; x < N - 3; x += 2) {
        G[off_x + x + 2][off_y + 1] = G[off_x + x + 3][off_y + 0]
            = G[off_x + x + 3][off_y + 1] = G[off_x + x + 4][off_y + 0]
            = M + 1;

        G[off_x + x + 0][off_y + N - 1] = G[off_x + x + 1][off_y + N - 2]
            = G[off_x + x + 1][off_y + N - 1] = G[off_x + x + 2][off_y + N - 2]
            = M + 2;

        M += 2;
    }

    for(int y = 1; y < N - 4; y += 2) {
        G[off_x + 0][off_y + y + 3] = G[off_x + 0][off_y + y + 4]
            = G[off_x + 1][off_y + y + 2] = G[off_x + 1][off_y + y + 3]
            = M + 1;

        G[off_x + N - 2][off_y + y + 1] = G[off_x + N - 2][off_y + y + 2]
            = G[off_x + N - 1][off_y + y + 0] = G[off_x + N - 1][off_y + y + 1]
            = M + 2;

        M += 2;
    }

    fill_border(N - 4, M, G, off_x + 2, off_y + 2);
}

void fill_mod_0(const int N, int &M, vec<vec<int>> &G) {
    for(int x = 0; x < N; x += 4) {
        for(int y = 0; y < N; y += 4) {
            paste(x, y, M, G, BASE[4]);
        }
    }
}

void fill_mod_1(const int N, int &M, vec<vec<int>> &G) {
    fill_border(N, M, G);
    int sz = (N - 5) / 2;

    paste(sz, sz, M, G, BASE[5]);
}

void fill_mod_2(const int N, int &M, vec<vec<int>> &G) {
    fill_mod_0(N - 10, M, G);

    for(int x = 0; x < N - 10; x += 4) {
        paste(x, N - 10, M, G, BASE2[0]);
    }

    for(int y = 0; y < N - 10; y += 4) {
        paste(N - 10, y, M, G, BASE2[1]);
    }

    paste(N - 10, N - 10, M, G, BASE[10]);
}

void fill_mod_3(const int N, int &M, vec<vec<int>> &G) {
    fill_border(N, M, G);
    int sz = (N - 7) / 2;

    paste(sz, sz, M, G, BASE[7]);
}

void (*filler[])(const int, int &, vec<vec<int>> &) = {
    fill_mod_0, fill_mod_1, fill_mod_2, fill_mod_3,
};

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N; cin >> N;

    int M = 0;
    vec<vec<int>> G(N, vec<int>(N));

    if(N <= 7 || N == 10) {
        M = BASE[N].fi;
        G = BASE[N].se;
    } else filler[N % 4](N, M, G);

    cout << M << lf;
    for(int x = 0; x < N; ++x) {
        for(int y = 0; y < N; ++y) {
            cout << G[x][y] << " ";
        }

        cout << lf;
    }
}
