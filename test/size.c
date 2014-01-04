#include<stdio.h>
static long file_size(char *fullpath)
{

    FILE *fp;
    long size;
    fp = fopen(fullpath, "rb");
    if(fp == NULL)
    {
        fprintf(stderr, "\nFile not found!\n");
    }
    else
    {
        fseek(fp, 0L,SEEK_END);
        size = ftell(fp);
        fclose(fp);
    }
    return size;
}
int main()
{
    printf("%ld\n", file_size("test.txt"));
}
