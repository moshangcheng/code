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
	return 0;
}