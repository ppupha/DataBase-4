#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define INIT 4

int *check = NULL;
int *a = NULL;
int *head = NULL;
int *adj = NULL;
int *trace = NULL;

int bac = 0;
struct matrix
{
    int *adj;
    int *head;
};
typedef struct matrix matrix_t;

void matrix_input(void)
{
    printf("Input:\n");
    int n;
    int count;
    printf("n = ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("ERROR INPUT\n");
        return;
    }
    a = malloc((n + 1) * (n + 1) * sizeof(int));
    a[0] = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j)
                a[i*n + j] = 1;
            else
                a[i*n + j] = 0;

    printf("Input EGes:\n");
    printf("Input 0 0 to exit\n");
    int x = 1, y = 1;
    while (x != 0 && y != 0)
    {
        printf("Input: ");
        if (scanf("%d %d", &x, &y) != 2 || x < 0 || y < 0 || x > n || y > n)
        {
            printf("ERROR INPUT\n");
            return;
        }
        if (x != 0 && y != 0)
        {
            if (a[x * n + y] == 0)
                count++;
            a[x * n + y]++;
        }
    }
    a[1] = count;
}

void matrix_adj_change(void)
{
    if (!a)
        return;
    int n = a[0];
    int count = a[1];
    head = malloc((n + 2) * sizeof(int));
    head[0] = n;
    adj = malloc((count + 1) * sizeof(int));
    adj[0] = count;
    count = 1;
    for (int i = 1; i <=n; i++)
    {
        head[i] = count;
        for (int j = 1; j <= n; j++)
            if (a[i * n + j])
            {
                adj[count] = j;
                count++;
            }
    }
    head[n + 1] = count;
}



void matrix_print(void)
{
    if (!a)
        return;
    int n = a[0];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            printf("%d ", a[i * n + j]);
        printf("\n");
    }
}

void matrix_adj_print(void)
{
    printf("\n");
    for (int i = 1; i <= adj[0]; i++)
        printf("%d ", adj[i]);
    printf("\n");
    for (int i = 1; i <= head[0] + 1; i++)
        printf("%d ", head[i]);
    printf("\n");
}

void DFS(int u)
{
    bac += INIT;
    for (int i = 0; i < bac - INIT; i++)
        printf(" ");
    printf("|");
    for (int i = 0; i < INIT - 1; i++)
        printf("-");
    printf("%d\n", u);

    check[u] = 1;
    for (int i = head[u]; i < head[u + 1]; i++)
    {
        int v = adj[i];
        if (check[v] == 0)
        {
            trace[v] = u;
            DFS(v);
        }
    }
    bac -= INIT;
}

void matrix_adj_DFS()
{
    int n = head[0];
    int u;
    printf("Input Number :");
    if (scanf("%d", &u) != 1)
    {
        printf("ERROR INPUT\n");
        return;
    }
    if (u <= 0 || u > n)
    {
        printf("ERROR RANGE\n");
        return;
    }
    check = calloc((n + 1), sizeof(int));
    trace = calloc((n + 1), sizeof(int));
    trace[0] = n;
    DFS(u);
}

void print_result()
{
    int n = a[0];
    int count = 0;
    printf("\n\nResult:\n");
    for (int i = 1; i <= n; i++)
        if (check[i] == 0)
        {
            count++;
            printf("%d ", i);
        }
    if (count == 0)
        printf("Empty\n");
    printf("\n\n\n");

    printf("Trace: \n");
    for (int i = 1; i <= n; i++)
        printf("%4d", i);
    printf("\n");

    for (int i = 1; i <= n; i++)
        printf("%4d", trace[i]);
    printf("\n");

    printf("\n");
}

int main(void)
{
    matrix_input();
    matrix_print();
    matrix_adj_change();
    matrix_adj_print();
    matrix_adj_DFS();
    print_result();
    return 0;
}
