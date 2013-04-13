#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream in("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt");
    char plain[100],sub[100],letter[256],text[100];
    in.getline(plain,100,'\n');
    in.getline(sub,100,'\n');
    for(int i=0;i<256;i++) letter[i]=char(i);
    for(int i=0;plain[i]!='\0';i++) letter[int(plain[i])]=sub[i];
    cout<<sub<<endl<<plain<<endl;
    in.getline(text,100,'\n');
    while(in.getline(text,100,'\n')){
        for(int i=0;text[i]!='\0';i++) text[i]=letter[int(text[i])];
        cout<<text<<endl;
    }
    system("pause");
    return 0;
}
