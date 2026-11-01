#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<pair<int, int>> stila(int N, int M, int Q, vector<int> C,
        vector<int> T, vector<int> S) {
    vector x(N, vector<int>(M, 0));
    for(int i = 0; i < Q; ++i) {
        x[C[i]][T[i]] = max(x[C[i]][T[i]], S[i]);
    }

    vector<int> s(N);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            s[i] += x[i][j];
        }
    }

    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 0);

    sort(ord.begin(), ord.end(), [&](int i, int j) -> bool {
        return s[i] > s[j];
    });

    vector<pair<int, int>> R(N);
    for(int i = 0; i < N; ++i) {
        R[i] = {ord[i], s[ord[i]]};
    }

    return R;
}
