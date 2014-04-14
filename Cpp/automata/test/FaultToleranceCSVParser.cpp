#include <iostream>
#include <cassert>
#include "BooleanMatrix.h"

using namespace std;
using namespace CT;

// Fault-Tolerance CSV Parser

// Description of Automata for Fault-Tolerance CSV Parser
/* States: (S)tart, (I)nQuote, (O)utQuote, (T)emp, (E)rror
** Transitions
**		Seprator	Quote	Other
** S	S			I		O
** I	I			T		I
** O	S			O		O
** T	S			I		E
** E	S			E		E
*/


// MAAT Description
// Check paper "Automata, Boolean Matrices, and Ultimate Periodicity"
const bool M[4][5 * 5] =
{
	// for identity matrix
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	}
	,// for separator
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0
	}
	,// for quote char
	{
		0, 1, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 1
	}
	,// for other charaters
	{
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 0, 1
	}
};

const bool S[6][1 * 5] = 
{
	// start
	{
		1, 0, 0, 0, 0
	}
	,// qutoed
	{
		0, 1, 0, 0, 0
	}
	,// unquoted
	{
		0, 0, 1, 0, 0
	}
	,// temp
	{
		0, 0, 0, 1, 0
	}
	,// error
	{
		0, 0, 0, 0, 1
	}
	,// any
	{
		1, 1, 1, 1, 1
	}
};

const BooleanMatrix gmIdentity(5, 5, M[0]);
const BooleanMatrix gmSeparator(5, 5, M[1]);
const BooleanMatrix gmQuote(5, 5, M[2]);
const BooleanMatrix gmOther(5, 5, M[3]);

const BooleanMatrix gmStart(5, 1, S[0]);
const BooleanMatrix gmQutoed(5, 1, S[1]);
const BooleanMatrix gmUnQutoed(5, 1, S[2]);
const BooleanMatrix gmTemp(5, 1, S[3]);
const BooleanMatrix gmError(5, 1, S[4]);
const BooleanMatrix gmAny(5, 1, S[5]);

// DFA
BooleanMatrix ScanCSV(const char* ipCSV, const BooleanMatrix& iStartState = gmStart)
{
	BooleanMatrix lmResult(iStartState.Transport());
	for(const char* lpCurrent = ipCSV; *lpCurrent != '\0'; lpCurrent++)
	{
		switch(*lpCurrent)
		{
		case ',':
			lmResult = lmResult * gmSeparator;
			break;
		case '|':
			lmResult = lmResult * gmQuote;
			break;
		default:
			lmResult = lmResult * gmOther;
			break;
		}
	}
	return lmResult;
}

// NFA
BooleanMatrix BackScanCSV(const char* ipCSV, const BooleanMatrix& iEndState = gmAny)
{
	size_t lLen = strlen(ipCSV);
	BooleanMatrix lmResult(iEndState);
	for(const char* lpCurrent = ipCSV + lLen -1 ; lpCurrent >= ipCSV; lpCurrent--)
	{
		if(lmResult.AllFalse() || lmResult.AllTrue())
		{
			return lmResult;
		}

		switch(*lpCurrent)
		{
		case ',':
			lmResult = gmSeparator * lmResult;
			break;
		case '|':
			lmResult = gmQuote * lmResult;
			break;
		default:
			lmResult = gmOther * lmResult;
			break;
		}
	}
	return lmResult;
}

ostream& operator << (ostream& out, const BooleanMatrix& obj)
{
	out << obj.ToSimpleString();
	return out;
}

int main()
{
	BooleanMatrix lTemp(gmIdentity);

	cout << gmOther * gmQuote * gmOther << endl;
	cout << gmAny.Transport() * gmOther * gmQuote * gmOther << endl;
	cout << gmOther * gmQuote * gmSeparator << endl;
	cout << gmAny.Transport() * gmOther * gmQuote * gmSeparator << endl;

	return 0;

	// scan
	{
		cout << "--- doing basic unit test\n";

		assert(ScanCSV("") == gmStart.Transport());

		assert(ScanCSV(",") == gmStart.Transport());
		assert(ScanCSV("|") == gmQutoed.Transport());
		assert(ScanCSV("A") == gmUnQutoed.Transport());

		assert(ScanCSV("|,") == gmQutoed.Transport());
		assert(ScanCSV("||") == gmTemp.Transport());
		assert(ScanCSV("|A") == gmQutoed.Transport());

		assert(ScanCSV("A,") == gmStart.Transport());
		assert(ScanCSV("A|") == gmUnQutoed.Transport());
		assert(ScanCSV("AA") == gmUnQutoed.Transport());

		assert(ScanCSV("||,") == gmStart.Transport());
		assert(ScanCSV("||A") == gmError.Transport());
		assert(ScanCSV("|||") == gmQutoed.Transport());

		assert(ScanCSV("||A,") == gmStart.Transport());
		assert(ScanCSV("||A|") == gmError.Transport());
		assert(ScanCSV("||AA") == gmError.Transport());

	}

	{
		cout << "--- doing advanced unit test\n";

		assert(ScanCSV("|||,A|") == gmTemp.Transport());
	}

	// scan
	{
		cout << "--- doing scan test\n";

		cout << ScanCSV("A,,") << endl;
		cout << ScanCSV("A,|") << endl;
		cout << ScanCSV("A,A") << endl;

		cout << ScanCSV("A") << endl;
		cout << ScanCSV("A,") << endl;
		cout << ScanCSV("A,B") << endl;
		cout << ScanCSV("A,B|") << endl;
		cout << ScanCSV("A,|") << endl;
		cout << ScanCSV("A,|,")<< endl;
		cout << ScanCSV("A,|B|||,C,") << endl;
	}

	// back scan, use | as quote char
	{
		cout << "\n--- back scan, the last separator in the following cases are quoted\n";
		cout << BackScanCSV("C,B,|A,", gmStart).Transport() << endl;
		cout << BackScanCSV("C,|B,||,", gmStart).Transport() << endl;
		cout << BackScanCSV("C,|B,||,", gmStart).Transport() << endl;

		cout << "\n--- back scan, the last separator in the following cases are unquoted\n";
		cout << BackScanCSV("B,|A|,", gmQutoed).Transport() << endl;
		cout << BackScanCSV("C,|B|,A,", gmQutoed).Transport() << endl;
		cout << BackScanCSV("B,|A|,", gmQutoed).Transport() << endl;

		cout << "\n--- back scan, the last separator in the following cases are quoted if reach the start\n";
		lTemp = BackScanCSV("A,|,", gmStart);
		cout << lTemp.Transport() << (gmStart & lTemp).Transport() << endl;
		lTemp = BackScanCSV("B,|,A,", gmStart);
		cout << lTemp.Transport() << (gmStart & lTemp).Transport() << endl;

		cout << "\n--- back scan, the last separator in the following cases are unquoted if reach the start\n";
		lTemp = BackScanCSV("A,", gmQutoed);
		cout << lTemp.Transport() << (gmStart & lTemp).Transport() << endl;
		lTemp = BackScanCSV("C,B,||,", gmQutoed);
		cout << lTemp.Transport() << (gmStart & lTemp).Transport() << endl;
		lTemp = BackScanCSV("C,|,B,|,A,", gmQutoed);
		cout << lTemp.Transport() << (gmStart & lTemp).Transport() << endl;

		cout << "\n--- other tests\n";
		cout << BackScanCSV("C,B,|A,", gmStart).Transport() << endl;

		cout << BackScanCSV("Z|,A,||a|,A,", gmStart).Transport() << endl;
	}

	return 0;
}