﻿#include <iostream>
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

void create_locale()
{
	Locale l_en("en");
	Locale l_en_us("en", "US");
	Locale l_china = Locale::getChina();
	Locale l_chinese = Locale::getChinese();
	Locale l_tw = Locale::getTaiwan();
	Locale l_simplified_chinese = Locale::getSimplifiedChinese();
	Locale l_canada = Locale::getCanada();
	Locale l_canada_french = Locale::getCanadaFrench();
	Locale l_french = Locale::getFrench();
	Locale l_france = Locale::getFrance();
}


void get_timezone()
{
	wcout << L"-- get timezone\n";

	UnicodeString result;
	TimeZone* tz = TimeZone::createTimeZone(UnicodeString("EST"));

	tz->getDisplayName(true, TimeZone::SHORT, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::SHORT_COMMONLY_USED, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::SHORT_GENERIC, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::SHORT_GMT, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::LONG, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::LONG_GMT, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::LONG_GENERIC, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	tz->getDisplayName(true, TimeZone::GENERIC_LOCATION, Locale::getUS(), result);
	wcout << wstring(result.getBuffer(), result.getBuffer() + result.length()) << endl;

	wcout << endl;
}

// ref: http://userguide.icu-project.org/formatparse/datetime
UnicodeString FormatDatetime(const UDate& date = Calendar::getNow()
						 , const Locale& locale = Locale::getUS()
						 , const UnicodeString& fmt = UnicodeString("EEE MMM dd HH:mm:ss z yyyy"))
{
	UErrorCode status = U_ZERO_ERROR;
	// try to generate "Fri Jan 01 00:00:00 EST 2010"
	{
		//wcout << L"-- generate datetime like \"Fri Jan 01 00:00:00 EST 2010\"\n";

		SimpleDateFormat* lpSrcDateFormat = new SimpleDateFormat(fmt, locale, status);

		lpSrcDateFormat->setTimeZone(*TimeZone::createTimeZone(UnicodeString("EST")));

		UnicodeString myString;

		lpSrcDateFormat->format(date, myString, status);

		delete lpSrcDateFormat;
		return myString;		
	}
}

UnicodeString ParseDatetime(const UnicodeString& srcString = UnicodeString("Fri Jan 01 00:00:00 EST 2010")
							 , const Locale& locale = Locale::getUS()
							 , const UnicodeString& fmt = UnicodeString("EEE MMM dd HH:mm:ss z yyyy"))
{
	UErrorCode status = U_ZERO_ERROR;
	// try to pase "Fri Jan 01 00:00:00 EST 2010"
	{
		//wcout << L"-- parse datetime " << wstring(srcString.getBuffer(), srcString.getBuffer() + srcString.length()) << endl << endl;

		SimpleDateFormat* lpSrcDateFormat = new SimpleDateFormat(fmt, locale, status);
		UDate lDate = lpSrcDateFormat->parse(srcString, status);

		if(U_FAILURE(status)) {
			wcout << L"parse date time failed\n";
		}

		UnicodeString targetString;
		DateFormat* lpTargetDateFormat = DateFormat::createDateTimeInstance(DateFormat::FULL, DateFormat::FULL, Locale::getUS());
		lpTargetDateFormat->setTimeZone(*TimeZone::createTimeZone(UnicodeString("EST")));
		lpTargetDateFormat->format( lDate, targetString, status);
		
		delete lpSrcDateFormat;
		delete lpTargetDateFormat;
		return targetString;
	}
}

int main() {
	UnicodeString lResult;

	// test simple format string
	{
		// test US
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getUS()), Locale::getUS());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test German
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getGerman()), Locale::getGerman());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test France
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getFrance()), Locale::getFrance());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test China
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getChina()), Locale::getChina());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test Japan
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getJapan()), Locale::getJapan());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test Korea
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getKorea()), Locale::getKorea());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test CanadaFrench
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getCanadaFrench()), Locale::getCanadaFrench());
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;
	}

	// test complicated format string
	{
		// test US
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getUS(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")), Locale::getUS(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test German
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getGerman(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")), Locale::getGerman(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test France
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getFrance(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")), Locale::getFrance(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test China
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getChina(), UnicodeString("EEE MMM dd HH:mm:ss '在' z 'at' yyyy")), Locale::getChina(), UnicodeString("EEE MMM dd HH:mm:ss '在' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test Japan
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getJapan(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")), Locale::getJapan(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test Korea
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getKorea(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")), Locale::getKorea(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

		// test CanadaFrench
		lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), Locale::getCanadaFrench(),UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")), Locale::getCanadaFrench(), UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy"));
		wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;
	}

	return 0;
}

