#include <iostream>
#include <string>
#include <unicode/ucal.h>
#include <unicode/ucnv.h>
#include <unicode/udat.h>
#include <unicode/fieldpos.h>
#include <unicode/datefmt.h>
#include <unicode/timezone.h>
#include <unicode/smpdtfmt.h>
#include <unicode/dtfmtsym.h>
using namespace std;

int main()
{
	// get LCID
	{
		wcout << Locale::getChina().getLCID() << endl;
		wcout << Locale::getUS().getLCID() << endl;
	}

	// create locale from LCID
	{
		Locale lLoc("en_US");
		wcout << lLoc.getCountry() << endl;
		wcout << lLoc.getLanguage() << endl;
		wcout << lLoc.getLCID() << endl;
	}

	{
		wstring s(L"abc");
		wcout << s << L" " << s.length() << L" " << s.size() << L" "  << endl;

		s += L"a\0adef";
		wcout << s << L" " << s.length() << L" " << s.size() << L" " << endl;
	}
	return 0;
}