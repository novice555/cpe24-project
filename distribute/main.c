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
    distribute(argv[1], atoi(argv[2]), 80, split_file_mode_c);
    
}
