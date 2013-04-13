/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-3-25 下午06:49:28
 * @brief http://acm.hdu.edu.cn/showproblem.php?pid=1298
 */
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <algorithm>
using namespace std;

//101所在的索引表示概率，2所在的索引分别存储合法单词和它对应的数字序列
//如果用一维数组，数组的长度必须为3，额外增加一维存储概率
vector<string> p[101][2];
//存储符合输入数字序列的单词序列，第一维表示概率，第二维表示在字典中的位置
list<pair<int, int> > L;
map<string, int> M;
list<pair<int, int> >::iterator cnt;
char c[26] = { '2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6',
		'6', '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9' };

//将一个单词转换成对应的数字序列
string convert(const string& a) {
	string b;
	for (int i = 0; i < a.size(); i++)
		b += c[a[i] - 'a'];
	return b;
}

void output(int len) {
	int i, j, max;
	string tmp;
	M.clear();
	map<string, int>::iterator m_cnt, max_e;
	//计算前缀相同的单词的概率之和
	for (cnt = L.begin(); cnt != L.end(); cnt++)
		M[p[cnt->first][0][cnt->second].substr(0, len)] += cnt->first;
	m_cnt = max_e = M.begin();
	for (m_cnt++; m_cnt != M.end(); m_cnt++)
		if (m_cnt->second > max_e->second)
			max_e = m_cnt;
	cout << max_e->first << endl;
}

int main() {
	string s, numb;
	int ntest, otest = 0;
	int i, j, k, tmp, m, nword;
	cin >> ntest;
	while (otest++ < ntest) {
		cin >> nword;
		for (i = 0; i < 101; i++) {
			p[i][0].clear();
			p[i][1].clear();
		}
		for (i = 0; i < nword; i++) {
			cin >> s >> tmp;
			p[tmp][0].push_back(s);
			p[tmp][1].push_back(convert(s));
		}
		cout << "Scenario #" << otest << ":\n";
		cin >> m;
		for (i = 0; i < m; i++) {
			L.clear();
			cin >> numb;
			if (numb[0] == '1') {
				cout << endl;
				continue;
			}
			//存储所有符合第一个数的单词，概率最大的单词存储在链表的起始端
			for (j = 100; j >= 0; j--)
				for (k = 0; k < p[j][1].size(); k++)
					if (p[j][1][k][0] == numb[0])
						L.push_back(make_pair(j, k));
			for (j = 1; j < numb.size(); j++) {
				//输出
				if (L.empty())
					cout << "MANUALLY\n";
				else
					output(j);
				if (numb[j] == '1')
					break;
				//所有不符合当前数字的单词必须过滤掉
				for (cnt = L.begin(); cnt != L.end();)
					if (p[cnt->first][1][cnt->second][j] != numb[j])
						cnt = L.erase(cnt);
					else
						cnt++;
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}

