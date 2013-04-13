#include <stdio.h> 
#include <string.h> 

char ch1[300],ch2[300],ch3[300]; 
long status[300][300][300][2]; 

long solve() 
{ 
        int l1,l2,l3,i,j,k; 
        l1 = strlen(ch1); 
        l2 = strlen(ch2); 
        l3 = strlen(ch3); 
        for(i = 0;i <= l1;i++) 
        for(j = 0;j <= l2;j++) 
                status[i][j][0][0] = status[i][j][0][1] = 1; 
        for(i = 0;i <= l1;i++) 
        for(k = 1;k <= l3 && k <= i;k++) 
        { 
                status[i][0][k][1] = 0; 
                status[i][0][k][0] = status[i-1][0][k][0]; 
                if(ch1[i-1] == ch3[k-1]) status[i][0][k][0] += status[i-1][0][k-1][0]; 
        } 
        for(j = 0;j <= l2;j++) 
        for(k = 1;k <= l3 && k <= j;k++) 
        { 
                status[0][j][k][0] = 0; 
                status[0][j][k][1] = status[0][j-1][k][1]; 
                if(ch2[j-1] == ch3[k-1]) status[0][j][k][1] += status[0][j-1][k-1][1]; 
        } 
        for(i = 1;i <= l1;i++) 
        for(j = 1;j <= l2;j++) 
        for(k = 1;k <= i+j && k <= l3;k++) 
        { 
                status[i][j][k][0] = status[i-1][j][k][0]; 
                if(ch1[i-1] == ch3[k-1]) status[i][j][k][0] += status[i-1][j][k-1][0]+status[i-1][j][k-1][1]; 
                status[i][j][k][1] = status[i][j-1][k][1]; 
                if(ch2[j-1] == ch3[k-1]) status[i][j][k][1] += status[i][j-1][k-1][0]+status[i][j-1][k-1][1];           
        } 
        return status[l1][l2][l3][0]+status[l1][l2][l3][1]; 
} 

int main() 
{ 
        int t; 
        scanf("%d",&t); 
        while(t--) 
        { 
                scanf("%s%s%s",ch1,ch2,ch3); 
                printf("%d\n",solve()); 
                memset(ch1,0,300); 
                memset(ch2,0,300); 
                memset(ch3,0,300); 
        } 
        return 0; 
} 

