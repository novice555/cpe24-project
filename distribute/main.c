#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"
//#include"split_file_mode_a.c"
int main(int argc, char *argv[])
{
/*    if(argv[3][0]=='a')
        distribute(argv[1], atoi(argv[2]), 0, split_file_mode_a);
    else if(argv[3][0]=='b')
        distribute(argv[1], atoi(argv[2]), 0, split_file_mode_b);
    return 0;
*/
    //distribute("~/news", 4, 80, split_file_mode_c);
    distribute(
        argv[1],
        argv[2],
        atoi(argv[3]),
        atoi(argv[4]),
        split_file_mode_c
    );
    return 0;   
}
