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

struct buf_type_base {
	UChar pivot_buf_[ 4096 ], *pivot_source_, *pivot_target_;

	buf_type_base() { reset(); }
	void buf_type_base::reset() {
		pivot_source_ = pivot_target_ = pivot_buf_;
	}
};

struct gbuf_type : buf_type_base {
};
gbuf_type g_;

UConverter* create_conv( char const *charset ) {
	UErrorCode err = U_ZERO_ERROR;
	UConverter *const conv = ucnv_open( charset, &err );
	ucnv_setFromUCallBack(
		conv, UCNV_FROM_U_CALLBACK_STOP, NULL, NULL, NULL, &err
		);
	ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_STOP, NULL, NULL, NULL, &err
		);
	return conv;
}

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

UnicodeString formate_datetime(const UDate& date = Calendar::getNow()
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

UnicodeString parse_datetime(const UnicodeString& srcString = UnicodeString("Fri Jan 01 00:00:00 EST 2010")
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
		SimpleDateFormat* lpTargetDateFormat = new SimpleDateFormat(fmt, Locale::getUS(), status);
		lpTargetDateFormat->setTimeZone(*TimeZone::createTimeZone(UnicodeString("EST")));
		lpTargetDateFormat->format( lDate, targetString, status);
		
		delete lpSrcDateFormat;
		delete lpTargetDateFormat;
		return targetString;
	}
}

int main() {
	UnicodeString lResult;

	// test US
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getUS()), Locale::getUS());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	// test German
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getGerman()), Locale::getGerman());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	// test France
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getFrance()), Locale::getFrance());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	// test China
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getChina()), Locale::getChina());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	// test Japan
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getJapan()), Locale::getJapan());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	// test Korea
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getKorea()), Locale::getKorea());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	// test CanadaFrench
	lResult = parse_datetime(formate_datetime(Calendar::getNow(), Locale::getCanadaFrench()), Locale::getCanadaFrench());
	wcout << wstring(lResult.getBuffer(), lResult.getBuffer() + lResult.length()) << endl << endl;

	return 0;
}

