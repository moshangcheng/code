#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

//记录伤害
struct DAMAGE {
	int number;//当前使用的武器编号
	int damage;//累计的总伤害值
	int time;//当前时间
};

const int SIZE = 20;
int weapon[SIZE][2];
vector<DAMAGE> heap;

bool compare(const DAMAGE& a, const DAMAGE& b) {
	if(a.damage > b.damage) {
		return true;
	} else if(a.damage == b.damage) {
		if(a.number > b.number) {
			return true;
		} else if(a.number == b.number) {
			return a.time > b.time;
		}
	}
	return false;
}


int main() {
	int n, k;
	while(scanf("%d%d", &n, &k) == 2) {
		heap.clear();
		for(int i = 0; i < n; i++) {
			scanf("%d%d", weapon[i], weapon[i]+1);
		}
		//初始化
		for(int i = 0; i < n; i++) {
			DAMAGE tempDamage;
			tempDamage.number = i;
			tempDamage.damage = weapon[i][0] + weapon[i][1];
			tempDamage.time = 1;
			heap.push_back(tempDamage);			
		}

		DAMAGE lastDamage, minDamage;
		make_heap(heap.begin(), heap.end(), compare);
		for(int i = 0; i < k; i++) {
			//获取最小伤害minDamage，同时判重和压入侄子节点
			for(int j = 0; j < n; j++) {
				if(j == 0) {					
					minDamage = heap[0];
				}
				else {
					//判重结束
					if(heap[0].damage > minDamage.damage) {
						break;
					}
					if(minDamage.time > heap[0].time) {
						minDamage = heap[0];
					}
				}
				lastDamage = heap[0];
				pop_heap(heap.begin(), heap.end(), compare);
				heap.pop_back();							
				while(heap[0].damage == lastDamage.damage && heap[0].number == lastDamage.number) {								
					//如果伤害和使用的武器相同，时间较大的节点的侄子节点不必压入堆
					pop_heap(heap.begin(), heap.end(), compare);
					heap.pop_back();
				}
				
				//将侄子节点压入堆
				DAMAGE nephewDamage;
				//侄子节点的伤害
				nephewDamage.damage = lastDamage.damage + weapon[lastDamage.number][1];
				nephewDamage.time = lastDamage.time+1;
				nephewDamage.number = lastDamage.number;
				heap.push_back(nephewDamage);
				push_heap(heap.begin(), heap.end(), compare);
			}			
			//将所有子节点压入堆
			DAMAGE childDamage;
			for(int j = 0; j < n; j++) {
				childDamage.number = j;
				childDamage.time = minDamage.time + 1;
				//子节点的伤害
				childDamage.damage = minDamage.damage + weapon[j][0] + weapon[j][1]*childDamage.time;							
				heap.push_back(childDamage);
				push_heap(heap.begin(), heap.end(), compare);
			}
		}
		printf("%d\n", minDamage.damage);
	}
	return 0;
}