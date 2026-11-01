#include <bits/stdc++.h>
using namespace std;

#define lf "\n"
#define ff endl
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#define infos(str) do { fprintf(stderr, str"\n"); } while(0)
#define infor(str, ...) do { fprintf(stderr, str, __VA_ARGS__); } while(0)
#define infof(str, ...) do { fprintf(stderr, str"\n", __VA_ARGS__); } while(0)

#ifndef DEBUG

#undef infos
#undef infor
#undef infof

#define infos(str)
#define infor(str, ...)
#define infof(str, ...)

#endif

using ll = long long;

constexpr int LOG = 10;
constexpr int MOD = 1e9+7;
constexpr int MAXN = 1e5+7;

void series(vector<int> G);
vector<int> disconnect(vector<int> L);

void study(int N) {
    vector<array<vector<int>, 2>> Qs(1), tmpQs;

    Qs[0][0] = vector<int>(N); iota(all(Qs[0][0]), 0);

    while(!Qs.empty()) {
        vector<int> ask;

        for(auto &[nodes, qry]: Qs) {
            if(qry.empty()) qry = nodes;
            if(qry.size() == 1) {
                qry = {};
                series(nodes);

                continue;
            }

            auto new_qry = vector<int>(
                qry.begin(),
                qry.begin() + qry.size() / 2
            );

            for(auto x: new_qry)
                ask.push_back(x);
        }

        if(ask.empty()) break;

        auto v = disconnect(ask);

        for(auto &[nodes, qry]: Qs) {
            if(qry.empty()) continue;

            auto new_qry = vector<int>(
                qry.begin(),
                qry.begin() + qry.size() / 2
            );

            vector<int> new_qr2;
            for(int i = qry.size() / 2; i < qry.size(); ++i)
                if(v[qry[i]]) new_qr2.push_back(qry[i]);

            vector<int> l, r;
            for(auto nd: nodes)
                (v[nd] ? r : l).push_back(nd);

            if(!l.empty()) tmpQs.push_back({l, new_qry});
            if(!r.empty()) tmpQs.push_back({r, new_qr2});
        }

        Qs.clear();
        swap(Qs, tmpQs);
    }
}
