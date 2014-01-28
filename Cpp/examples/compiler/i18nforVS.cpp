/*
 一共有6个文件读写API
 本地编码对ASCII编码进行了扩展，一般是GB2312，数据的格式为机内码。所以汉字由两个字节表示，
 每个字节都大于128，区位码、国标码、机内码转换见 区位码.cpp
 分别是：ASCII编码文件的读写，读出是ASCII字符串，读入要求是ASCII字符串
 UTF8文件的读写，读出是UNICODE字符串，写入的数据要求是UNICODE字符串
 UNICODE文件的读写，读出是UNICODE字符串，写入的数据要求是UNICODE字符串
 vs对utf8、unicode、gbk编码支持较好
 */

/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-4-29 下午01:54:00
 * @brief i18n vs
 * @details 测试vs对国际化编码的支持
 */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>//必须
#include <clocale>//必须
using namespace std;

wchar_t native_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\native.txt";
wchar_t native2utf8_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\native2utf8.txt";
wchar_t native2unicode_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\native2unicode.txt";
wchar_t native2native_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\native2native.txt";

wchar_t utf8_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\utf8.txt";
wchar_t utf82native_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\utf82native.txt";
wchar_t utf82unicode_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\utf82unicode.txt";
wchar_t utf82utf8_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\utf82utf8.txt";

wchar_t unicode_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\unicode.txt";
wchar_t unicode2native_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\unicode2native.txt";
wchar_t unicode2utf8_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\unicode2utf8.txt";
wchar_t unicode2unicode_path[] = L"C:\\Documents and Settings\\moshangcheng\\桌面\\unicode2unicode.txt";

const int LINE_LENGTH = 100;
const int FILE_SIZE = 1000;

//fgets会把换行符读入到字符串，所以没问题
int readFile(char* data, const wchar_t* path) {
	memset(data, 0, sizeof(data));
	char text[LINE_LENGTH];
	FILE* in = _wfopen(path, L"r");
	if (in == NULL) {
		cout << "读入文件失败" << endl;
		return 0;
	}
	int len;
	for (len = 0; fgets(text, LINE_LENGTH, in); len += strlen(text)) {
		strcat(data, text);
	}
	fclose(in);
	return len;
}

//写本地编码的文件，即ascii编码文件
int writeFile(char* data, const wchar_t* path) {
	FILE* out = _wfopen(path, L"w");
	int len = strlen(data);
	fputs(data, out);
	fclose(out);
	return len;
}

//unicode文件的读取办法
//如果使用"rb"，换行符读入会出错
int readUnicodeFile(wchar_t* data, const wchar_t* path) {
	memset(data, 0, sizeof(data));
	wchar_t text[LINE_LENGTH];
	FILE* in = _wfopen(path, L"r,ccs=UNICODE");
	if (in == NULL) {
		cout << "读入文件失败" << endl;
		return 0;
	}
	int len;
	for (len = 0; fgetws(text, LINE_LENGTH, in); len += wcslen(text)) {
		wcscat(data, text);
	}
	fclose(in);
	return len;
}

//写Unicode文件
int writeUnicodeFile(wchar_t* data, const wchar_t* path) {
	FILE* out = _wfopen(path, L"w, ccs=UNICODE");
	int len = wcslen(data);
	fputws(data, out);
	fclose(out);
	return len;
}

//utf8文件的读取办法，读入后的数据为Unicode存储形式
int readUtf8File(wchar_t* data, const wchar_t* path) {
	memset(data, 0, sizeof(data));
	wchar_t text[LINE_LENGTH];
	FILE* in = _wfopen(path, L"r,ccs=UTF-8");
	if (in == NULL) {
		cout << "读入文件失败" << endl;
		return 0;
	}
	int len;
	for (len = 0; fgetws(text, LINE_LENGTH, in); len += wcslen(text)) {
		wcscat(data, text);
	}
	return len;
}

//写utf8文件
int writeUtf8File(wchar_t* data, const wchar_t* path) {
	FILE* out = _wfopen(path, L"w, ccs=UTF-8");
	int len = wcslen(data);
	fputws(data, out);
	fclose(out);
	return len;
}

int main() {
	cout << setlocale(LC_ALL, "") << endl;
	setlocale(LC_ALL, "C");
	setlocale(LC_ALL, ".936");
	//setlocale(LC_ALL, "chs_chn.65001");
	int nativeLength = 0;
	char native_data[2 * FILE_SIZE] = "你我";
	wchar_t native2unicode_data[FILE_SIZE];
	//读取本地编码文件
	nativeLength = readFile(native_data, native_path);
	if (nativeLength > 0) {
		cout << nativeLength << endl;
		printf("%s", native_data);
		//将本地编码数据转换成Unicode数据
		mbstowcs(native2unicode_data, native_data, strlen(native_data));
		//分别写入Unicode文件和utf8文件
		cout << endl << writeFile(native_data, native2native_path) << endl;
		cout << writeUnicodeFile(native2unicode_data, native2unicode_path)
				<< endl;
		cout << writeUtf8File(native2unicode_data, native2utf8_path) << endl;
		cout << "1******************\n";
	}

	int unicodeLength = 0;
	wchar_t unicode_data[FILE_SIZE] = L"你我他";
	char unicode2native_data[2 * FILE_SIZE];
	//读取Unicode文件
	unicodeLength = readUnicodeFile(unicode_data, unicode_path);
	if (unicodeLength > 0) {
		cout << unicodeLength << endl;
		wprintf(L"%ls", unicode_data);
		//将Unicode数据转换成本地编码文件
		wcstombs(unicode2native_data, unicode_data, 2 * wcslen(unicode_data));
		//分别将数据写入本地编码文件和Utf8文件
		cout << endl << writeUnicodeFile(unicode_data, unicode2unicode_path)
				<< endl;
		cout << writeFile(unicode2native_data, unicode2native_path) << endl;
		cout << writeUtf8File(unicode_data, unicode2utf8_path) << endl;
		cout << "2******************\n";
	}

	int utf8Length = 0;
	wchar_t utf8_data[FILE_SIZE] = L"你我";
	char utf82native_data[2 * FILE_SIZE];
	//读取Utf8文件
	utf8Length = readUtf8File(utf8_data, utf8_path);
	if (utf8Length > 0) {
		cout << utf8Length << endl;
		wprintf(L"%ls", utf8_data);
		//将Unicode数据转换成本地编码文件
		wcstombs(utf82native_data, utf8_data, 2 * wcslen(utf8_data));
		//分别将数据写入本地编码文件和unicode文件
		cout << endl << writeUtf8File(utf8_data, utf82utf8_path) << endl;
		cout << writeFile(utf82native_data, utf82native_path) << endl;
		cout << writeUnicodeFile(utf8_data, utf82unicode_path) << endl;
		cout << "3******************\n";
	}
	return 0;
}
