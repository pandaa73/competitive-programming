#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b, c; cin >> a >> b >> c;

    array<vector<int>, 3> v;
    int count = 1;
    string a1 = ""; a1 += a[0];
    for(int i = 1; i < a.length(); ++i)
        if(a[i] != a[i-1]) a1 += a[i], v[0].push_back(count), count = 1;
        else ++count;
    v[0].push_back(count); 

    count = 1;
    string b1 = ""; b1 += b[0];
    for(int i = 1; i < b.length(); ++i)
        if(b[i] != b[i-1]) b1 += b[i], v[1].push_back(count), count = 1;
        else ++count;
    v[1].push_back(count); 

    count = 1;
    string c1 = ""; c1 += c[0];
    for(int i = 1; i < c.length(); ++i)
        if(c[i] != c[i-1]) c1 += c[i], v[2].push_back(count), count = 1;
        else ++count;
    v[2].push_back(count); 

    if(a1 != b1 || b1 != c1) { cout << "IMPOSSIBLE"; return 0; }

    int x[a1.length()];
    for(int i = 0; i < a1.length(); ++i) {
        if((v[0][i] >= v[1][i] && v[0][i] <= v[2][i]) || (v[0][i] <= v[1][i] && v[0][i] >= v[2][i])) x[i] = v[0][i];
        else if((v[1][i] >= v[0][i] && v[1][i] <= v[2][i]) || (v[1][i] <= v[0][i] && v[1][i] >= v[2][i])) x[i] = v[1][i];
        else x[i] = v[2][i];
    }
    
    string ans = "";
    for(int i = 0; i < a1.length(); ++i) 
        for(int j = 0; j < x[i]; ++j)
            ans += a1[i];

    cout << ans;
}
