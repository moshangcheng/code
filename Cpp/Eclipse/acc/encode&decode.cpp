#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

/*  unicode     utf-8
	0000 - 007F	0xxxxxxx
	0080 - 07FF	110xxxxx 10xxxxxx
	0800 - FFFF 1110xxxx 10xxxxxx 10xxxxxx
*/
void utf2unicode(const char* src, wchar_t* answer)    {
	wchar_t tmp;
	int len = strlen(src);
	for(int i = 0, j = 0; i < len; j++) {
		if((src[i] & (0xFF)) < 0x80)    {//0xxxxxxx
		    tmp = src[i];
		    i++;
		}
		else if((src[i] & (0xFF)) < 0xE0)  {//110xxxxx 10xxxxxx
		    tmp = (src[i] & 0x1F) * 64 + (src[i+1] & 0x3F);
		    i += 2;
		}
		else    {//1110xxxx 10xxxxxx 10xxxxxx
			tmp = (src[i] & 0xF) * 64 * 64 + (src[i+1] & 0x3F) * 64  + (src[i+2]);
			i += 3;
		}
		answer[j] = tmp;
	}
}

void unicode2utf_eight(const wchar_t* src, char* answer)   {
	int len = strlen(src);
    for(int i = 0, j = 0; i < len; i += 2) {
		int sum = src[i]*256 + src[i+1];
		if(sum < 0x0080)   {//0000 - 007F
			answer[j] = (src[i] & 0x00FF);
			j++;
		}
		else if(sum < 0x0800)    {//0080 - 07FF
			answer[j] = (0xC0 + (sum/64)) * 0xFF + (0x80 + sum%64);
		}
		else {//0800 - FFFF
			answer[j] = (0xE0 + (sum/4096)) * 0xFF * 0xFF + (0x80 + ((sum%4096)/64)) * 0xFF + (0x80 + sum%64);
		}
	}
}

//To be completed
void gb2unicode(const string& src, string& answer)   {
    for(int i = 0; i < src.size(); i++) {

	}
}
//To be completed
void unicode2gb(const string& src, string& answer)   {
  	answer.clear();
    for(int i = 0; i < src.size(); i++) {
		answer += src[i] - (0x8080);
	}
}

void gb2machine_code(const string& src, string& answer)   {
  	answer.clear();
    for(int i = 0; i < src.size(); i++) {
		answer += src[i] + (0x8080);
	}
}

void machine_code2gb(const string& src, string& answer)   {
	answer.clear();
    for(int i = 0; i < src.size(); i++) {
		answer += src[i] - (0x8080);
	}
}


int main()
{
	system("pause");
	return 0;
}
