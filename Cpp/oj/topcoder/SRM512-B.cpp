/**
 * @author moshangcheng
 * @version 1.0
 * @date 2011-7-20 下午01:43:06
 * @brief
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

int priceValue[50][50];
int cost[50];//cost[i]表示第i、第i-7、第i-7*2天点餐花费之和的最小值
int dishNum, dayNum, budget;

class MysteriousRestaurant {
public:
	int inline getPrice(char c) {
		if ('0' <= c && c <= '9') {
			return c - '0';
		} else if ('A' <= c && c <= 'Z') {
			return c - 'A' + 10;
		} else {
			return c - 'a' + 36;
		}
	}

	int maxDays(vector<string> prices, int budget) {
		dishNum = prices[0].length();
		dayNum = prices.size();
		budget = budget;
		for (int i = 0; i < dayNum; i++) {
			for (int j = 0; j < dishNum; j++) {
				priceValue[i][j] = getPrice(prices[i][j]);
			}
		}
		for (int i = 0; i < dayNum; i++) {
			int minCost = 0;
			for (int j = 0; j < dishNum; j++) {
				int cntCost = 0;
				//从第i天开始，依次累加第i-7、第i-2*7天等此道菜的价格
				for (int k = i; k >= 0; k -= 7) {
					cntCost += priceValue[k][j];
				}
				if (j == 0 || minCost > cntCost) {
					minCost = cntCost;
				}
			}
			cost[i] = minCost;
		}
		int day = 0, prevCost = 0;
		for (day = 0;; day++) {
			prevCost += cost[day];
			if (day >= 7)
				prevCost -= cost[day - 7];
			if (prevCost >= budget) {
				break;
			}
		}
		return day;
	}
};
