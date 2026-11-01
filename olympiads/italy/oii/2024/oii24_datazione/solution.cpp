#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
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

constexpr int LOG = 20;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

struct SegTree {
    SegTree(int N): N(N), st(2 * N), mx(2 * N) {}

    void build(int v) {
        infof("... st.build(%d)", v);

        for(v >>= 1; v > 0; v >>= 1) {
            infof("... - v = %d: st[v] = %d | mx[l] = %d | mx[r] = %d",
                v, st[v], mx[v << 1], mx[v << 1 | 1]);

            if(mx[v] == 0)
                history.push(v);
            mx[v] = st[v] + max(mx[v << 1], mx[v << 1 | 1]);
        }
    }

    int get_mx(void) { return mx[1]; }

    void range_inc(int l, int r) {
        l += N, r += N;
        int l0 = l, r0 = r - 1;

        for(; l < r; l >>= 1, r >>= 1) {
            if(l&1) {
                if(mx[l] == 0)
                    history.push(l);
                st[l]++, mx[l]++;

                l++;
            }
            if(r&1) {
                --r;

                if(mx[r] == 0)
                    history.push(r);
                st[r]++, mx[r]++;
            }
        }

        build(l0), build(r0);
    }

    void clear(void) {
        while(!history.empty()) {
            int v = history.top();
            history.pop();

            st[v] = mx[v] = 0;
        }
    }

    int N;
    vector<int> st, mx;

    stack<int> history;
};

int radioline(int N, vector<int> L, vector<int> R) {
    for(auto &x: L) x--;

    vector<int> ord(N); iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) -> bool {
        return R[i] < R[j];
    });

    SegTree st(2 * N);

    auto f = [&](int K) -> int {
        infof("======= f(%d) =======", K);

        int ans = 0;
        int last_r = 0;

        for(int ii = 0; ii < N; ++ii) {
            int i = ord[ii];
            int l = L[i], r = R[i];

            if(l < last_r) continue;

            infof("... processing segment [%d, %d)", l, r);

            st.range_inc(l, r);

            infof("... - new max is %d", st.get_mx());

            int x = st.get_mx();

            if(N - ii < K - x) break;
            if(x < K) continue;

            ans++;
            last_r = r;
            st.clear();

            infof("----- cleared segment -----");
        }

        st.clear();

        infof("\nf(%d): ans = %d", K, ans);

        return ans;
    };

    vector<int> ans(N + 2); ans[0] = N;
    auto conquer = [&](int l, int r, auto &&conquer) -> void {
        if(l >= r) return;

        if(ans[l - 1] == ans[r]) {
            for(; l < r; ++l)
                ans[l] = ans[r];
            return;
        }

        int m = (l + r) / 2;

        ans[m] = f(m);

        conquer(l, m, conquer);
        conquer(m + 1, r, conquer);
    };

    conquer(1, N + 1, conquer);

    infor("ans:");
    for(auto x: ans)
        infor(" %d", x);
    infof("");

    int mx = 0;
    for(int i = 0; i <= N; ++i)
        mx = max(mx, i * ans[i]);

    return mx;
}

#ifdef DEBUG
int main() {
    ios::sync_with_stdio(false);

    int N;
    cin >> N;

	vector<int> L(N), R(N);
	for (int i = 0; i < N; ++i) {
		cin >> L[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> R[i];
	}

    cout << radioline(N, std::move(L), std::move(R)) << endl;

    return 0;
}
#endif
