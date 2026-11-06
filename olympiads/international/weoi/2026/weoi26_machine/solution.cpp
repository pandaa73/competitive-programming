// This does not always use at most 23 instructions. The worst case is
// N = 827570 which uses 26 instructions.

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

void add_halt(void);
void add_increment(int x, int i);
void add_decrement(int x, int i, int j);

vec<pii> convert(int N, int B) {
    vec<pii> ans;
    for(; N > 0; N /= B) {
        int d = N % B;

        if(ans.empty() || ans.back().fi != d) {
            ans.emplace_back(d, 1);
        } else {
            ans.back().se += 1;
        }
    }

    reverse(all(ans));

    return ans;
}

void build_machine(int N, int B) {
    int curr_i = 0;

    auto A = convert(N, B);

    int reg = 2;
    for(auto [d, c]: A) {
        while(c--) {
            add_increment(reg, curr_i + 1);
            curr_i += 1;
        }

        reg += 1;
    }

    vec<int> add(B + 1);

    int loop = curr_i;

    add_decrement(0, curr_i + B + 1, curr_i + 1);
    curr_i += 1;

    for(int b = B; b > 1; b--) {
        add[b] = curr_i;
        add_increment(1, curr_i + 1);
        curr_i += 1;
    }

    add[1] = curr_i;
    add_increment(1, loop);
    curr_i += 1;

    add[0] = loop;

    assert(curr_i == loop + B + 1);

    loop = curr_i;
    add_decrement(1, curr_i + 2, curr_i + 1);
    curr_i += 1;

    add_increment(0, loop);
    curr_i += 1;

    reg = 2;
    for(auto [d, c]: A) {
        add_decrement(reg, curr_i + 1, add[d]);
        curr_i += 1;
        reg += 1;
    }

    add_halt();
}

void program_machine(int N) {
    int best_B = -1, best_x = 101;
    for(int B = 2; B <= 20; ++B) {
        auto A = convert(N, B);

        int s = 0;
        for(auto [d, c]: A) {
            s += c;
        }

        int x = A.size() + s + B + 4;

        if(x < best_x) {
            best_B = B;
            best_x = x;
        }
    }

    build_machine(N, best_B);
}

#ifdef LOCAL

#define NUM_REGISTERS 64
#define MAX_PROGRAM_LENGTH 100
#define MAX_ITERATIONS 50000000

#define INCREMENT 0
#define DECREMENT 1
#define HALT 2

void program_machine(int N);
void add_increment(int x, int i);
void add_decrement(int x, int i, int j);
void add_halt();

struct instruction {
    int type;
    int x; int i; int j;
} instructions[MAX_PROGRAM_LENGTH];

int registers[NUM_REGISTERS];

int instruction_count = 0;

[[noreturn]] static void wa(const string& message) {
    cerr << "WA " << message << '\n';
    exit(0);
}

void add_increment(int x, int i) {
    if (instruction_count == MAX_PROGRAM_LENGTH) {
        cout << "Program too long." << endl;
        exit(0);
    }
    if (x < 0 || x >= NUM_REGISTERS) {
        cout << "Invalid register." << endl;
        exit(0);
    }

    println("{:02}: INC r{:02} -> {:02}", instruction_count, x, i);

    instructions[instruction_count] = {INCREMENT, x, i};
    instruction_count++;
}

void add_decrement(int x, int i, int j) {
    if (instruction_count == MAX_PROGRAM_LENGTH) {
        cout << "Program too long." << endl;
        exit(0);
    }
    if (x < 0 || x >= NUM_REGISTERS) {
        cout << "Invalid register." << endl;
        exit(0);
    }

    println("{:02}: DEC r{:02} -> [{:02}, {:02}]", instruction_count, x, i, j);

    instructions[instruction_count] = {DECREMENT, x, i, j};
    instruction_count++;
}

void add_halt() {
    if (instruction_count == MAX_PROGRAM_LENGTH) {
        cout << "Program too long." << endl;
        exit(0);
    }

    println("{:02}: HLT", instruction_count);

    instructions[instruction_count] = {HALT};
    instruction_count++;
}

int main() {
    int N;
    cin >> N;

    program_machine(N);

    memset(registers, 0, sizeof(registers));
    int ip = 0; // instruction pointer
    for (int cnt = 0; cnt < MAX_ITERATIONS; cnt++) {
        if (instructions[ip].type == HALT) {
            if (registers[0] != N) {
                wa("Register 0 does not contain the correct value at halt.");
            }
            cout << "OK " << instruction_count << endl;
            return 0;
        }
        if (instructions[ip].type == INCREMENT) {
            registers[instructions[ip].x]++;
            if (instructions[ip].i < 0 || instructions[ip].i >= instruction_count) {
                wa("Invalid instruction index in increment.");
            }
            ip = instructions[ip].i;
        } else {
            if (registers[instructions[ip].x] == 0) {
                if (instructions[ip].i < 0 || instructions[ip].i >= instruction_count) {
                    wa("Invalid instruction index in decrement.");
                }
                ip = instructions[ip].i;
            } else {
                registers[instructions[ip].x]--;
                if (instructions[ip].j < 0 || instructions[ip].j >= instruction_count) {
                    wa("Invalid instruction index in decrement.");
                }
                ip = instructions[ip].j;
            }
        }
    }
    wa("Too many iterations without halting.");
    return 0;
}

#endif /* LOCAL */
