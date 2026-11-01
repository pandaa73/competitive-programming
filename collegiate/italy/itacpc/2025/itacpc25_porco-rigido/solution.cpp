#include <bits/stdc++.h>
using namespace std;

#define ff endl
#define lf "\n"
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infor(str, ...) do { fprintf(stderr, str, ##__VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", ##__VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infor
#undef infof

#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 31;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

constexpr int MAXQ = 330;

#define int ll

ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    // assume a > b

    if(b == 0) {
        x = 1;
        y = 0;

        return a;
    }

    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

ll mod_inv(ll a, ll m) {
    // assume a >= 0

    a %= m;

    ll x, y;
    ll g = ext_gcd(m, a, x, y);

    y = (y + m) % m;

    return g == 1 ? y : -1;
}

signed main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

#ifdef DEBUG
    int N; cin >> N;
#else
    constexpr int N = 26;
#endif

    set<array<int, 2>> s;
    vector<array<int, 2>> ops;

    vector<int> V(N);

    ll g = 0;
    for(auto &x: V) {
        cin >> x;
        g = gcd(g, x);
    }

    for(int i = 0; i < N; ++i) {
        int x = V[i];

        if(x > 0) s.insert({-x/g, i});
    }

    while(s.size() > 1) {
        auto [x, qi] = *s.begin(); s.erase(s.begin());
        x = -x;

        int div2 = LOG + 1, yyy = -1, jjj = -1;
        for(auto [y, qj]: s) {
            int zr = __builtin_ctz(y);

            if(zr < div2)
                div2 = zr, yyy = y, jjj = qj;
        }

        for(int i = 0; i < div2; ++i)
            ops.push_back({jjj, jjj});

        s.erase({yyy, jjj});
        s.insert({yyy >> div2, jjj});

        int mn = INT_MAX, idx = -1, jj = 0, yy = 0;

        infof("======= x = (%d, %d) =======", x, qi);

        for(auto [y, qj]: s) {
            y = -y;

            infof("------- try y = (%d, %d) -------", y, qj);

            for(int i = 0; i < LOG; ++i) {
                int inv = mod_inv(1 << i, y);

                if(inv < 0) continue;

                int x0 = (x * inv) % y;

                int mv = i;

                int b = (x - x0 * (1 << i)) / y;

                if(b < 0) continue;

                int c = b % (1  << (i + 1));
                mv += __builtin_popcount(c) + b - c;

                if(mv < mn) mn = mv, idx = i, jj = qj, yy = y;

//                infof("----- try i = %d -----", i);
//                infof("... inv = %d", inv);
//                infof("... x0 = %d", x0);
//                infof("... mv = %d", mv);
//                infof("... b = %d", b);
//                infof("it takes %d moves.", mv);
            }
        }

        assert(mn > 0);

        int y = yy;
        int qj = jj;

        infof("chose idx, j: %d, %d [%d moves]", idx, qj, mn);

        int inv = mod_inv(1 << idx, y);
        assert(inv >= 0);

        int x0 = (x * inv) % y;

        int b = (x - x0 * (1 << idx)) / y;

        int c = b % (1 << (idx + 1));

        #ifdef DEBUG
            infof("... inv = %d", inv);
            infof("... x0 = %d", x0);
            infof("... mv = %d", mn);
            infof("... b = %d", b); {
                int b0 = b;

                string bits = "";
                while(b > 0) {
                    bits += '0';
                    bits.back() += b&1;
                    b >>= 1;
                }

                b = b0;

                reverse(all(bits));

                infof("... b = %s", bits.c_str());
            }
            infof("... c = %d", c); {
                int c0 = c;

                string bits = "";
                while(c > 0) {
                    bits += '0';
                    bits.back() += c&1;
                    c >>= 1;
                }

                c = c0;

                reverse(all(bits));

                infof("... c = %s", bits.c_str());
            }
        #endif

        vector<bool> bits(idx + 1);
        int c0 = c, j = idx;
        while(c > 0) {
            bits[j--] = c & 1;
            c >>= 1;
        }

        for(auto b: bits)
            infor("%d", (int)b);
        infof("");

        c = c0;

        int ii = ops.size();

        for(j = 0; j <= idx; ++j) {
            if(j > 0) {
                ops.push_back({qi, qi});
                infof("add op: x *= 2");
            }

            if(bits[j]) ops.push_back({qi, qj});
            if(bits[j]) infof("add op: x += k");
        }

        for(int i = 0; i < b - c; ++i) {
            ops.push_back({qi, qj});
            infof("add op: x += k");
        }

        reverse(ops.begin() + ii, ops.end());

        if(x0 > 0) s.insert({-x0, qi});
    }

    reverse(all(ops));

    auto getc = [&](int i) -> char {
        return i + 'a';
    };

    assert(ops.size() + 1 <= MAXQ);

    #ifdef DEBUG
        for(int i = 0; i < N; ++i)
            cout << getc(i) << "=" << 0 << lf;

        cout << "N=" << N << lf;
        cout << "Q=";
    #endif

    cout << ops.size() + 1 << lf;

    {
        auto [x, i] = *s.begin();
        cout << getc(i) << "=" << -x*g << lf;
        // probably just =g is fine
    }

    for(auto [i, j]: ops) {
        cout << getc(i) << "+=" << getc(j) << lf;
    }

    #ifdef DEBUG
        printf("print(f'=========== N = {N} | Q = {Q} ===========')\n");

        for(int i = 0; i < N; ++i) {
            printf("print(f'%c = {%c:>10} | expected: %10lld')\n",
                getc(i), getc(i), V[i]);
        }
    #endif
}
