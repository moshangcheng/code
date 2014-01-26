#include <iostream>
#include <openssl/hmac.h>
using namespace std;

int main() {
    HMAC_CTX ctx;
    cout << sizeof(ctx.md_ctx) << endl;
    HMAC_Init(&ctx, "abc", 3, EVP_sha1());
    cout << ctx.key_length << "\n";
    return 0;
}

