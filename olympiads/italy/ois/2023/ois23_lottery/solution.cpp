// Codice di James

#include <bits/stdc++.h>
using namespace std;

inline int maxsum(int n){
    return (n/3)*26 + (n%3)*9;
}

inline int minsum(int n){
    return n/3;
}

inline bool isPossible(int ris, int qualcosa, string s, int x) {
	int len = s.length();
	s[ris] = qualcosa + '0';

	for(int i=ris-1; i>=0; i--){
		bool cond = false;
		for(int j=0; j<10; j++){

			if(i<len-2 and s[i+1] == '0'+j and s[i+2] == '0'+j)
				continue;

			int nines = 0;
			if(j == 9){
				nines++;
				if(s[i+1]== '9'){
					nines++;
				}
			}

			int zeros = 0;
			if(j == 0){
				zeros++;
				if(s[i+1]== '0'){
					zeros++;
				}
			}

			int mx = maxsum(i) + j;
			int mn = minsum(i) + j;

			if(i%3+nines >= 3)
				mx--;
			if(i%3+zeros >= 3)
				mn++;

			if(x <= mx and x >= mn){
				s[i] = j + '0';
				x -= j;
				cond = true;
				break;
			}
		}
		if(!cond){
			return 0;
		}
	}

	return 1;
}

inline void solve(){
    int n; cin >> n;
    string s; cin >> s;
    int len = s.length();

    int sum[len+1];
    sum[len] = 0;
    int prev = -1;
    int start = -1;
    int f = 0;
    reverse(s.begin(), s.end());
    for(int i=len-1; i>=0; i--){
        sum[i] = sum[i+1] + s[i]-'0';

        if(s[i] == prev)
            f++;
        else
            f = 1;

        if(f > 2 and start == -1){
            start = i;
        }
        prev = s[i];
    }

    if(sum[0] == n and start == -1){
        reverse(s.begin(), s.end());
        cout << s << "\n";
        return;
    }

    int mins = minsum(len+1);
	if((len+1)%3)
		mins++;

    if(mins > n){
        cout << -1 << "\n";
        return;
    }

    int ris = -1;
    bool cond = false;
    if(start == -1) start = 0;
    for(int i=start; i<len; i++){
        int st = s[i] - '0' +1;
        for(int j = st; j<10; j++){

            if(i<len-2 and s[i+1] == '0'+j and s[i+2] == '0'+j)
                continue;

            int nines = 0;
            if(j == 9){
                nines++;
                if(s[i+1]== '9'){
                    nines++;
                }
            }


            int mx = maxsum(i) + sum[i+1] + j;
            int mn = minsum(i) + sum[i+1] + j;

            if(i%3+nines >= 3)
                mx--;

            if(n <= mx and n >= mn and isPossible(i, j, s, n-sum[i+1]-j)) {
                s[i] = j + '0';
                ris = i;
				cond = true;

				break;
            }
        }
        if(cond)
            break;
    }
    int i = len;
    while(!cond){
        s.push_back('0');
        for(int j = 1; j<10; j++){
            int mx = maxsum(i) + j;
            int mn = minsum(i) + j;

			int nines = 0;
			if(j == 9){
				nines++;
				if(s[i+1]== '9'){
					nines++;
				}
			}
			if(i%3+nines >= 3)
				mx--;

            if(n <= mx and n >= mn){
                s[i] = j + '0';
                ris = i;
                cond = true;
                break;
            }
        }
        i++;
    }

    int x = s[ris] - '0';
    if(ris < len)
        x += sum[ris+1];
    x = n-x;

    for(int i=ris-1; i>=0; i--){
        cond = false;
        for(int j=0; j<10; j++){

            if(i<len-2 and s[i+1] == '0'+j and s[i+2] == '0'+j)
                continue;

            int nines = 0;
            if(j == 9){
                nines++;
                if(s[i+1]== '9'){
                    nines++;
                }
            }

            int zeros = 0;
            if(j == 0){
                zeros++;
                if(s[i+1]== '0'){
                    zeros++;
                }
            }

            int mx = maxsum(i) + j;
            int mn = minsum(i) + j;

            if(i%3+nines >= 3)
                mx--;
            if(i%3+zeros >= 3)
                mn++;

            if(x <= mx and x >= mn){
                s[i] = j + '0';
                x -= j;
                cond = true;
                break;
            }
        }
        if(!cond){
            cout << -1 << "\n";
            return;
        }
    }

    reverse(s.begin(), s.end());
    cout << s << endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}
