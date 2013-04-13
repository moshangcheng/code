/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-20 下午01:43:14
 * @brief
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class MarbleDecoration {
public:
	int color[3];
	int maxLength(int R, int G, int B) {
		color[0] = R;
		color[1] = G;
		color[2] = B;
		sort(color, color + 3);
		if (color[2] == color[1]) {
			return 2 * color[1];
		} else {
			return 2 * color[1] + 1;
		}
	}
};
