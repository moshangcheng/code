#include <iostream>
#include <string>
#include <sstream>
using namespace std;

bool isvowel[26] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
					0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0};
					
int vowel(const string& str)	{
	int i, sum = 0;
	for(i = 0; i < str.size(); i++){
		if(isvowel[str[i]-'a'])	sum++;
		while(i < str.size() && isvowel[str[i]-'a']) i++;
	}
	return sum;
}
		
int main()
{
	string s, word;
	istringstream is;
	int sum, slh1, slh2;
	while(getline(cin, s))	{
		if(s == "e/o/i")	break;
		slh1 = s.find('/', 0);
		slh2 = s.find('/', slh1+1);
		is.clear();
		is.str(s.substr(0, slh1));
		sum = 0;
		while(is >> word)	
			sum += vowel(word);
		if(sum != 5) {
			cout << 1 << endl;
			continue;
		}
		is.clear();
		is.str(s.substr(slh1+1, slh2-slh1-1));
		sum = 0;
		while(is >> word)	
			sum += vowel(word);
		if(sum != 7) {
			cout << 2 << endl;
			continue;
		}
		is.clear();
		is.str(s.substr(slh2+1));
		sum = 0;
		while(is >> word)	
			sum += vowel(word);
		if(sum != 5) {
			cout << 3 << endl;
			continue;
		}
		cout << 'Y' << endl;
	}
	return 0;
}
