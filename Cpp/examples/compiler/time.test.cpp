#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

int main()

{
    struct timeb timebuffer;
    ftime( &timebuffer );
    struct ::tm gmtm;
    localtime_r(&timebuffer.time, &gmtm); //thread safe localtime on Linux
    printf("%d\n", timebuffer.timezone); 
    printf("%d\n", timezone);
    printf("%d\n", timebuffer.dstflag);
    return 0;

} 
