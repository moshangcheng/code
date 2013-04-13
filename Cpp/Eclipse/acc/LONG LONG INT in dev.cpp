//当输入超过数据的阈值时，只取余 
//例如超过 int 阈值时，只取 x % 2^32 
#include <stdio.h> 

int main() { 
    int i = 4; 
    FILE *fp; 
    signed long long int v_signed_long_long_int; 
    unsigned long long int v_unsigned_long_long_int; 
    freopen("C:\\Documents and Settings\\moshangcheng\\桌面\\in.txt", "r", stdin); 
    fp = fopen("C:\\Documents and Settings\\moshangcheng\\桌面\\OUT.TXT", "wt+"); 
    while (i--) { 
        fprintf(fp, "case %d:\n", 4-i); 
        /* PART1：USE %I64d AND %I64u */ 
        /* [-2^63, 2^63-1] ==> [-9223372036854775808, 9223372036854775807] */ 
        scanf("%I64d", &v_signed_long_long_int); 
        fprintf(fp, "%I64d\n", v_signed_long_long_int); 
        /* [0, 2^64-1] ==> [0, 18446744073709551615]   */ 
        scanf("%I64u", &v_unsigned_long_long_int);  
        fprintf(fp, "%I64u\n", v_unsigned_long_long_int); 
        /* PART2：USE %lld AND %llu */ 
        /* [-2^63, 2^63-1] ==> [-9223372036854775808, 9223372036854775807] */ 
        scanf("%lld", &v_signed_long_long_int); 
        fprintf(fp, "%lld\n", v_signed_long_long_int); 
        /* [0, 2^64-1] ==> [0, 18446744073709551615]   */ 
        scanf("%llu", &v_unsigned_long_long_int); 
        fprintf(fp, "%llu\n", v_unsigned_long_long_int); 
        
        printf("\n\n"); 
        fprintf(fp, "\n\n"); 
    } 
    fclose(fp); 
    getchar();
    return 0; 
} 
