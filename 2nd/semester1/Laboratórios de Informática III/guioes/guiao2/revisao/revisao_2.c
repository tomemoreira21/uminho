#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main (int argc,char** argv) {
    if (argc < 2) {
        fprintf (stderr,"Missing filename.\n");
        return 1;
    }

    FILE* fp = fopen ("teste2.txt","a");
    time_t t = time(NULL);
    struct tm timeInfo = *localtime(&t);

    //fputs("The time is: \n", fp);
    fprintf(fp, "[%d-%02d-%02d %02d:%02d:%02d] - %s\n",
    timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
    timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, argv[1]);
    
    fclose (fp);
    return 0;
}   
