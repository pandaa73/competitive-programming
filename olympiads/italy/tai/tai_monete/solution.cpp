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

struct MinQueue {
    MinQueue(void): s(0), t(0) {}

    void push(int x) {
        while(!q.empty() && q.back().fi >= x) {
            q.pop_back();
        }

        q.emplace_back(x, t++);
    }

    void pop(void) {
        if(!q.empty() && q.front().se <= s) {
            q.pop_front();
        }

        s += 1;
    }

    int top(void) {
        return q.empty() ? 0 : q.front().fi;
    }

    int s, t;
    deque<pii> q;
};

int best_score(int N, int K, vector<int> &V) {
    MinQueue q;
    for(int i = 0; i < K; ++i) {
        q.push(0);
    }

    int s = 0, x;
    for(int i = 0; i < N; ++i) {
        s += V[i];
        x = s - q.top();

        q.push(x);
        q.pop();
    }

    return x;
}

#ifdef LOCAL

int main(){
	int N, K;
	cin>>N>>K;
	vector<int> v(N);
	for(int i=0;i<N;i++)
		cin>>v[i];
	cout<<best_score(N,K,v);
}

#endif /* LOCAL */
