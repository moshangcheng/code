#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

const int INF = 1000000000;
int main()
{
   int i;
   string s;
   double length;
   int section, nb, hour, mnt, sec, time, v, flag;
   cin >> section >> length;
   while(1)  {
      while(cin >> nb) {
         flag = 1;
         cin >> s;
         istringstream is(s);
         if(s.size() != 7) {
            section = nb;
            is >> length;
            break;
         }
         i = time = 0;
         while(1) {
            if(s == "-:--:--") 
               time += INF;
            else if(time < INF) {
               hour  = (s[0]-'0');
               mnt   = (s[2]-'0')*10 + (s[3]-'0');
               sec   = (s[5]-'0')*10 + (s[6]-'0');
               time += hour*3600 + mnt*60 + sec;
            }
            if(++i < section) cin >> s;
            else break;
         }
         cout << setw(3) << nb << ": ";
         if(time >= INF) cout << "-\n";
         else {
            v = floor(time/length + 0.5);
            cout << v/60 << ":";
            if(v%60 < 10) cout << 0;
            cout << v%60 << " min/km\n";
         }
         flag = 0;
      }
      if(flag == 0) break;
   }
   return 0;
}
   
