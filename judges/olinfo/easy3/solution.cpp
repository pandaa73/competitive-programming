#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;

	int p1 = 0, p2 = 0, d1 = 0, d2 = 0, p = 0, d = 0;
	for(int i = 0; i < n; ++i) {
		int x; cin >> x;
        if(x%2 == 0) {
            if(x > p1) p2 = p1, p1 = x;
            else if (x > p2) p2 = x;
            p++;
        } else {
			if(x > d1) d2 = d1, d1 = x;
            else if (x > d2) d2 = x;
            d++;
		}
	}

    p1 *= !p<2, d1 *= !p<2;
	
	if(p < 2 and d < 2)	cout << -1;
	else cout << max(p1+p2, d1+d2);
}