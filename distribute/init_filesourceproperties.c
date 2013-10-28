#include<stdlib.h>
#include"distribute.h"
FileSourceProperties init_filesourceproperties()
{
    FileSourceProperties fsp;
    fsp = malloc(sizeof(FileSourcePropertiesDesc));
    fsp->count = 0;
    fsp->sum_size = 0;
    return fsp;
}

