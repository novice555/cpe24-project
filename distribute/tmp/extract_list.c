#include<stdio.h>
#include"include/distribute.h"
int extract_list(int child, void *src, void *re_src)
{
    CompactSrc *decompact = (CompactSrc *) src;
    FileDesc Parent = decompact->in;
    FileDesc *Child = decompact->out;
    FileDesc Same = decompact->same;

    CompactSrc *re_decompact = (CompactSrc *) re_src;
    FileDesc *Re_Child = re_decompact->out;
    FileDesc Re_Same = re_decompact->same;
    
    int i;
    for(i=0; i<child; i++)
    {
        i++;
    }

}
