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

void CreateLocale()
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


void CreateTimeZone()
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
		// wcout << L"-- parse datetime: " << wstring(srcString.getBuffer(), srcString.getBuffer() + srcString.length()) << endl;
		// wcout << L"   use format string: " << wstring(fmt.getBuffer(), fmt.getBuffer() + fmt.length()) << endl;

		SimpleDateFormat* lpSrcDateFormat = new SimpleDateFormat(fmt, locale, status);
		UDate lDate = lpSrcDateFormat->parse(srcString, status);

		if(U_FAILURE(status)) {
			wcout << L"parse date time failed\n";
		}

		UnicodeString targetString;
		DateFormat* lpTargetDateFormat = DateFormat::createDateTimeInstance(DateFormat::FULL, DateFormat::FULL, Locale::getUS());
		lpTargetDateFormat->format( lDate, targetString, status);
		
		delete lpSrcDateFormat;
		delete lpTargetDateFormat;
		return targetString;
	}
}

UnicodeString ParseDate(const UnicodeString& srcString = UnicodeString("2000-01-01")
							 , const Locale& locale = Locale::getUS()
							 , const UnicodeString& fmt = UnicodeString("yyyy-mm-dd"))
{
	UErrorCode status = U_ZERO_ERROR;
	// try to pase "Fri Jan 01 00:00:00 EST 2010"
	{
		// wcout << L"-- parse datetime: " << wstring(srcString.getBuffer(), srcString.getBuffer() + srcString.length()) << endl;
		// wcout << L"   use format string: " << wstring(fmt.getBuffer(), fmt.getBuffer() + fmt.length()) << endl;

		SimpleDateFormat* lpSrcDateFormat = new SimpleDateFormat(fmt, locale, status);
		lpSrcDateFormat->setTimeZone(*TimeZone::createTimeZone(UnicodeString("EST")));
		UDate lDate = lpSrcDateFormat->parse(srcString, status);

		if(U_FAILURE(status)) {
			wcout << L"parse date failed\n";
		}

		UnicodeString targetString;
		DateFormat* lpTargetDateFormat = DateFormat::createDateInstance(DateFormat::FULL, Locale::getUS());
		lpTargetDateFormat->format( lDate, targetString, status);
		
		delete lpSrcDateFormat;
		delete lpTargetDateFormat;
		return targetString;
	}
}

UnicodeString ParseTime(const UnicodeString& srcString = UnicodeString("00:00:00")
							 , const Locale& locale = Locale::getUS()
							 , const UnicodeString& fmt = UnicodeString("HH:mm:ss"))
{
	UErrorCode status = U_ZERO_ERROR;
	// try to pase "Fri Jan 01 00:00:00 EST 2010"
	{
		// wcout << L"-- parse datetime: " << wstring(srcString.getBuffer(), srcString.getBuffer() + srcString.length()) << endl;
		// wcout << L"   use format string: " << wstring(fmt.getBuffer(), fmt.getBuffer() + fmt.length()) << endl;

		SimpleDateFormat* lpSrcDateFormat = new SimpleDateFormat(fmt, locale, status);
		lpSrcDateFormat->setTimeZone(*TimeZone::createTimeZone(UnicodeString("EST")));
		UDate lDate = lpSrcDateFormat->parse(srcString, status);

		if(U_FAILURE(status)) {
			wcout << L"parse date failed\n";
		}

		UnicodeString targetString;
		DateFormat* lpTargetDateFormat = DateFormat::createTimeInstance(DateFormat::FULL, Locale::getUS());
		lpTargetDateFormat->format( lDate, targetString, status);
		
		delete lpSrcDateFormat;
		delete lpTargetDateFormat;
		return targetString;
	}
}

int main() {

	UnicodeString lResult;

	// test support for datetime format string of each locale
	{
		UnicodeString lFmtStrings[] = {
			UnicodeString("EEE MMM dd HH:mm:ss z yyyy")
			, UnicodeString("EEE MMM dd HH:mm:ss 'in' z 'at' yyyy")
		};

		Locale lLocales[] = {
			Locale::getUS()
			, Locale::getGerman()
			, Locale::getFrance()
			, Locale::getChina()
			, Locale::getJapan()
			, Locale::getKorea()
			, Locale::getCanadaFrench()
		};

		int lFmtStringCount = sizeof(lFmtStrings) / sizeof(UnicodeString);
		int lLocaleCount = sizeof(lLocales) / sizeof(Locale);

		for(int i = 0; i < lFmtStringCount; i++)
		{
			for(int j = 0; j < lLocaleCount; j++)
			{
				lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), lLocales[j], lFmtStrings[i]), lLocales[j], lFmtStrings[i]);
				wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;
			}
		}

	}

	// test support for date format string of each locale
	{
		UnicodeString lFmtStrings[] = {
			UnicodeString("yyyy-MM-dd")
			, UnicodeString("yyyyMMdd")
			, UnicodeString("yyyy/MM/dd")
			, UnicodeString("yyyyMMdd")
			, UnicodeString("yyyy|MM|dd")
			, UnicodeString("yyyy '*' MM '*' dd")
		};

		Locale lLocales[] = {
			Locale::getUS()
			, Locale::getGerman()
			, Locale::getFrance()
			, Locale::getChina()
			, Locale::getJapan()
			, Locale::getKorea()
			, Locale::getCanadaFrench()
		};

		int lFmtStringCount = sizeof(lFmtStrings) / sizeof(UnicodeString);
		int lLocaleCount = sizeof(lLocales) / sizeof(Locale);

		for(int i = 0; i < lFmtStringCount; i++)
		{
			for(int j = 0; j < lLocaleCount; j++)
			{
				lResult = ParseDate(FormatDatetime(Calendar::getNow(), lLocales[j], lFmtStrings[i]), lLocales[j], lFmtStrings[i]);
				wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;
			}
		}

	}

	// test support for time format string of each locale
	{
		UnicodeString lFmtStrings[] = {
			UnicodeString("HH:mm:ss")
			, UnicodeString("HH-mm-ss")
			, UnicodeString("HH/mm/ss")
			, UnicodeString("HH|mm|ss")
			, UnicodeString("HH 'x' mm 'x' ss")
		};

		Locale lLocales[] = {
			Locale::getUS()
			, Locale::getGerman()
			, Locale::getFrance()
			, Locale::getChina()
			, Locale::getJapan()
			, Locale::getKorea()
			, Locale::getCanadaFrench()
		};

		int lFmtStringCount = sizeof(lFmtStrings) / sizeof(UnicodeString);
		int lLocaleCount = sizeof(lLocales) / sizeof(Locale);

		for(int i = 0; i < lFmtStringCount; i++)
		{
			for(int j = 0; j < lLocaleCount; j++)
			{
				lResult = ParseTime(FormatDatetime(Calendar::getNow(), lLocales[j], lFmtStrings[i]), lLocales[j], lFmtStrings[i]);
				wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;
			}
		}

	}

	// test fault-tolerence of icu format string
	{
		UnicodeString lIncorrectFmtStrings[] = {
			UnicodeString("EEE  MMM dd  HH:mm:ss  z   yyyy") // dummy white space, compatitible
			, UnicodeString("EEE MMM dd '3' HH:mm:ss z yyyy") // dummy number 3, not compatible
		};

		UnicodeString lFmtStrings[] = {
			UnicodeString("EEE MMM dd HH:mm:ss z yyyy")
			, UnicodeString("EEE MMM dd HH:mm:ss z yyyy")
		};

		Locale lLocales[] = {
			Locale::getUS()
			, Locale::getGerman()
			, Locale::getFrance()
			, Locale::getChina()
			, Locale::getJapan()
			, Locale::getKorea()
			, Locale::getCanadaFrench()
		};

		int lFmtStringCount = sizeof(lFmtStrings) / sizeof(UnicodeString);
		int lLocaleCount = sizeof(lLocales) / sizeof(Locale);

		for(int i = 0; i < lFmtStringCount; i++)
		{
			for(int j = 0; j < lLocaleCount; j++)
			{
				lResult = ParseDatetime(FormatDatetime(Calendar::getNow(), lLocales[j], lIncorrectFmtStrings[i]), lLocales[j], lFmtStrings[i]);
				wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;
			}
		}

	}

	return 0;
}

