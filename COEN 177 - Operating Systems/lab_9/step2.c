#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    char buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while(fread(buffer, sizeof(buffer), 1, fp))
    {}
    fclose(fp);
}
