/* memmove example */
#include <stdio.h>
#include <string.h>

void removeSubstring(char *a,const char *b)
{
    char *k;
    k = strstr(a, b);
    puts(k);
}
int main ()
{
  char *a = "/tmp/1/2/3/a.txt";
  char *b = "/tmp/1/2/";
  removeSubstring(a,b);
  puts (a);
  return 0;
}

