﻿#include <iostream>

using namespace std;

int main()
{
	int N,k,S[100],f[10001],g[10001],cookie=1;
	memset(g,0,sizeof(g));
	while (1) {
		cin >> k;
		if (!k) break;
		for(int i=0;i<k;i++) cin >> S[i];
		for(int i=0,j;i<=10000;i++,cookie++) {
			for(j=0;j<k;j++)
				if (i-S[j]>=0) g[f[i-S[j]]]=cookie;
			for(j=0;g[j]==cookie;j++);
			f[i]=j;
		}
		cin >> k;
		while (k--) {
			int h,j,mask=0;
			cin >> h;
			while (h--) {
				cin >> j;
				mask^=f[j];
			}			
			cout << (mask ? "W" : "L");
		}
		cout << endl;
	}
		
	return 0;
}

