#include <bits/stdc++.h>
using namespace std;
// flag[10]

long long n, m;
long long curr, best;

void Solve(long long num, long long prev, int digits = 1) {
    best = max(best, num %m);
    if(digits == n) return;

    long long next = num;
    prev = (prev + 3) %9;
    if(prev == 0) prev = 9;
    next = 10*next + prev;
    curr++;

    Solve(next, prev, digits+1);

    next = num;
    prev = (prev + 3) % 9;
    if(prev == 0) prev = 9;
    next = 10*next + prev;
    curr++;

    Solve(next, prev, digits+1);
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int T; cin >> T;

    for(int t = 0; t < T; t++) {
        cin >> n >> m;
        if(m == 3) {
            cout << 0 << " ";
            continue;
        }

        curr = 0;
        best = 3%m;

        Solve(3, 3);
        best = max(best, 6%m);

        Solve(6, 6);
        best = max(best, 9%m);

        Solve(9, 9);
        cout << best << " ";
    }
}