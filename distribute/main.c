#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
//#include"split_file_mode_a.c"
int main(int argc, char *argv[])
{
    distribute(argv[1], atoi(argv[2]), split_file_mode_a);
    return 0;
}
