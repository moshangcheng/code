#include <iostream>
#include <string>
#include <unicode/ucal.h>
#include <unicode/ucnv.h>
#include <unicode/udat.h>
#include <unicode/fieldpos.h>
#include <unicode/datefmt.h>
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

bool getStrftimeFormatFromICU(DateFormat* format, UnicodeString& posixPattern)
{
	posixPattern.remove();
	SimpleDateFormat* simpleFormat = dynamic_cast<SimpleDateFormat*>(format);
	if (!simpleFormat) {
		return false;
	}

	// convert ICU-type pattern to posix (i.e. strftime()) format string
	UnicodeString icuPattern;
	simpleFormat->toPattern(icuPattern);
	if (icuPattern.length() > 0) {
		UChar lastCharSeen = 0;
		int lastCharCount = 1;
		bool inSingleQuotes = false;
		bool inDoubleQuotes = false;
		// we loop one character past the end on purpose, which will result in a
		// final -1 char to be processed, which in turn will let us handle the
		// last character (via lastCharSeen)
		for (int i = 0; i <= icuPattern.length(); ++i) {
			UChar currChar = icuPattern.charAt(i);
			if (lastCharSeen != 0 && currChar == lastCharSeen) {
				lastCharCount++;
				continue;
			}

			if (!inSingleQuotes && !inDoubleQuotes) {
				switch (lastCharSeen) {
					case L'a':
						posixPattern.append(UnicodeString("%p", ""));
						break;
					case L'd':
						if (lastCharCount == 2)
							posixPattern.append(UnicodeString("%d", ""));
						else
							posixPattern.append(UnicodeString("%e", ""));
						break;
					case L'D':
						posixPattern.append(UnicodeString("%j", ""));
						break;
					case L'c':
						// fall through, to handle 'c' the same as 'e'
					case L'e':
						if (lastCharCount == 4)
							posixPattern.append(UnicodeString("%A", ""));
						else if (lastCharCount <= 2)
							posixPattern.append(UnicodeString("%u", ""));
						else
							posixPattern.append(UnicodeString("%a", ""));
						break;
					case L'E':
						if (lastCharCount == 4)
							posixPattern.append(UnicodeString("%A", ""));
						else
							posixPattern.append(UnicodeString("%a", ""));
						break;
					case L'k':
						// fall through, to handle 'k' the same as 'h'
					case L'h':
						if (lastCharCount == 2)
							posixPattern.append(UnicodeString("%I", ""));
						else
							posixPattern.append(UnicodeString("%l", ""));
						break;
					case L'H':
						if (lastCharCount == 2)
							posixPattern.append(UnicodeString("%H", ""));
						else
							posixPattern.append(UnicodeString("%k", ""));
						break;
					case L'm':
						posixPattern.append(UnicodeString("%M", ""));
						break;
					case L'L':
						// fall through, to handle 'L' the same as 'M'
					case L'M':
						if (lastCharCount == 4)
							posixPattern.append(UnicodeString("%B", ""));
						else if (lastCharCount == 3)
							posixPattern.append(UnicodeString("%b", ""));
						else
							posixPattern.append(UnicodeString("%m", ""));
						break;
					case L's':
						posixPattern.append(UnicodeString("%S", ""));
						break;
					case L'w':
						posixPattern.append(UnicodeString("%V", ""));
						break;
					case L'y':
						if (lastCharCount == 2)
							posixPattern.append(UnicodeString("%y", ""));
						else
							posixPattern.append(UnicodeString("%Y", ""));
						break;
					case L'Y':
						posixPattern.append(UnicodeString("%G", ""));
						break;
					case L'z':
						posixPattern.append(UnicodeString("%Z", ""));
						break;
					case L'Z':
						posixPattern.append(UnicodeString("%z", ""));
						break;
					default:
						if (lastCharSeen != 0)
							posixPattern.append(lastCharSeen);
				}
			} else {
				if (lastCharSeen != 0)
					posixPattern.append(lastCharSeen);
			}

			if (currChar == L'"') {
				inDoubleQuotes = !inDoubleQuotes;
				lastCharSeen = 0;
			} else if (currChar == L'\'') {
				inSingleQuotes = !inSingleQuotes;
				lastCharSeen = 0;
			} else
				lastCharSeen = currChar;

			lastCharCount = 1;
		}
	}
	return true;
}

void ConvertTest()
{
	UErrorCode err = U_ZERO_ERROR;
	UConverter* utf8_conv = create_conv("UNICODE");
	UConverter* eascii_conv = create_conv("ISO-8859-1");

	const char* orig = "הצü";
	char result[100];

	const char* source = orig;
	char* dest = result;

	memset(result, 0, sizeof(result));
	ucnv_convertEx(utf8_conv, eascii_conv, &dest, dest+99, &source, source+3, g_.pivot_buf_, &g_.pivot_source_, &g_.pivot_target_, g_.pivot_buf_ + sizeof g_.pivot_buf_, 0, 1, &err);
	for(int i = 0; i < 100; i++) {
		cout << (int)result[i] << " ";
	}
	cout << endl;

	memset(result, 0, sizeof(result));
	cout << ucnv_convert("UTF-8", "ISO-8859-1", result, 99, orig, 3, &err) << endl;
	for(int i = 0; i < 100; i++) {
		cout << (int)result[i] << " ";
	}
	cout << endl;

	//delete [] pDestStr;
}

void FormatTest() {

	cout << UCAL_SUNDAY << endl;

	//get locale
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

	UErrorCode status = U_ZERO_ERROR;

	//create DateFormat and date
	DateFormat* df = DateFormat::createDateInstance(DateFormat::FULL, Locale::getGerman());
	UDate lDate = Calendar::getNow();

	UnicodeString myString;
	FieldPosition pos(DateFormat::DAY_OF_WEEK_FIELD);
	//format date
	df->format( lDate, myString, pos, status);
	//get full formatted string
	cout << string(myString.getBuffer(), myString.getBuffer() + myString.length()) << endl;
	//get specified filed of formatted string
	cout << string(myString.getBuffer() + pos.getBeginIndex(), myString.getBuffer() + pos.getEndIndex()) << endl;

	//convert to SimpleDateFormat
	SimpleDateFormat* lpSimpleDateFormat = dynamic_cast<SimpleDateFormat*>(df);
	if(!lpSimpleDateFormat) {
		//todo
	}

	//Get Posix Format String
	UnicodeString lPosixDateTimeFormatString;
	getStrftimeFormatFromICU(df, lPosixDateTimeFormatString);
	cout << string(lPosixDateTimeFormatString.getBuffer(), lPosixDateTimeFormatString.getBuffer() + lPosixDateTimeFormatString.length()) << endl;

	//Get Datetime Format String
	UnicodeString lDateTimeFormatString;
	lpSimpleDateFormat->toPattern(lDateTimeFormatString);
	cout << string(lDateTimeFormatString.getBuffer(), lDateTimeFormatString.getBuffer() + lDateTimeFormatString.length()) << endl;

	//Get Format Symbols
	const DateFormatSymbols* lpDateFormatSymbos = lpSimpleDateFormat->getDateFormatSymbols();

	//Get names of day of week
	int32_t lDayOfWeekCount = 1;
	const UnicodeString* lcpSymbolName = lpDateFormatSymbos->getQuarters(lDayOfWeekCount, DateFormatSymbols::STANDALONE, DateFormatSymbols::WIDE);
	cout << string(lcpSymbolName->getBuffer(), lcpSymbolName->getBuffer() + lcpSymbolName->length()) << endl;
	delete df;

	Calendar* lpCalander = Calendar::createInstance(Locale::getFrance(), status);
	delete lpCalander;

	int len = 12;
	UChar result[100];
	UDateFormat* lpUDateFormat = udat_open(UDAT_FULL, UDAT_FULL, Locale::getUS().getName(), NULL, -1, NULL, -1, &status);
	udat_getSymbols(lpUDateFormat, UDAT_SHORT_WEEKDAYS, 1, result, 99, &status);
	delete lpUDateFormat;
}
 
 
 
 

int main() {
	//ConvertTest();
	FormatTest();
	return 0;
}

