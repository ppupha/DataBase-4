#include <string.h>
#include "in_out.h"
#include <stdio.h>
#include "define.h"
#include "my_math.h"

int input_strnum(char *str)
{
    printf("                ---------|---------|---------|---------\n");
    printf("Input a number: ");
    gets(str);
    return OK;
}

void print_int(int *a)
{
    int i = 0;
    while (a[i] != -2)
    {
        printf("%d", a[i]);
        i++;
    }
    //printf("\n");
}
