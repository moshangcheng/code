#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct SUB { int c, t, r; };
struct TEAM{ int c, n, t; };

vector<SUB> problem[21];
TEAM team[1001];

bool pb_cmp(const SUB& a, const SUB& b) {
   if(a.c < b.c) return 1;
   else if(a.c == b.c && a.t < b.t) return 1;
   return 0;
}

bool tm_cmp(const TEAM& a, const TEAM& b) {
   if(a.n > b.n) return 1;
   else if(a.n == b.n && a.t < b.t) return 1;
   else if(a.n == b.n && a.t == b.t) return a.c < b.c;
   return 0;
}

int main()
{
   int C, N;
   SUB tmp;
   int i, j, c, p, t, r;
   while(cin >> C >> N) {
      for(i = 1; i <= C; i++) {
         team[i].c = i;
         team[i].n = team[i].t = 0;
      }
      for(i = 1; i < 21; i++)
         problem[i].clear();
      for(i = 0; i < N; i++) {
         cin >> c >> p >> t >> r;
         tmp.c = c;  tmp.t = t;  tmp.r = r;
         problem[p].push_back(tmp);
      }
      for(i = 0; i < 20; i++) 
         sort(problem[i].begin(), problem[i].end(), pb_cmp);
      int cnt_c, cnt_s, sum;
      for(i = 1; i < 20; i++) {
         if(problem[i].empty()) continue;
         cnt_c = sum = cnt_s = 0;
         for(j = 0; j < problem[i].size(); j++) {
            tmp = problem[i][j];
            if(tmp.c == cnt_c) {
               if(cnt_s == 1) continue;
               else if(cnt_s == 0) {
                  if(tmp.r == 1) {
                     sum += tmp.t;
                     cnt_s = 1;
                  }
                  else if(tmp.r == 0) sum += 1200;
               }
            }
            else {
               if(cnt_s == 1) {
                  team[cnt_c].n++;  
                  team[cnt_c].t += sum;
               }
               if(tmp.r == 0) {
                  sum = 1200;    
                  cnt_s = 0;
                  cnt_c = tmp.c;
               }
               else {
                  cnt_c = tmp.c;
                  sum = tmp.t;   
                  cnt_s = 1;
               }
            }
         }
         if(cnt_s == 1) {
            team[cnt_c].n++;
            team[cnt_c].t += sum;
         }
      }
      stable_sort(team+1, team+C+1, tm_cmp);
      for(i = 1; i < C; i++) 
         cout << team[i].c << " ";
      cout << team[C].c << endl;
   }
   return 0;
}
      
         
            
                     
         
         
