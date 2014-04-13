#include <iostream>
#include "BooleanMatrix.h"

using namespace std;
using namespace CT;

// Description of Automata for CSV Parser
/* States: (S)tart, (I)nQuote, (O)utQuote, (T)emp, (E)rror
** Transitions
**		Seprator	Quote	Other
** S	S			I		O
** I	I			T		I
** O	S			O		O
** T	S			I		E
** E	E			E		E
*/


// MAAT Description
// Check paper "Automata, Boolean Matrices, and Ultimate Periodicity"
const bool M[4][5 * 5] =
{
	// for identity matrix
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	}
	,// for separator
	{
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 1
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

const bool S[5][1 * 5] = 
{
	// start state
	{
		1, 0, 0, 0, 0
	}
	,// any
	{
		1, 1, 1, 1, 1
	}
	,// qutoed
	{
		0, 1, 0, 0, 0
	}
	,// error
	{
		0, 0, 0, 0, 1
	}
	,// new filed found
	{
		1, 0, 0, 0, 0
	}
};

const BooleanMatrix gmIdentity(5, 5, M[0]);
const BooleanMatrix gmSeparator(5, 5, M[1]);
const BooleanMatrix gmQuote(5, 5, M[2]);
const BooleanMatrix gmOther(5, 5, M[3]);

const BooleanMatrix gmStart(1, 5, S[0]);
const BooleanMatrix gmAny(5, 1, S[1]);
const BooleanMatrix gmQutoed(5, 1, S[2]);
const BooleanMatrix gmError(5, 1, S[3]);
const BooleanMatrix gmNewField(5, 1, S[4]);

// DFA
BooleanMatrix ScanCSV(const char* ipCSV)
{
	BooleanMatrix lmResult(gmStart);
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
BooleanMatrix BackScanCSV(const char* ipCSV, const BooleanMatrix& irRequriedState)
{
	size_t lLen = strlen(ipCSV);
	BooleanMatrix lmResult(irRequriedState);
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

int main()
{
	// scan
	{
		cout << "--- scan\n";
		cout << ScanCSV("").ToString() << endl;
		cout << ScanCSV("A").ToString() << endl;
		cout << ScanCSV("A,").ToString() << endl;
		cout << ScanCSV("A,B").ToString() << endl;
		cout << ScanCSV("A,B|").ToString() << endl;
		cout << ScanCSV("A,|").ToString() << endl;
		cout << ScanCSV("A,|,").ToString() << endl;
		cout << ScanCSV("A,|B|||,C,").ToString() << endl;
	}

	// back scan, use | as quote char
	{
		cout << "\n\n--- back scan, the last char in the following cases are quoted\n";
		cout << BackScanCSV("A,|,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("C,B,|A,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("C,|B,||,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("C,|B,||,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;

		cout << "\n\n--- back scan, the last char in the following cases are note quoted\n";
		cout << BackScanCSV("A,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("C,B,||,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("C,|,B,|,A,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("B,|A|,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("C,|B|,A,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
		cout << BackScanCSV("B,|A|,", BooleanMatrix(5, 1, S[2])).Transport().ToString() << endl;
	}

	return 0;
}