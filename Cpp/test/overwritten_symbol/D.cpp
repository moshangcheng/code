#include <stdio.h>
namespace S {void testS();}
namespace D {
    int test() {
        return 1;
    }
    void testD() {
        S::testS();
        printf("%s,%d, test=%d\n",__FILE__,__LINE__, test());
    }
}

