#include <bits/stdc++.h>
using namespace std;

bool ordina(int n, vector<int> v, vector<int>& l) {
    int count = 1, f;

    vector<int> u;
    for(int i = 1; i < n; ++i) {
        if(count == 1) f = v[i];
        if(v[i-1] < v[i]) {
            l.push_back(count);
            u.push_back(v[i-1]);
            u.push_back(f);
            count = 1;
            continue;
        } count++;
    }
    l.push_back(count);
    u.push_back(v.back());
    u.push_back(f);

	return is_sorted(u.begin(), u.end());
}
