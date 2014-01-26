#include <iostream>
using namespace std;

struct TS {
    int value;
};

int main() {
    TS* lpTS;
    {
        TS lTS;
        lTS.value = 3;
        lpTS = std::move  
    }
    cout << lpTS->value << endl;
    return 0;
}
