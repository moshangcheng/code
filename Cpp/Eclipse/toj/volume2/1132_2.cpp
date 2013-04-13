#include <iostream>
#include <string>
using namespace std;

int minKightStep(int a, int b){ //a >= 0 && b >= 0
 if(a > b) swap(a, b);
 if(a == 0){
  if(b == 0) return 0;
  if(b == 1) return 3;
  if(b == 2) return 2;
  if(b == 6) return 4;
 }
 if(a == 1 && b == 4) return 3;
 if(a == 2 && b == 2) return 4;

 int u = min(min((a+b) / 3, (2*a+b) / 4) , (a+2*b) / 4);
 return a+b-2*u;

}

int main()
{
 string s1,s2;
 int ax,ay,bx,by;

 while(cin >> s1 >> s2)
 {
  if ( s1 == s2 )
  {
   cout << "To get from " << s1 << " to " << s2 << " takes 0 knight moves.";
   continue;
  }

  ax = s1[0]-'a';
  ay = s1[1]-'1';
  bx = s2[0]-'a';
  by = s2[1]-'1';

  cout << minKightStep(ax*8+ay,bx*8+by) << endl;
 }

}


