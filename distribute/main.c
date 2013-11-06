#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
//#include"split_file_mode_a.c"
void distribute(char *path, int n_child, void (*split_file)(FileSource*, FileSourceProperties, FileSource**, FileSourceProperties*, int));
int main(int argc, char *argv[])
{
    distribute(argv[1], atoi(argv[2]), split_file_mode_a);
    return 0;
}
