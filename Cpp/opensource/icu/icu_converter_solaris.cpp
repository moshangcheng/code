#include <iostream>
#include <string>
#include <unicode/ucnv.h>
using namespace std;

struct buf_type_base {
    UChar pivot_buf_[ 4096 ], *pivot_source_, *pivot_target_;

    buf_type_base() { reset(); }
    void buf_type_base::reset() {
      pivot_source_ = pivot_target_ = pivot_buf_;
    }
};

struct gbuf_type : buf_type_base {
};
gbuf_type g_;

UConverter* create_conv( char const *charset ) {
    UErrorCode err = U_ZERO_ERROR;
    UConverter *const conv = ucnv_open( charset, &err );
    ucnv_setFromUCallBack(
        conv, UCNV_FROM_U_CALLBACK_STOP, NULL, NULL, NULL, &err
        );
    ucnv_setToUCallBack(conv, UCNV_TO_U_CALLBACK_STOP, NULL, NULL, NULL, &err
        );
    return conv;
}

int main() {
    UErrorCode err = U_ZERO_ERROR;
    UConverter* utf8_conv = create_conv("UTF-8");
    UConverter* eascii_conv = create_conv("ISO-8859-1");

    const char* orig = "הצü";
    char result[100];

    const char* source = orig;
    char* dest = result;

    memset(result, 0, sizeof(result));
    ucnv_convertEx(utf8_conv, eascii_conv, &dest, dest+99, &source, source+3, g_.pivot_buf_, &g_.pivot_source_, &g_.pivot_target_, g_.pivot_buf_ + sizeof g_.pivot_buf_, 0, 1, &err);
    for(int i = 0; i < 100; i++) {
        cout << (int)result[i] << " ";
    }
    cout << endl;

    memset(result, 0, sizeof(result));
    cout << ucnv_convert("UTF-8", "ISO-8859-1", result, 99, orig, 3, &err) << endl;
    for(int i = 0; i < 100; i++) {
        cout << (int)result[i] << " ";
    }
    cout << endl;
    //delete [] pDestStr;
    return 0;
}


