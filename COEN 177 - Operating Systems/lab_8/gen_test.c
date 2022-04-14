#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define someNumber 10
#define capNumber 10
int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[sizeof(int)];
    int i;
    fp = fopen("testInput.txt", "w");
    for(int i = 0;i< someNumber; i++)
    {
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}