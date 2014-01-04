#include<string.h>
#include<stdlib.h>
#include<stdio.h>
void strbuff(char *sptr, char *text)
{
    char *tmp;
    char *ptr;
    int length = strlen(text);
    tmp = malloc(length * sizeof(char));
    strcpy(tmp, text);
    ptr = sptr;
    *ptr = 
}

int main()
{
    char *a;
    char b[250] = "1234567890";
    strbuff(a, b);
    if(a==NULL)
        printf("malloc fail");
    else
        printf("%s", a);
}
