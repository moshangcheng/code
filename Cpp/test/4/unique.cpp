#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    vector<int> L;
    for(int i = 0; i < 100 ; i++) L.push_back(i % 5);
    
    vector<int>::iterator new_end = unique(L.begin(), L.end());
    copy(L.begin(), new_end, ostream_iterator<int>(cout, " "));
    cout<<endl<<endl;;
    
    sort(L.begin(), L.end());
    new_end = unique(L.begin(), L.end());
    copy(L.begin(), new_end, ostream_iterator<int>(cout, " "));
    system("pause");
    return 0;
}
    
    
