/********************************************************************
@created:	2011/05/05 17:16
@author:	moshangcheng
@version:	1.0
@tag:		GCJ2011
@purpose:	http://code.google.com/codejam/contest/dashboard?c=975485#s=p0
*********************************************************************/
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

vector<char> symbolList;
vector<int> orgValueList;
vector<int> blueValueList;

int main()	{
//int tempTest(istream& cin, ostream& cout)	{
	int T, N;
	cin >> T;
	for(int i = 0; i < T; i++)	{
		cin >> N;
		symbolList.clear();
		orgValueList.clear();
		blueValueList.clear();
		for(int j = 0; j < N; j++)	{
			int tempInt;
			char tempChar;
			cin >> tempChar >> tempInt;
			symbolList.push_back(tempChar);
			if(tempChar == 'O')	{
				orgValueList.push_back(tempInt);
			}
			else	{
				blueValueList.push_back(tempInt);
			}
		}
		int secondsSum = 0;
		int currentOrgValue = 1, currentBlueValue = 1;
		int currentOrgPosition = 0, currentBluePosition = 0;
		for(int j = 0; j < N; j++)	{
			if(symbolList[j] == 'O')	{
				int step = abs(orgValueList[currentOrgPosition] - currentOrgValue) + 1;
				currentOrgValue = orgValueList[currentOrgPosition];
				secondsSum += step;				
				currentOrgPosition++;
				if(currentBluePosition < blueValueList.size())	{
					int nextValue = blueValueList[currentBluePosition];
					if(abs(currentBlueValue - nextValue) <= step)	{
						currentBlueValue = nextValue;
					}
					else	{
						if(currentBlueValue < nextValue)	{
							currentBlueValue += step;
						}
						else	{
							currentBlueValue -= step;
						}
					}
				}
			}
			else	{
				int step = abs(blueValueList[currentBluePosition] - currentBlueValue) + 1;
				currentBlueValue = blueValueList[currentBluePosition];
				secondsSum += step;				
				currentBluePosition++;
				if(currentOrgPosition < orgValueList.size())	{
					int nextValue = orgValueList[currentOrgPosition];
					if(abs(currentOrgValue - nextValue) <= step)	{
						currentOrgValue = nextValue;
					}
					else	{
						if(currentOrgValue < nextValue)	{
							currentOrgValue += step;
						}
						else	{
							currentOrgValue -= step;
						}
					}
				}
			}
		}
		cout << "Case #" << i+1 << ": " << secondsSum << "\n";
	}
	return 0;
}
