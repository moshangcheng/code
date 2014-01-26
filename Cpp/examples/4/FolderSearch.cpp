#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <io.h>
using namespace std;


//缺点是在给出的路径是一个文件而不是文件夹时有BUG
vector<string> file;
void filesearch(const string& path)
{
	struct _finddata_t filefind;
	string curr = path + "\\*.*";
	int done = 0;
	int handle;
	
	if((handle = _findfirst(curr.c_str(), &filefind)) == -1)
		return;
	while(!(done = _findnext(handle,&filefind)))	{
		if(filefind.name[0] == '.')
			continue;
        curr = path + "\\" + filefind.name;
		if((_A_SUBDIR == filefind.attrib))	{
			filesearch(curr);
		}
		else	{
			file.push_back(curr);
		}
	}
	_findclose(handle);
}

int main() {
	string path = "F:\\doc\\课程讲义和习题答案\\JavaScript\\精通JavaScript\\Chapter05";
	filesearch(path);
	for(int i = 0; i < file.size(); i++)	{
		cout << i << ":" << file[i] << endl;
	}
	return 0;
}

