﻿#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
vector<int> intVector(100);
 
int main()
{
    intVector[20] = 50;
    const vector<int>::iterator intIter=
    find(intVector.begin(),intVector.end(),50);
    
    if(intIter!=intVector.end())
    cout<<"Vector contains value "<<*intIter<<endl;
    
    else cout<<"Vector does not contain 50"<<endl;
    *intIter=13;
    
    cout<<"intIterChanged is "<<*intIter<<endl;
    system("pause");
    return 0;
}
 