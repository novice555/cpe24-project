#include<string.h>
#include<stdio.h>
int main()
{
    char k[2000] = "abc";
    strcat(k, "12 123 12 12 1");
    printf("%s\n", k);
}
