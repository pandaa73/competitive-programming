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

struct GuessResult {
    int comparison;  //  1: your guess was too low, -1: your guess was too high
    bool swapped;    // whether Rybina swapped the two halves (A B <-> B A) after this guess
};

GuessResult guess(long long X);

void rybina_search(int N) {
    const int INF = pow(10, N);

    int l = 0, r = INF;
    int l1 = 0, r1 = INF;

    while(r - l > 1) {
        int m = (l + r) / 2;

        auto [c, sw] = guess((ll)m * INF);

        if(c > 0) {
            l = m;
        } else {
            r = m;
        }

        if(sw) {
            swap(l, l1);
            swap(r, r1);
        }
    }

    bool side = r - l > 1;
    if(!side) {
        swap(l, l1);
        swap(r, r1);
    }

    while(r - l > 1) {
        int m = (l + r) / 2;

        ll X = side == 0 ? (ll)l1 * INF + m : (ll)m * INF + l1;
        auto [c, sw] = guess(X);

        if(c > 0) {
            l = m;
        } else {
            r = m;
        }

        side ^= sw;
    }

    ll X = side == 0 ? (ll)l1 * INF + l : (ll)l * INF + l1;
    guess(X);

    assert(0 && "unreachable");
}

#ifdef LOCAL

namespace {

constexpr int kMaxGuesses = 64;

int N;
long long half_size;
long long full_size;
long long password;
int num_guesses = 0;
mt19937 rng;

void fail(string msg) {
    cerr << msg << endl;
    exit(0);
}

} // namespace

GuessResult guess(long long X) {
    num_guesses++;
    if (num_guesses > kMaxGuesses) {
        fail("Too many guesses.");
    }
    if (X < 0 || X >= full_size) {
        fail("Invalid guess.");
    }
    if (X == password) {
        cerr << "OK " << num_guesses << " guesses." << endl;
        exit(0);
    }

    int comparison = (X < password) ? 1 : -1;
    bool swapped = rng() & 1;
    if (swapped) {
        long long A = password / half_size, B = password % half_size;
        password = B * half_size + A;
    }

    infof("Query {:02}: guess({}) -> ({}, {})",
            num_guesses, X, comparison, swapped);

    return {comparison, swapped};
}

int main() {
    long long seed, target;
    cin >> N >> seed >> target;

    half_size = 1;
    for (int i = 0; i < N; ++i)
        half_size *= 10;
    full_size = half_size * half_size;

    password = target;
    rng.seed(seed);

    rybina_search(N);

    fail("No guess was correct.");
}

#endif /* LOCAL */
