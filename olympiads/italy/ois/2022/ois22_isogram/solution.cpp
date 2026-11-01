// NOTE: it is recommended to use this even if you don't understand the following code.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// input data
int N;
string S;

bool isLettera(char c)
{
	if(c >= 'a' and c <= 'z')
		return true;
	if(c >= 'A' and c <= 'Z')
		return true;
	
	return false;
}

bool cmp(char a, char b)
{
	return a%32 < b%32;
	
}

int main() {
//  uncomment the following lines if you want to read/write from files
//  ifstream cin("input.txt");
//  ofstream cout("output.txt");

    cin >> N;
    cin.ignore();
    int conta=0;



    for(int i=0; i<N; i++) 
	{
        getline(cin, S);
        
        vector<char> v;
        
        for(int j=0; j < S.length(); j++)
        {
			if(isLettera(S[j]))
				v.push_back(S[j]);
		}
 
        
		sort(v.begin(), v.end(), cmp);

		
		bool isogram = true;
		int len = v.size()-2;
		
		for(int j=0; j<len; j++)
		{	
			if(v[j] % 32 == v[j+1] % 32 and v[j] % 32 == v[j+2] % 32)
			{
				isogram = false;
				break;
			}

		}
		
		if(isogram)
			conta++;
        
    }

    cout << conta << endl; // print the result
    return 0;
}
