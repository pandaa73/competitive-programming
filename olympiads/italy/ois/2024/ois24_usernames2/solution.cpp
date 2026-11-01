#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<

constexpr int N = 1e5+7;
constexpr int MOD = 1e9+7;

using ll = long long;

string get_numstr(string s, int add) {
    if(!add) return s;

    return (s + to_string(add));
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s; cin >> s;
    
    int n; cin >> n;
    set<string> v;

    for(int i = 0; i < n; ++i) {
        string x; cin >> x;
        v.insert(x);
    }

    ll add = 0;
    while(v.find(get_numstr(s, add)) != v.end()) ++add;

    cout << get_numstr(s, add) << lf;
}