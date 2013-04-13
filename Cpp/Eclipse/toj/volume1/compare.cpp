#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
   bool f1, f2;
   ifstream is1("ans.txt");
   ifstream is2("out.txt");
   string s1, s2;
   while(1) {
      getline(is1, s1);
      f1 = is1.fail();
      getline(is2, s2);
      f2 = is2.fail();
      if(f1 && f2) {
         cout << "Accpeted.\n";
         break;
      }
      else if(f1 && !f2) {
         cout << "Output exceeded.\n";
         break;
      }
      else if(!f1 && f2) {
         cout << "Output too less.\n";
         break;
      }
      else if(s1 != s2) {
         cout << "Wrong Answer.\n";
         cout << s1 << endl << s2 << endl;
         break;
      }
   }
   system("pause");
   return 0;
}
