#include <map>
#include <iostream>
#include <string>
#include <iostream>

using namespace std;

map <string, int> mp;
int N, D;

int main()
{
	char s[1001];
	
	scanf("%d%d", &N, &D);
	
	for(int i = 0; i < N; i++)
	{
		scanf("%s", s);
		int tran = s[0] - 'a';
		for(int j = 0; j < D; j++)
		{
			s[j] -= tran;
			if(s[j] < 'a') s[j] += 26;
		}
		mp[s]++;
	}
	int ris = 0;
	for(auto item: mp)
	{
		if(item.second > ris)
		{
			ris = item.second;
		}
	}
	cout << ris;
}