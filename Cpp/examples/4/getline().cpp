//getline的任何功能，get均能实现。而且get能实现单字符的输入 
#include <string>
#include <iostream>
using namespace std;

int main () {
	string s,s2;
	char a[100], b[100];
	
	getline(cin,s);
	getline(cin,s2);
	cout << s <<'\n'<< s2 << std::endl;
	
	cin.getline(a, 100);
	cin.getline(b, 100);
	cout << a << endl << b << endl;
	
	system("pause");
	return 0;
}
