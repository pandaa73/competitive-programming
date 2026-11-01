#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

bool associabili(int n, int voti2[], int voti5[]) {
    int cnt2[10]; memset(cnt2, 0x00, sizeof(cnt2));
    int cnt5[10]; memset(cnt5, 0x00, sizeof(cnt5));

    for(int i = 0; i < n; ++i)
        cnt2[voti2[i] - 1]++, cnt5[voti5[i] - 1]++;

    if(cnt2[9]) return 0;

    bool q = 1;
    int a = 0, b = 0;
    for(int i = 9; i > 0; i--) {
        a += cnt2[i - 1], b += cnt5[i];

        if(a > b) {
            q = 0;
            break;
        }

        b -= a, a = 0;
    }

    return q;
}