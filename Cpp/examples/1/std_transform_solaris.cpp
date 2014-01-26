#include <iostream>
#include <algorithm>
#include <vector>

int f(int i) { std::cout << i << std::endl; return  i+1; }
int main() {
    std::vector<int> lIntVec;
    for(int i = 0; i < 10; i++) {
        lIntVec.push_back(i);
    }
    std::vector<int> lAnotherIntVec;
    lAnotherIntVec.resize(lIntVec.size());
    std::transform(lIntVec.begin(), lIntVec.end(), lAnotherIntVec.begin(), f); 
    return 0;
}
