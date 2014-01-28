#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

char name[1000];
FILE *fin;
char line[1000];
int i;
int start, cnt, wrong, len;

int main()
{
    while (1) {
        printf("Description: Challenge your speed\n");
        printf("Author: MDZfirst @ Tianjin University\n");
        printf("Version: 8.4.16\n\n");
        printf("Enter the filename: ");
        scanf("%s", name);        
        fin = fopen(name, "r");
        
        if (fin == NULL) {
            printf("File not found!\n\n");
            for (i = 0; i < 80; i++)
                printf("=");
            printf("\n");
            continue;
        } else {
            printf("Press any key to start.\n");
            getchar();
            getchar();
        }    
        
        cnt = wrong = 0;
        start = clock();
        
        while (fgets(line, 80, fin)) {
			len = strlen(line);
			if (line[len - 1] == '\n' || line[len - 1] == '\r')
				line[len - 1] = '\0';
            cnt += len;
            printf("%s\n", line);
            for (i = 0; line[i]; i++) {
                while (getch() != line[i]) {
                    printf("\7");
                    wrong++;
                }    
                printf("%c", line[i]);
            }    
            printf("\n");
        }
        start = clock() - start;
        printf("\n%d characters, %d min %d sec %d ms, average %.3lf cps, precision %.3lf%%\n\n",
            cnt, start / 1000 / 60, start / 1000 % 60, start % 1000,
            1000.0 * cnt / start, 100.0 * cnt / (cnt + wrong));
        
        if (1000.0 * cnt * cnt / start / (cnt + wrong) > 6.0)
            printf("You should register for GRE!\n\n");
        else if (1000.0 * cnt * cnt / start / (cnt + wrong) > 5.0)
            printf("You should register for TOEFL!\n\n");
        else if (1000.0 * cnt * cnt / start / (cnt + wrong) > 4.0)
            printf("You should register for New Oriental!\n\n");
        else if (1000.0 * cnt * cnt / start / (cnt + wrong) > 3.0)
            printf("You should register for CET-6!\n\n");
        else if (1000.0 * cnt * cnt / start / (cnt + wrong) > 2.0)
            printf("You should register for CET-4!\n\n");
        else if (1000.0 * cnt * cnt / start / (cnt + wrong) > 1.0)
            printf("You should register for illiteracy-eliminating class!\n\n");
        else
            printf("You must be iceson!\n\n");
        
        for (i = 0; i < 80; i++)
            printf("=");
        printf("\n");
        
        fclose(fin);
    }    
    
    return (0);
}    
