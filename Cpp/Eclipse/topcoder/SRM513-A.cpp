#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


class TrainingCamp {
public:
	vector <string> determineSolvers(vector <string> attendance, vector <string> problemTopics) {
		int N = attendance.size();
		int M = attendance[0].size();
		int K = problemTopics.size();
		vector<string> ans;
		for(int i = 0; i < N; i++) {
			string str = "";
			for(int j = 0; j < K; j++) {
				char flag = 'X';
				for(int k = 0; k < M; k++) {
					if(problemTopics[j][k] == 'X' && attendance[i][k] == '-') {
						flag = '-';
						break;
					}
				}
				str += flag;
			}
			ans.push_back(str);
		}
		return ans;
	}
};
