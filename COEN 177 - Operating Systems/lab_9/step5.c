#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

int BSIZE;
int NTHREADS;
typedef struct
{
    char *fname;
    int i;
}LIST;

void *go(void *arg)
{
    LIST *l = (LIST*)arg;

    char *origname = (*l).fname;
    int origlen = strlen(origname);

    char cpy[origlen+3];
    cpy[0] = 't';
    if((*l).i < 10)
        cpy[1] = (char)(*l).i + '0';
    else
    {
        int first = (*l).i /10;
        int second = (*l).i % 10;
        cpy[1] = (char)first + '0';
        cpy[2] = (char)second + '0';
    }
    strcat(cpy, origname);

    char buffer[BSIZE];
    FILE * fp1, *fp2;
    fp1 = fopen(origname, "rb");
    fp2 = fopen(cpy, "wb");
    while(fread(buffer, sizeof(buffer), 1, fp1))
    {
        fwrite(buffer, sizeof(buffer), 1, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

int main(int agrc, char *argv[])
{
    BSIZE = atoi(argv[2]);
    NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];
    int i;
    for(i = 0; i< NTHREADS; i++)
    {
        LIST *l;
        l = malloc(sizeof(LIST));
        (*l).fname = argv[1];
        (*l).i = i;
        pthread_create(&threads[i], NULL, go, (void *)l);
    }
    int j;
    for(j = 0; j<NTHREADS; j++)
    {
        pthread_join(threads[j], NULL);
    }
}
