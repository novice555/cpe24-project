#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"include/distribute.h"

static int max_child(FileDesc *desc, int n)
{
    int i;
    int max_no;
    long long max;
    max_no = n-1;
    max = desc[n-1]->sum_size;
    for(i=n-1; i>=0; i--)
    {
        if(desc[i]->sum_size >= max)
        {
            max = desc[i]->sum_size;
            max_no = i;
        }
    }
    return max_no;
}

static int maxxx_child(struct FileSource cmp[], int n)
{
    int i;
    int min_no;
    long long min;
    min_no = 0;
    min = cmp[0].size;
    for(i=1; i<n; i++)
    {
        if(cmp[i].size < min)
        {
            min = cmp[i].size;
            min_no = i;
        }
        else if(cmp[i].size == min)
        {
            if(strcmp(cmp[min_no].filename, cmp[i].filename)<0)
            {
                min = cmp[i].size;
                min_no = i;
            }
        }
    }
    return min_no;
}

static int min_child(FileDesc *desc, int n)
{
    int i;
    int min_no;
    long long min;
    min_no = 0;
    min = desc[0]->sum_size;
    for(i=1; i<n; i++)
    {
        if(desc[i]->sum_size < min)
        {
            min = desc[i]->sum_size;
            min_no = i;
        }
    }
    return min_no;
}

int arrange(int child, int percent, void *re_src, void *mv_src)
{
    CompactSrc *re_decompact = (CompactSrc *) re_src;
    FileDesc *Re_Child = re_decompact->out;
    FileDesc Re_Same = re_decompact->same;
    
    CompactSrc *mv_decompact = (CompactSrc *) mv_src;
    FileDesc *Mv_Child = mv_decompact->out;
    //FileDesc Mv_Same = mv_decompact->same;
    
    long long max_child_size;
    long long sum_all_size;
    long long child_size;
    int cmin, cmax;
    struct FileSource tmp_move;
    int i;
    struct FileSource cmp[child];
    
    sum_all_size = Re_Same->sum_size;
    child_size = 0;
    for(i=0; i<child; i++)
    {
        sum_all_size += Re_Child[i]->sum_size;
        child_size += Re_Child[i]->sum_size;
    }
    max_child_size = percent*sum_all_size/100;
    printf("%lld\n", max_child_size);
    if(child_size<max_child_size)
    {
    
        while(child_size<max_child_size)
        {
            cmin = min_child(Re_Child, child);
            tmp_move = dequeue(Re_Same);
            enqueue(Re_Child[cmin], tmp_move);
            enqueue(Mv_Child[cmin], tmp_move);
            child_size += tmp_move.size;
        }
        return 1;
    }
    else
    {
        while(child_size>max_child_size)
        {
            for(i=0; i<child; i++)
            {
                cmp[i] = *(Re_Child[i]->tail);
            }
            cmax = maxxx_child(cmp, child);
            tmp_move = popqueue(Re_Child[cmax]);
            pushbottom(Re_Same, tmp_move);
            enqueue(Mv_Child[cmax], tmp_move);
            child_size -= tmp_move.size;
        }
        if(child_size!=0)
        {
            tmp_move = dequeue(Re_Same);
            cmin = min_child(Re_Child, child);
            enqueue(Re_Child[cmin], tmp_move);
            child_size += tmp_move.size;
            popqueue(Mv_Child[cmin]);
        }
        return 0;
    }



}
