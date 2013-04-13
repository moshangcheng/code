#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;

bool yeah;
int n, nb, depth, stick[51], num[51];

bool dfs(int cnt_len, int len) {
   if(depth == n) return (cnt_len == len);
   int i;
   if(cnt_len == len) {
      for(i = nb-1; i >= 0 && num[stick[i]] == 0; i--);
      if(i >= 0) {
         num[stick[i]]--;
         depth++;
         yeah = dfs(stick[i], len);
         depth--;
         num[stick[i]]++;
         if(yeah == 1) return 1;
      }
   }      
   else if(cnt_len < len) {
      for(i = 0; i < nb; i++) {
         if(num[stick[i]] == 0) continue;
         if(stick[i]+cnt_len > len) break;
         num[stick[i]]--;
         depth++;
         yeah = dfs(cnt_len + stick[i], len);
         depth--;
         num[stick[i]]++;
         if(yeah == 1) return 1;
      }
   }
   return 0;
}

int main()
{
   ifstream in("in.txt");
   ofstream out("out.txt");
   int i, j, tmp, len, tot_len;
   while(in >> n && n > 0) {
      memset(num, 0, sizeof(num));
      for(tot_len = i = 0; i < n; i++) {
         in >> tmp;
         if(tmp > 50) {
            n--;
            i--;
         }
         else {
            tot_len += tmp;
            num[tmp]++;
         }
      }
      if(tot_len == 0) {
         out << 0 << endl;
         continue;
      }
      for(nb = 0, i = 1; i < 51; i++) 
         if(num[i] > 0) stick[nb++] = i;
      for(len = 1; len < tot_len; len++) {
         if(tot_len % len != 0) continue;
         depth = 0;
         yeah = dfs(len, len);
         if(yeah) break;
      }
      out << len << endl;
   }
   return 0;
}
