#include <cstdio>
#include <string>
using namespace std;

const int L = 17;
const int DIV = 200;
const int VALUE = 10;

unsigned int f(char* s)	{
	unsigned int sum = 0, temp;
	for(int i = 0; s[i] != '\0'; i++)	{
		temp = s[i];
		sum +=  temp * temp * temp;
	}
	return sum;
}

int main()
{
	int i;
	char buf[L];
	char out[100][L];
	char division[100][DIV][L];
	int  freq[100][DIV];
	int  last[100][DIV];
	int  cnt_f[100][DIV];
	
	memset(cnt_f, 0, sizeof(cnt_f)); 
	memset(freq,  0, sizeof(freq));
	memset(last,  0, sizeof(last));
	
	for(i = 0; scanf("%s", buf) == 1; i++) {
		//if(strcmp(buf, "*") == 0)	break;
	    unsigned tmp1 = f(buf);
        unsigned tmp2 = tmp1/100%DIV;
        tmp1 %= 100;
        
        freq[tmp1][tmp2]++;
        last[tmp1][tmp2] = i+1;
        
        if(cnt_f[tmp1][tmp2] == 0)	{
			cnt_f[tmp1][tmp2]++;
            strcpy(division[tmp1][tmp2], buf);
		}
		else if(i+1 - last[tmp1][tmp2] < 10000)	{
			cnt_f[tmp1][tmp2]++;
			if(strcmp(division[tmp1][tmp2],buf)!=0 && cnt_f[tmp1][tmp2]*VALUE<freq[tmp1][tmp2])
				strcpy(division[tmp1][tmp2], buf);
		}

    }
    
    for(i = 0; i < 100; i++)	{
		int maxsum = 0;
		int flag;
		for(int j = 0; j < DIV; j++)
			if(maxsum < cnt_f[i][j] + freq[i][j]/VALUE)	{
				flag = j;
				maxsum = cnt_f[i][j] + freq[i][j]/VALUE;
			}
		if(maxsum == 0)	continue;
		else	printf("%s\n", division[i][flag]);
	}
	//system("pause");
    return 0;
}
