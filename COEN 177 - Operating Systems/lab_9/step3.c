#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    int size = atoi(argv[2]);
    char buffer[size];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while(fread(buffer, sizeof(buffer),1,fp)){}
    fclose(fp);
}