#include <iostream>
#include <cassert>
using namespace  std;

// DFA description

/* start state is 1011, which is coded as state 4
** accept state is 1111, which is coded as state 5
** error state is 0000,  which is coded as state 0

		Seprator	Quote	Other
0000	0000		0000	0000
0100	0100		1001	0100
0110	0100		1011	1111
1001	1011		0100	0000
1011	1011		0110	1011
1111	1111		1111	1111
*/

int Transitions[6][3] =
{
	// state 0000
	{0, 0, 0}
	, // state 0100
	{1, 3, 1}
	, // state 0110
	{1, 4, 5}
	, // state 1001
	{4, 1, 0}
	, // state 1011
	{4, 2, 4}
	, // state 1111
	{5, 5, 5}
};

struct State
{
	int state;
	bool sameField;
};

// @return, the state of DFA
// @orSameField, this value indicates whether it's possbile that
// the entire processed string is in one filed. This is very
// useful when the return state is not 0 or 5.
State BackScanCSV(const char* ipCSV, size_t iLen = 0)
{
	State s = {4, true};
	if(iLen == 0)
	{
		iLen = strlen(ipCSV);
	}
	for(const char* lpCurrent = ipCSV + iLen -1 ; lpCurrent >= ipCSV; lpCurrent--)
	{
		switch(s.state)
		{
		case 0:
		case 5:
			return s;
			break;
		case 1:
		case 3:
			s.sameField = false;
			break;
		default:
			break;
		}

		switch(*lpCurrent)
		{
		case ',':
			s.state = Transitions[s.state][0];
			break;
		case '|':
			s.state = Transitions[s.state][1];
			break;
		default:
			s.state = Transitions[s.state][2];
			break;
		}
	}
	return s;
}


int main()
{
	// use | as quote char
	// CSV char should end with char ,
	// check whether the last separatr is valid

	bool lSameField = true;

	{
		// CSV strictly follow RFC4180, no partially quoted filed

		// valid separtors
		assert(BackScanCSV("A|A,").state == 5);
		assert(BackScanCSV("A|||A,").state == 5);
		assert(BackScanCSV("A|||||A,").state == 5);
		assert(BackScanCSV("A|||||||A,").state == 5);
		assert(BackScanCSV("A|||||||||A,").state == 5);
		assert(BackScanCSV("A|||||||||,").state == 5);
		assert(BackScanCSV("A|||||||,").state == 5);
		assert(BackScanCSV("A|||||,").state == 5);
		assert(BackScanCSV("A|||,").state == 5);
		assert(BackScanCSV("A|,").state == 5);

		// valid separtors
		assert(BackScanCSV("A|,|,A,|,").state == 5);
		assert(BackScanCSV("A|,|,A,|,A,|,A,|,").state == 5);

		// quoted separators
		assert(BackScanCSV("A|A,|,").state == 0);
		assert(BackScanCSV("A|||A,|,").state == 0);
		assert(BackScanCSV("A|||||A,|,").state == 0);
		assert(BackScanCSV("A|||||||A,|,").state == 0);
		assert(BackScanCSV("A|||||||||A,|,").state == 0);
		assert(BackScanCSV("A|||||||||,|,").state == 0);
		assert(BackScanCSV("A|||||||,|,").state == 0);
		assert(BackScanCSV("A|||||,|,").state == 0);
		assert(BackScanCSV("A|||,|,").state == 0);
		assert(BackScanCSV("A|,|,").state == 0);

		// quoted separators
		assert(BackScanCSV("A|A,|,A,|,A,|,").state == 0);
	}

	{
		// CSVs don't strictly follow RFC4180,  have partially quoted fileds

		// valid separtors
		assert(BackScanCSV("A|A,|A|A,").state == 5);
		assert(BackScanCSV("A|||A,|A|A,").state == 5);
		assert(BackScanCSV("A|||||A,|A|A,").state == 5);
		assert(BackScanCSV("A|||||||A,|A|A,").state == 5);
		assert(BackScanCSV("A|||||||||A,|A|A,").state == 5);
		assert(BackScanCSV("A|||||||||,|A|A,").state == 5);
		assert(BackScanCSV("A|||||||,|A|A,").state == 5);
		assert(BackScanCSV("A|||||,|A|A,").state == 5);
		assert(BackScanCSV("A|||,|A|A,").state == 5);
		assert(BackScanCSV("A|,|A|A,").state == 5);

		// valid separtors
		assert(BackScanCSV("A|,|A|A,|,A,|,").state == 5);
		assert(BackScanCSV("A|,|,A,|,|A|A,A,|,A,|,").state == 5);

		// quoted separators
		assert(BackScanCSV("A|A,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||A,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||||A,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||||||A,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||||||||A,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||||||||,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||||||,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||||,|A|A,|,").state == 0);
		assert(BackScanCSV("A|||,|A|A,|,").state == 0);
		assert(BackScanCSV("A|,|A|A,|,").state == 0);

		// quoted separators
		assert(BackScanCSV("A|A,|,A,|,|A|A,A,|,").state == 0);
	}

	{
		// sperators whose status cannot be determined
		assert(BackScanCSV("A,A,A,").state == 4 && BackScanCSV("A,A,A,").sameField);
		assert(BackScanCSV("A,|,").state == 1 && !BackScanCSV("A,|,").sameField);
		assert(BackScanCSV("A,|,A,|,").state == 4 && !BackScanCSV("A,|,A,|,").sameField);
		assert(BackScanCSV("A,|,A,|,A,|,").state == 1 && !BackScanCSV("A,|,A,|,A,|,").sameField);
		assert(BackScanCSV("A,|,A,|,A,|,A,|,").state == 4 && !BackScanCSV("A,|,A,|,A,|,A,|,").sameField);
	}

	return 0;
}