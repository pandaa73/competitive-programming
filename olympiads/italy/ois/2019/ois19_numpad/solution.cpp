#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s; cin >> s;

    int dist[][10] = {
        {1, 4, 3, 4, 3, 2, 3, 2, 1, 2},
        {4, 1, 1, 2, 1, 2, 3, 2, 3, 4},
        {3, 1, 1, 1, 2, 1, 2, 3, 2, 3},
        {4, 2, 1, 1, 3, 2, 1, 4, 3, 2},
        {3, 1, 2, 3, 1, 1, 2, 1, 2, 3},
        {2, 2, 1, 2, 1, 1, 1, 2, 1, 2},
        {3, 3, 2, 1, 2, 1, 1, 3, 2, 1},
        {2, 2, 3, 4, 1, 2, 3, 1, 1, 2},
        {1, 3, 2, 3, 2, 1, 2, 1, 1, 1},
        {2, 4, 3, 2, 3, 2, 1, 2, 1, 1}
    };

    ll sum = 0;
    char curr = '0';
    for(auto c: s) sum += (curr != c) + dist[curr - '0'][(curr = c) - '0'];

    cout << sum << lf;
}