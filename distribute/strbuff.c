#include<string.h>
#include<stdlib.h>
char* strbuff(char *text)
{
    char *tmp;
    int length = strlen(text);
    tmp = malloc(length * sizeof(char));
    strcpy(tmp, text);
    return tmp;
}
