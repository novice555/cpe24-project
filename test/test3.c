#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    char str[256];
    int n;
} A;

int main()
{
    A **ex;
    A *in1;
    A *p[4];
    in1 = malloc(3*sizeof(A));
    strcpy(in1[1].str, "AAAAA");
    in1[1].n = 24;
    p[3] = &in1[1];
    ex = malloc(5*sizeof(A*));
    ex[2] = malloc(4*sizeof(A));
    ex[2][3] = *p[3];
    p[3].n  = 500;
    printf("%s %d\n", ex[2][3].str, ex[2][3].n);
}
