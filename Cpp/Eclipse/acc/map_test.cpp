#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class CStudent
{
public :
  int nStudentID;
  int nAge;
public :
  //缺省构造函数--通常为空
  CStudent()  {  }
  // 完整的构造函数
  CStudent(int nSID, int nA)  {  nStudentID=nSID; nAge=nA;  }
  //拷贝构造函数
  CStudent(const CStudent& ob)  
    {  nStudentID=ob.nStudentID; nAge=ob.nAge;  }
  // 重载"="
  void operator = (const CStudent& ob)  
    {  nStudentID=ob.nStudentID; nAge=ob.nAge;  }
};    


struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

int main()
{
    map <string, CStudent> mapStudent;

  mapStudent["Joe Lennon"] = CStudent(103547, 22);
  mapStudent["Phil McCartney"] = CStudent(100723, 22);
  mapStudent["Raoul Starr"] = CStudent(107350, 24);
  mapStudent["Gordon Hamilton"] = CStudent(102330, 22);

  // 通过姓名来访问Cstudent类中的成员
  cout << "The Student number for Joe Lennon is " << 
    (mapStudent["Joe Lennon"].nStudentID) << endl;
    
    
  map<const char*, int, ltstr> months;
  
  
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  
  cout << "june -> " << months["june"] << endl;
  map<const char*, int, ltstr>::iterator cur  = months.find("june");
  map<const char*, int, ltstr>::iterator prev = cur;
  map<const char*, int, ltstr>::iterator next = cur;    
  ++next;
  --prev;
  cout << "Previous (in alphabetical order) is " << (*prev).first <<(*prev).second << endl;
  cout << "Next (in alphabetical order) is " << (*next).first <<(*next).second<< endl;

  system("pause");
  return 0;
}

