#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i;
    char plain[100], sub[100], letter[256], text[100];
    cin.getline(plain, 100, '\n');
    cin.getline(sub, 100, '\n');
    for(i = 0;i < 256; i++) letter[i] = char(i);
    for(i = 0;plain[i] != '\0'; i++) letter[int(plain[i])] = sub[i];
    cout << sub << endl << plain <<endl;
    while( cin.getline(text, 100, '\n') )  {
        for(i = 0; text[i] != '\0'; i++) text[i] = letter[int(text[i])];
        cout << text <<endl;
    }
    return 0;
}
