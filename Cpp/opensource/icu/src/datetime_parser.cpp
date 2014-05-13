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

void ParseTest() {

	// cout << UCAL_SUNDAY << endl;
	UErrorCode status = U_ZERO_ERROR;

	//get locale
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

	// get timezone
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


	// try to generate "Fri Jan 01 00:00:00 EST 2010"
	{
		wcout << L"-- generate datetime like \"Fri Jan 01 00:00:00 EST 2010\"\n";

		UnicodeString targetPatten("EEE MMMM dd HH:mm:ss z yyyy");
		SimpleDateFormat* lpSimpleDateFormat = new SimpleDateFormat(targetPatten, Locale::getUS(), status);

		lpSimpleDateFormat->setTimeZone(*TimeZone::createTimeZone(UnicodeString("EST")));

		UnicodeString myString;

		lpSimpleDateFormat->format(Calendar::getNow(), myString, status);

		//get full formatted string
		wcout << wstring(myString.getBuffer(), myString.getBuffer() + myString.length()) << endl << endl;
	}

	// try to pase "Fri Jan 01 00:00:00 EST 2010"
	{
		wcout << L"-- parse datetime like \"Fri Jan 01 00:00:00 EST 2010\"\n";

		UnicodeString srcPatten("EEE MMMM dd HH:mm:ss z yyyy");
		SimpleDateFormat* lpSimpleDateFormat = new SimpleDateFormat(srcPatten, Locale::getUS(), status);

		UnicodeString srcString("Fri Jan 01 00:00:00 EST 2010");

		UDate lDate = lpSimpleDateFormat->parse(srcString, status);

		if(U_FAILURE(status)) {
			wcout << L"parse date time failed\n";
		}

		//create DateFormat and date
		DateFormat* df = DateFormat::createDateTimeInstance(DateFormat::LONG, DateFormat::LONG);

		UnicodeString targetString;
		df->format( lDate, targetString, status);
		//get full formatted string
		wcout << wstring(targetString.getBuffer(), targetString.getBuffer() + targetString.length()) << endl << endl;
		delete df;
	}

	{
		//create DateFormat and date
		DateFormat* df = DateFormat::createDateTimeInstance(DateFormat::LONG, DateFormat::LONG);//, Locale::getGerman());
		UDate lDate = Calendar::getNow();


		UnicodeString myString;
		FieldPosition pos(DateFormat::DAY_OF_WEEK_FIELD);
		//format date
		df->format( lDate, myString, pos, status);
		//get full formatted string
		wcout << wstring(myString.getBuffer(), myString.getBuffer() + myString.length()) << endl;
		//get specified filed of formatted string
		wcout << wstring(myString.getBuffer() + pos.getBeginIndex(), myString.getBuffer() + pos.getEndIndex()) << endl;

		//convert to SimpleDateFormat
		SimpleDateFormat* lpSimpleDateFormat = dynamic_cast<SimpleDateFormat*>(df);
		if(!lpSimpleDateFormat) {
			//todo
		}

		//Get Datetime Format String
		UnicodeString lDateTimeFormatString;
		lpSimpleDateFormat->toPattern(lDateTimeFormatString);
		wcout << wstring(lDateTimeFormatString.getBuffer(), lDateTimeFormatString.getBuffer() + lDateTimeFormatString.length()) << endl;

		//Get Format Symbols
		const DateFormatSymbols* lpDateFormatSymbos = lpSimpleDateFormat->getDateFormatSymbols();

		//Get names of day of week
		int32_t lDayOfWeekCount = 1;
		const UnicodeString* lcpSymbolName = lpDateFormatSymbos->getQuarters(lDayOfWeekCount, DateFormatSymbols::STANDALONE, DateFormatSymbols::WIDE);
		wcout << wstring(lcpSymbolName->getBuffer(), lcpSymbolName->getBuffer() + lcpSymbolName->length()) << endl;
		delete df;
	}

	{
		Calendar* lpCalander = Calendar::createInstance(Locale::getFrance(), status);
		delete lpCalander;
	}


	{
		UChar result[100];
		UDateFormat* lpUDateFormat = udat_open(UDAT_FULL, UDAT_FULL, Locale::getUS().getName(), NULL, -1, NULL, -1, &status);
		int len = udat_getSymbols(lpUDateFormat, UDAT_SHORT_WEEKDAYS, 1, result, 99, &status);
		for(int i = 0; i < len; i++) {
			wcout << result[i];
		}
		wcout << endl;
	}
}

int main() {
	ParseTest();
	return 0;
}

