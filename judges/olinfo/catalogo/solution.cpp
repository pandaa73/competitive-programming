#include <bits/stdc++.h>
using namespace std;
// flag[10]

map<long long, int> mp;

void aggiungi(long long id) { mp[id]++;}
void togli(long long id) { mp[id]--; }
int conta(long long id) { return mp[id]; }