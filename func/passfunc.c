#include<stdio.h>
//void pass_func(void (*f)(int*, int))
void bubble_sort(int *array, int n)
{                       
    int d, c, swap;
    for (c = 0 ; c < ( n - 1 ); c++)
    {
        for (d = 0 ; d < n - c - 1; d++)
        {
            if (array[d] > array[d+1]) /* For decreasing order use < */
            {
                swap       = array[d];
                array[d]   = array[d+1];
                array[d+1] = swap;
            }
        }
    }
}
void pass_func(void (*f)(int*, int), int *array, int n)
{
    (*f)(array, n);                  
}

int main()
{
    int array[100], n, c;
   
    printf("Enter number of elements\n");
    scanf("%d", &n);
   
    printf("Enter %d integers\n", n);
   
    for (c = 0; c < n; c++)
        scanf("%d", &array[c]);
       
    pass_func(bubble_sort, array, n);   
    printf("Sorted list in ascending order:\n");
   
    for ( c = 0 ; c < n ; c++ )
        printf("%d\n", array[c]);
   
    return 0;
}
