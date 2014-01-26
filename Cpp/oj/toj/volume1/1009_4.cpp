#include <list>
#include <iostream>
using namespace std;

bool yeah;
list<int> stick;
list<int>::iterator cnt;

bool dfs(int cnt_len, int len) {
   if(stick.empty()) 
      return (cnt_len == len);
   if(cnt_len == len) {
      int vlu = stick.back();
      stick.pop_back();
      yeah = dfs(vlu, len);
      stick.push_back(vlu);
      if(yeah) {
         cout << vlu << " ";
         return 1;
      }
   }      
   else if(cnt_len < len) {
      for(cnt = stick.begin(); cnt != stick.end();) {
         if(cnt_len + *cnt > len) break;
         int vlu = *cnt;
         cnt = stick.erase(cnt);
         yeah = dfs(cnt_len + vlu, len);
         stick.insert(cnt, vlu);
         if(yeah) {
            cout << vlu << " ";
            return 1;
         }
      }
   }
   return 0;
}

int main()
{
   int i, n, tot_len, tmp;
   while(cin >> n && n > 0) {
      stick.clear();
      for(tot_len = i = 0; i < n; i++) {
         cin >> tmp;
         if(tmp > 50) continue;
         tot_len += tmp;
         stick.push_back(tmp);
      }
      if(tot_len == 0) {
         cout << 0 << endl;
         continue;
      }
      stick.sort();
      for(i = 1; i < tot_len; i++) {
         if(tot_len % i != 0) continue;
         yeah = dfs(i, i);
         if(yeah) break;
      }
      cout << i << endl;
   }
   return 0;
}
