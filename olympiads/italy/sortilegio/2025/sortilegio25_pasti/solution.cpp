// @check-accepted: examples same_weight exponential no_limits
#include <vector>
#include <bitset>
using namespace std;

constexpr int MAXN = 1e5+7;

int dividi(int N, vector<int> V) {
    bitset<MAXN> kp; kp[0] = 1;

    int sum = 0;
    for(auto x: V) {
        sum += x;
        kp |= kp << x;
    }

    return 2 * kp._Find_next((sum - 1) / 2) - sum;
}
