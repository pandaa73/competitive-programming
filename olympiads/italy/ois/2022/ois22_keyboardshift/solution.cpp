#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	
	string alph = "qwertyuiopasdfghjklzxcvbnm";
	
	string out;
	string S;
	cin >> S;
	
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < 26; j++)
		{
			if(S[i] == alph[j])
			{
				out += alph[j+1];
			}
		}
	}
	
	cout << out;
}
