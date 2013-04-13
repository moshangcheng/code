/**
 * @author moshangcheng
 * @date 2011-3-16 上午11:13:49
 * @brief 逐行判断两个文件是否完全一致
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream ans(ansPath);
	ifstream out(outPath);
	if (ans.exceptions()) {
		cout << "答案文件读取错误\n";
	}
	if (out.exceptions()) {
		cout << "待校验文件读取错误\n";
	}

	bool flag = true;
	string correctText, myText;
	for (int i = 0; ; i++) {
		istream& streamAns = getline(ans, correctText);
		istream& streamOut = getline(out, myText);
		if(streamAns.fail())	{
			if(!streamOut.fail())	{
				flag = false;
				cout << "文件校对失败， 参考文件只有" << i << "行，我的文件行数超过参考文件\n";				
			}
			break;
		}
		if(streamOut.fail())	{
			flag = false;
			cout << "文件校对失败， 我的文件只有" << i << "行，参考文件行数超过我的文件\n";
			break;
		}
		if (myText.compare(correctText) != 0) {
			flag = false;
			cout << "文件校对失败，错误在第" << i+1 << "行\n";
			cout << "参考文件此行长度为" << correctText.length() << "，数据为: " << correctText << "\n";
			cout << "我的文件此行长度为" << myText.length() << "，数据为: " << myText << "\n";
			break;
		}
	}
	if (flag) {
		cout << "文件校验完成，两个文件匹配成功\n";
	}
	return 0;
}
