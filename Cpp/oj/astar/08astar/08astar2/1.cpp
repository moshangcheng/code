#include <iostream>
#include <string>
#include <set>
using namespace std;

set<string> word[200], cy;//word[i]表示一组汉字 
string cls[200], s, str, tmp;

int main()
{
	int i, j, k, m, n, flag;
	set<string>::iterator cnt;
	while(cin >> n >> m)	{
		cy.clear();
		for(i = 0; i < n; i++) {
			word[i].clear();
			cin >> cls[i];
			for(j = 0; j < cls[i].size(); j += 2)
				word[i].insert(cls[i].substr(j, 2));//输入处理，获得一组汉字 
		}
		for(i = 0; i < m; i++) {
			cin >> s;
			cy.insert(s);
		}
		cin >> s;
		flag = 0;
		for(i = 0; i < s.size() && !flag; i += 2) {
			str = s.substr(i, 2);
			for(j = 0; j < n && !flag; j++) {
				if(word[j].find(str) == word[j].end())	continue;
				//在成语中将每个字用这个字所在汉字组中的汉字代替 
				for(cnt = word[j].begin(); cnt != word[j].end(); cnt++) {
					tmp = s.substr(0, i) + (*cnt) + s.substr(i+2);//新的词组 
					if(cy.find(tmp) != cy.end() && tmp != s)	{//判断此词组是否是成语 
						flag = 1;
						break;
					}
				}
			}
		}
		cout << tmp << endl;	
	}
	return 0;
}
