#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
int write_detail(char *path, int child, int percent, void *src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;
    FILE *wr;
    char *detail_name = "/koppae/data/detail.txt";
    int i;
    if((wr=fopen(detail_name, "w"))==NULL)
    {
        fprintf(stderr, "Cannot write file: %s", detail_name);
        exit(1);
    }
    fprintf(wr, "%s\n", path);
    fprintf(wr, "%d\n", child);
    fprintf(wr, "%d\n", percent);
    long long total = 0;
    int total_count = 0;
    for(i=0; i<child; i++)
    {
        fprintf(wr, "%lld\n", Child[i]->sum_size);
        fprintf(wr, "%d\n", Child[i]->count);
        total += Child[i]->sum_size;
        total_count += Child[i]->count;
    }

    fprintf(wr, "%lld\n", Same->sum_size);
    fprintf(wr, "%d\n", Same->count);
    total += Same->sum_size;
    total_count += Same->count;
    fprintf(wr, "%lld\n", total);
    fprintf(wr, "%d\n", total_count);
    fclose(wr);
}
