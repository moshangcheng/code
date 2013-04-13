#include <list>
#include <iostream>
using namespace std;

list<int> stick;
int n, tot_len;
list<int>::iterator cnt, prev, next;

bool dfs(int cnt_len, int len) {
   bool yeah;
   if(stick.empty()) return (cnt_len == len);
   int i, vlu;
   if(cnt_len == len) {
      vlu = stick.front();
      stick.pop_front();
      yeah = dfs(vlu, len);
      stick.push_front(vlu);
      if(yeah) return 1;
   }      
   else if(cnt_len < len) {
      for(cnt = stick.begin(); cnt != stick.end();) {
         //如果写成 prev = cnt++， 无法过样例
         //但是我写成 prev = cnt++;
        //            cout << *prev << " " << *cnt << endl;
        //多了一行输出，又能过样例了
        //按照标准写法  cnt = stick.erase(cnt) 也不行 
         prev = cnt;
         cnt++;
         vlu = *prev;
         stick.erase(prev);
         yeah = dfs(cnt_len + vlu, len);
         stick.insert(cnt, vlu);
         if(yeah) return 1;
      }
   }
   else if(cnt_len > len) return 0;
}

int main()
{
   bool yeah;
   int i, j;
   while(cin >> n && n > 0) {
      stick.clear();
      for(tot_len = i = 0; i < n; i++) {
         cin >> j;
         if(j > 50) continue;
         tot_len += j;
         stick.push_back(j);
      }
      if(tot_len == 0) {
         cout << 0 << endl;
         continue;
      }
      stick.sort();
      stick.reverse();
      //不让我输出链表中的值，一输出就无法过样例
      //list<int>::iterator here;
      //for(here = stick.begin(); here != stick.end(); here++)
      //   cout << *here << " ";
      //cout << endl;
      for(i = 1; i < tot_len; i++) {
         if(tot_len % i != 0) continue;
         // if(dfs(i, i)) 与 if(dfs(i,i) == 1) 不同 
         if(dfs(i, i) == 1) break;
      }
      cout << i << endl;
   }
   return 0;
}

