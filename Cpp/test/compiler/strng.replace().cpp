#include <string>
#include <iostream>
using namespace std;

void string_replace(string & strBig, const string & strsrc, const string &strdst) {
    string:: size_type pos = 0;
    string:: size_type srclen = strsrc.size();
    string:: size_type dstlen = strdst.size();
    while( (pos = strBig.find( strsrc, pos )) != string::npos){
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}

int main() {
    string strinfo = "This is Winter, Winter is a programmer. Do you know Winter?";
    cout << "Orign string is :\n" << strinfo << endl;
    string_replace(strinfo, "Winter", "wende");
    cout << "After replace Winter with wende, the string is :\n" << strinfo << endl;
    system("pause");
    return 0;
}
