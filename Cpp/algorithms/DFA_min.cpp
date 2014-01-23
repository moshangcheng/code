#include <iostream>
#include <fstream>
using namespace std;

//状态用大写字母表示，从A到Z；字母用小写字母表示，从a到z
int K_SIZE;//状态数
int SIGMA_SIZE;//字母表大小
int F_SIZE;//结束状态的数量

char S;//初始状态
bool F[26];//结束状态
int  DELTA[26][26];//转移矩阵

int preEq[26];//等价类的标识
int curEq[26];

ifstream in("in.txt");
ofstream out("out.txt");

void init()    {
	in >> K_SIZE >> SIGMA_SIZE;
	char tmp;//转移的三个参数 delta(p, a) = q
	for(int i = 0; i < K_SIZE; i++)
	for(int j = 0; j < SIGMA_SIZE; j++) {
		in >> tmp;
		DELTA[i][j] = tmp-'A';
	}
	
	in >> S >> F_SIZE;
	int first;
	char tmp_f;
	memset(F, 0, sizeof(F));
	for(int i = 0; i < F_SIZE; i++) {
		in >> tmp_f;
		F[tmp_f-'A'] = true;
		if(i == 0)	first = tmp_f-'A';
		preEq[tmp_f-'A'] = first;
	}
	for(int i = 0, first = -1; i < K_SIZE; i++) {
		if(F[i])    continue;
		if(first < 0)   first = i;
		preEq[i] = first;
	}
}

void update()   {
	int i, j, k;
	for(i = 0; i < K_SIZE; i++) curEq[i] = i;
	for(i = 0; i < K_SIZE; i++) {
		if(curEq[i] != i)   continue;
		for(j = i+1; j < K_SIZE; j++) {
			if(curEq[j] != j)   continue;
			if(preEq[i] != preEq[j])    continue;
			for(k = 0; k < SIGMA_SIZE; k++)
				if(preEq[DELTA[i][k]] != preEq[DELTA[j][k]])  break;
			if(k == SIGMA_SIZE) curEq[j] = i;
		}
	}
}

int main()
{
	init();
	bool flag;
	do	{
		update();
		flag = false;
		for(int i = 0; i < K_SIZE; i++) {
		    if(preEq[i] != curEq[i]) flag = true;
			preEq[i] = curEq[i];
		}
	}while(flag);
	
	int numEq;
	for(int i = numEq = 0; i < K_SIZE; i++)
	    if(curEq[i] == i)   numEq++;
	    
	out << numEq << endl;
	return 0;
}
	
	


		


