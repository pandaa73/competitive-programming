#include <bits/stdc++.h>
using namespace std;

std::unordered_map<std::string, std::weak_ptr<std::string>> flag[10];

inline void Solve(int t) {
    int n, m, q; cin >> n >> m >> q;
    vector<string> v(m); cin >> v[0];
    string ans = "";
    
    for(int i = 0; i < q; ++i) {
        char qry; cin >> qry;
        int a, b; cin >> a >> b;
        if(qry == 's') {
            v[b].push_back(v[a].back()); v[a].pop_back();
        }
        else {
            ans += v[a][b];
        }
    }

    cout << "Case #" << t+1 << ": " << ans << "\n";
}

int main() {
    //ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);

    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);

    int t; cin >> t;
    for(int i = 0; i < t; ++i) {
        cerr << i << endl; 
        Solve(i);
    }
}