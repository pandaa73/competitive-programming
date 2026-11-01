#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define _ << " " <<

using ll = long long;

vector<int> verifica(int N, vector<int> T) {
    vector<int> pr(N); pr[0] = T[0];
    for(int i = 1; i < N; ++i) {
        if(T[i] < pr[i - 1]) {
            pr[i] = T[i];
            continue;
        }

        pr[i] = pr[i - 1] - 1;
    }

    vector<int> sf(N); sf[N - 1] = T[N - 1];
    for(int i = N - 2; i >= 0; i--) {
        if(T[i] < sf[i + 1]) {
            sf[i] = T[i];
            continue;
        }

        sf[i] = sf[i + 1] - 1;
    }

    int mx = -1, idx = -1;
    for(int i = 0; i < N; ++i) {
        if(pr[i] < 0 || sf[i] < 0) continue;
            
        if(pr[i] + sf[i] > mx)
            mx = pr[i] + sf[i], idx = i;
    }

    if(idx == -1) return (vector<int>){};

    vector<int> ans;
    ans.push_back(idx);

    int l = idx, r = idx, t = 1;
    while(l > 0 || r < N - 1) {
        // cerr << l _ r _ t << lf;
        int susl = INT_MAX;
        if(l > 0) {
            susl = pr[l - 1];
        }

        int susr = INT_MAX;
        if(r < N - 1) {
            susr = sf[r + 1];
        }

        // cerr << susl _ susr << lf;

        if(susl == susr && susl == INT_MAX) break;

        if(susl < susr) {
            if(t > susl) break;
            ans.push_back(--l);
        }
        else {
            if(t > susr) break;
            ans.push_back(++r);
        }

        t++;
    }

    if(ans.size() < N) return (vector<int>){};

    return ans;
}