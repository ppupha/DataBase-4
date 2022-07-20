#include <stdio.h>

typedef struct ex
{
    int n;
    int m;
    int a[100][100];
} ex_t;

int input(ex_t *ae)
{
    for (int i = 0; i < ae->n; i++)
        for (int j = 0; j < ae->m; j++)
            ae->a[i][j] = i + j;
    return 0;
}

int main(void)
{
    ex_t ae;
    ae.n = 3;
    ae.m = 4;
    input(&ae);
    for (int i = 0; i < ae.n; i++)
    {
        for (int j = 0; j < ae.m; j++)
            printf("%d ", ae.a[i][j]);
        printf("\n");
    }
    return 0;
}
