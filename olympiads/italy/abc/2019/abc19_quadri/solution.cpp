#include <bits/stdc++.h>
using namespace std;
// flag[10]

int quadri(int n, long long m, int v[]) {
    long long sum = 0;
    
    int l = 0, r, mn = INT_MAX;
    for(r = 0; r < n; ++r) {
        sum += v[r];
        while(sum > m && l <= r) { 
            mn = min(mn, r-l);
            sum -= v[l]; l++;
        }
    }
	
    return min(n, mn);
}
