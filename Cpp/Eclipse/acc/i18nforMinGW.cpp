/*
 一共有6个文件读写API
 本地编码对ASCII编码进行了扩展，一般是GB2312，数据的格式为机内码。所以汉字由两个字节表示，
 每个字节都大于128，区位码、国标码、机内码转换见 区位码.cpp
 分别是：ASCII编码文件的读写，读出是ASCII字符串，读入要求是ASCII字符串
 UTF8文件的读写，读出是UNICODE字符串，写入的数据要求是UNICODE字符串
 UNICODE文件的读写，读出是UNICODE字符串，写入的数据要求是UNICODE字符串
 mingw和gcc对unicode、gbk支持不好，建议采用不带bom头的utf编码方式
 参考
 http://codingdao.com/wp/post/cset-loale-cpp-source-build-talk/
 http://codingdao.com/wp/post/c-stdlib-setlocale-usage-note/
 */

/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-4-29 下午01:53:08
 * @brief i18n mingw
 * @details 测试mingw对国际化编码的支持
 */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>//必须
#include <clocale>//必须
using namespace std;

wchar_t native_path[] = L"native.txt";
wchar_t native2utf8_path[] = L"native2utf8.txt";
wchar_t native2unicode_path[] = L"native2unicode.txt";
wchar_t native2native_path[] = L"native2native.txt";

wchar_t utf8_path[] = L"utf8.txt";
wchar_t utf82native_path[] = L"utf82native.txt";
wchar_t utf82unicode_path[] = L"utf82unicode.txt";
wchar_t utf82utf8_path[] = L"utf82utf8.txt";

wchar_t unicode_path[] = L"unicode.txt";
wchar_t unicode2native_path[] = L"unicode2native.txt";
wchar_t unicode2utf8_path[] = L"unicode2utf8.txt";
wchar_t unicode2unicode_path[] = L"unicode2unicode.txt";

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
	setlocale(LC_ALL, "C");
	setlocale(LC_ALL, "chs_chn.936");
	cout << setlocale(LC_ALL, NULL) << endl;
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

	setlocale(LC_ALL, "C");
	setlocale(LC_ALL, "chs_chn.65001");
	cout << setlocale(LC_ALL, NULL) << endl;
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
		cout << "2******************\n";
	}

	return 0;
}

