#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <list>
#include <string>
#include <cassert>
#include "BooleanMatrix.h"

using namespace std;
using namespace CT;

// No-Error CSV Parser
// This example shows that we can do split even if there is no error staate

// Description of Automata for No-Error CSV Parser
/* States: (S)tart, (I)nQuote, (O)utQuote, (T)emp
** Transitions
**		Seprator	Quote	Other
** S	S			I		O
** I	I			T		I
** O	S			O		O
** T	S			I		O
*/


// MAAT Description
// Read the paper "Automata, Boolean Matrices, and Ultimate Periodicity"
const bool M[4][4 * 4] =
{
	// for identity matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	}
	,// for separator
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		1, 0, 0, 0,
		1, 0, 0, 0
	}
	,// for quote char
	{
		0, 1, 0, 0,
		0, 0, 0, 1,
		0, 0, 1, 0,
		0, 1, 0, 0
	}
	,// for other charaters
	{
		0, 0, 1, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 1, 0
	}
};

const bool S[16][1 * 4] = 
{
	{
		0, 0, 0, 0
	}
	,
	{
		0, 0, 0, 1
	}
	,
	{
		0, 0, 1, 0
	},
	{
		0, 0, 1, 1
	},
	{
		0, 1, 0, 0
	},
	{
		0, 1, 0, 1
	},
	{
		0, 1, 1, 0
	},
	{
		0, 1, 1, 1
	},
	{
		1, 0, 0, 0
	}
	,
	{
		1, 0, 0, 1
	}
	,
	{
		1, 0, 1, 0
	},
	{
		1, 0, 1, 1
	},
	{
		1, 1, 0, 0
	},
	{
		1, 1, 0, 1
	},
	{
		1, 1, 1, 0
	},
	{
		1, 1, 1, 1
	}
};

const BooleanMatrix gmIdentity(4, 4, M[0]);
const BooleanMatrix gmSeparator(4, 4, M[1]);
const BooleanMatrix gmQuote(4, 4, M[2]);
const BooleanMatrix gmOther(4, 4, M[3]);


ostream& operator << (ostream& out, const BooleanMatrix& obj)
{
	out << obj.ToSimpleString();
	return out;
}

int main()
{
	// generate DFA
	{
		for(int i = 0; i < 16; i++)
		{
			BooleanMatrix lgmCurrent(1, 4, S[i]);
			cout << lgmCurrent.Value() << "	,{";
			cout << (lgmCurrent * BooleanMatrix(4, 4, M[1])).Value() << ",	";
			cout << (lgmCurrent * BooleanMatrix(4, 4, M[2])).Value() << ",	";
			cout << (lgmCurrent * BooleanMatrix(4, 4, M[3])).Value() << "}\n";
		}
	}

	// generate dot file
	{
		for(int i = 0; i < 16; i++)
		{
			BooleanMatrix lgmCurrent(1, 4, S[i]);
			cout << i << "->" << (lgmCurrent * BooleanMatrix(4, 4, M[1])).Value() << " [ label=\"" << ',' << "\" ]" << endl;
			cout << i << "->" << (lgmCurrent * BooleanMatrix(4, 4, M[2])).Value() << " [ label=\"" << '|' << "\" ]" << endl;
			cout << i << "->" << (lgmCurrent * BooleanMatrix(4, 4, M[3])).Value() << " [ label=\"" << '?' << "\" ]" << endl;
		}
	}

	{
		int Transition[16][3];

		// calculate transition table
		for(int i = 0; i < 16; i++)
		{
			BooleanMatrix lgmCurrent(1, 4, S[i]);
			for(int j = 0; j < 3; j++)
			{
				Transition[i][j] = (lgmCurrent * BooleanMatrix(4, 4, M[j+1])).Value();
			}
		}
	}

	return 0;
}