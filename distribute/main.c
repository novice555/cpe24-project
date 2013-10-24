#include<stdio.h>
#include<stdlib.h>
void distribute(char *path, int child);
int main(int argc, char *argv[])
{
    distribute(argv[1], atoi(argv[2]));
    return 0;
}
