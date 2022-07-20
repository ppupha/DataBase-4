#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
//318
#define N_MAX 10
#define K_NUM 2//N_MAX * N_MAX / 100000
#define N_PRINT 20

struct node
{
    int value;
    struct node *next;
};

typedef struct node *node_t;

typedef struct mat1
{
    double *AN;
    int *JA;
    node_t IA;
    int nia;
} mat1_t;

typedef struct mat2
{
    int n; // n - số hàng
    int m; // m - số cột
    double **a; // mảng
} mat2_t;

node_t new_node(int value)
{
    node_t tmp = (node_t) malloc(sizeof(node_t));
    tmp->value = value;
    tmp->next = NULL;
    return tmp;
}

void add_node(node_t node1, node_t node2)
{
    //printf("Value %d %d\n", node1->value, node2->value);
    /*node2->next = node1->next;*/
    node1->next = node2;
}

void node_link_free(node_t head)
{
    node_t tmp = head;
    while (tmp)
    {
        node_t tmp1 = tmp->next;
        free(tmp);
        tmp = tmp1;
    }
}

int max_arr(int *a, int n)
{
    assert(a);
    int max = a[1];
    for (int i = 2; i <= n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

void matrix_free_1(mat1_t *mA1)
{
    if (!mA1)
        return;
    if (mA1->AN)
        free(mA1->AN);
    if (mA1->JA)
        free(mA1->JA);
    //node_link_free(mA1->IA);
    free(mA1);
}

void matrix_free_2(mat2_t *mA2)
{
    if (!mA2)
        return;
    for (int i = 0; i <= mA2->n; i++)
        free(mA2->a[i]);
    free(mA2->a);
    free(mA2);
}

void matrix_print_2(mat2_t mA)
{
    for (int i = 1; i <= mA.n; i++)
    {
        for (int j = 1; j <= mA.m; j++)
            printf("%8.2f ", mA.a[i][j]);
        printf("\n");
    }
}

void matrix_print_1(mat1_t mA)
{
    printf("AN: ");
    for (int i = 1; i <= mA.JA[0]; i++)
        printf("%6.2f ", mA.AN[i]);
    printf("\nJA: ");
    for (int i = 1; i <= mA.JA[0]; i++)
        printf("%6d ", mA.JA[i]);
    printf("\nIA: ");
    node_t tmp = mA.IA;
    while (tmp)
    {
        printf("%6d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

double vector_row_mult(int *JA, double *AN, int na, int *JB, double *BN, int nb)
{
    assert(JA);
    assert(AN);
    assert(JB);
    assert(BN);
    //printf("checkkkkk\n");
    int namax = max_arr(JA, na);
    double mult = 0.0;
    if (na <= 0 || nb <= 0)
        return mult;
    int IP[namax];
    for (int i = 1; i <= namax; i++)
        IP[i] = 0;
    for (int i = 1; i <= na; i++)
    {
        int tmp = JA[i];
        IP[tmp] = i;
    }
    //printf("checkkkk2\n");
    for (int i = 1; i <= nb; i++)
    {
        if (JB[i] <= namax && IP[JB[i]] != 0)
            mult += BN[i] * AN[IP[JB[i]]];
    }
    //printf("check!\n");

    return mult;
}

node_t get_before(node_t head, node_t node)
{
    if (node == head)
        return NULL;

    node_t tmp = head;
    while (tmp->next != node && tmp)
        tmp = tmp->next;

    return tmp;
}

int set_last(node_t head)
{
    int count = 0;
    node_t last = head;
    while (last->next)
        last = last->next;
    while (1 == 1)
    {
        //printf("count = %d\n", count);
        node_t before = get_before(head, last);
        if (!before)
            return count;
        if (before->value != last->value)
            return count;
        count++;
        //free(last);
        last = before;
        last->next = NULL;
    }
}

double ** matrix_alloc(int n, int m)
{
    double **a = calloc((n + 1), sizeof(double*));
    if (!a)
        return NULL;
    for (int i = 1; i <= n; i++)
    {
        a[i] = calloc((m + 1), sizeof(double));
        if (!a[i])
            return NULL;
    }
    return a;
}

mat1_t * matrix_A_t(mat1_t *mA)
{
    assert(mA);

    mat1_t * mAT = malloc(sizeof(mat1_t));
    if (!mAT)
    {
        printf("ERR ALLOC MATRĨ_A_T\n");
        return NULL;

    }
    mAT->AN = malloc((mA->JA[0] +1) * sizeof(double));
    if (!mAT->AN)
    {
        matrix_free_1(mAT);
        printf("ERR ALLOC MATRiX_A_T\n");
        return NULL;
    }

    mAT->JA = malloc((mA->JA[0] + 1) * sizeof(int));
    if (!mAT->JA)
    {
        matrix_free_1(mAT);
        printf("ERR ALLOC MATRiX_A_T\n");
        return NULL;
    }

    mAT->JA[0] = mA->JA[0];
    int col = max_arr(mA->JA, mA->JA[0]);
    int row = mA->JA[0];
    mAT->nia = col + 1;
    //printf("check4 %d\n", col);


    int **p = calloc(col + 1, sizeof(int *));
    for (int i = 0; i <= col; i++)
        p[i] = calloc(row + 1, sizeof(int));
    double **a_t = matrix_alloc(col, mA->JA[0]);// mảng giá trị

    for (int i = 1; i <= col; i++)
        p[i][0] = 0;
    node_t node_i = mA->IA, node_ii = node_i->next;

    //printf("check5 mA->nia = %d\n", mA->nia);
    for (int row = 1; row <= mA->nia - 1; row++)
    {
        for (int j = node_i->value; j < node_ii->value; j++)
        {
            int cj = mA->JA[j];
            p[cj][0]++;

            p[cj][p[cj][0]] = row;
            a_t[cj][p[cj][0]] = mA->AN[j];
        }
        node_i = node_ii;
        node_ii = node_i->next;
    }


    //printf("check6\n");
    int count = 1;
    mAT->IA = new_node(1);
    if (!mAT->IA)
    {
        matrix_free_1(mAT);
        printf("ERR ALLOC MATRiX_A_T\n");
        return NULL;
    }
    node_t tmp = mAT->IA;
    //printf("check7 col = %d\n", col);


    for (int i = 1; i <= col; i++)
    {
        for (int j = 1; j <= p[i][0]; j++ )
        {
            //printf("i = %d j = %d p = %d a = %lf\n", i, j, p[i][j], a_t[i][j]);
            mAT->JA[count] = p[i][j];
            mAT->AN[count] = a_t[i][j];
            count++;
        }
    }

    count = 1;
    for (int i = 1; i <= col; i++)
    {
        count += (int) p[i][0];
        node_t new = new_node(count);
        if (!new)
        {
            matrix_free_1(mAT);
            printf("ERR ALLOC MATRiX_A_T\n");
            return NULL;
        }        add_node(tmp, new);
        node_t tmp1 = mAT->IA;
        while (tmp1)
        {
            //printf("%d -- ", tmp1->value);
            tmp1 = tmp1->next;
        }
        //printf("\n");
        //printf("value %d %d\n", tmp->value, tmp->next->value);
        tmp = new;

    }

    //matrix_print_1(*mAT);
    //printf("check8\n");*/
    mAT->nia -= set_last(mAT->IA);

    return mAT;
}

mat2_t * matrix_change_1(mat1_t *mA)
{
    mat2_t *mB = malloc(sizeof(mat2_t));
    if (!mB)
    {
        printf("ERR ALO MATRIX_CHANGE_!\n");
        return NULL;
    }
    if (mA->JA[0] == 0)
    {
        mB->n = 1;
        mB->m = 1;
        mB->a = matrix_alloc(mB->n, mB->m);
        if (!mB->a)
        {
            printf("ERR ALO MATRIX_CHANGE_!\n");
            return NULL;
        }
        mB->a[1][0] = 0;
        return mB;
    }

    int max = max_arr(mA->JA, mA->JA[0]);
    //printf("check1 %d \n", max);
    mB->m = max;
    mB->n = mA->nia - 1;
    mB->a = matrix_alloc(mB->n, mB->m);
    if (!mB->a)
    {
        printf("ERR ALO MATRIX_CHANGE_!\n");
        return NULL;
    }
    //printf("check2\n");

    int *IP = calloc(max + 1, sizeof(int));
    if (!IP)
    {
        printf("ERR ALO MATRIX_CHANGE_!\n");
        return NULL;
    }

    node_t node_i = mA->IA, node_ii = node_i->next;
    //printf("check3\n");

    for (int i = 1; i <= mA->nia - 1; i++)
    {
        for (int k = 1; k <= max; k++)
            IP[k] = 0;
        for (int k = node_i->value; k <= node_ii->value - 1; k++)
        {
            IP[mA->JA[k]] = k;
        }

        for (int j = 1; j <= max; j++)
        {
            if (IP[j] != 0)
            {
                int tmp = IP[j];
                tmp = mA->AN[tmp];
                mB->a[i][j] = tmp;
            }
            else
                mB->a[i][j] = 0.0;
        }
        node_i = node_ii;
        node_ii = node_i->next;
    }
    //printf("check4\n");
    return mB;
}

mat1_t * matrix_mult_1(mat1_t *mA, mat1_t *mB)
{
    mat1_t *mC = malloc(sizeof(mat1_t));
    if (!mC)
    {
        matrix_free_1(mC);
        printf("ERROR ALLOC MC MATRIX_MULT_1\n");
        return NULL;
    }
    mC->AN = malloc(sizeof(double));
    if (!mC->AN)
    {
        matrix_free_1(mC);
        printf("ERROR ALLOC MATRIX_MULT\n");
        return NULL;
    }
    mC->JA = calloc(1, sizeof(int));
    if (!mC->JA)
    {
        matrix_free_1(mC);
        printf("ERROR ALLOC MATRĨ_MULT\n");
        return NULL;
    }
    mC->JA[0] = 0;
    mC->nia = mA->nia;

    mat1_t *mBT = matrix_A_t(mB);

    //printf("MAtrix BT: \n");
    //matrix_print_1(*mBT);

    mC->IA = new_node(1);
    node_t tmp = mC->IA;
    node_t node_ia = mA->IA;
    for (int i = 1; i <= mA->nia - 1; i++)
    {
        node_t node_jbt = mBT->IA;
        for (int j = 1; j <= mBT->nia - 1; j++)
        {
            //printf("i = %d j = %d\n", i, j);
            // hàng i ma trận A: vị trí bắt đầu: PA[i], số phần tử: PA[i + 1] - PA[i],
            // hàng j ma trận BT:                PBT[j],             PBT[j + 1] - PBT[j],

            double mult_ij = vector_row_mult(mA->JA + node_ia->value - 1, mA->AN + node_ia->value - 1, node_ia->next->value - node_ia->value, mBT->JA + node_jbt->value - 1, mBT->AN + node_jbt->value - 1, node_jbt->next->value - node_jbt->value);
            //mult_ị = vector_row_mult(*mA, mBT, i, j);
            if (mult_ij != 0)
            {
                (mC->JA[0])++;
                int *tmp2 = realloc(mC->JA, (mC->JA[0] + 1) * sizeof(int));
                mC->JA = tmp2;
                double *tmp1 = realloc(mC->AN, (mC->JA[0] + 1) * sizeof(double));
                mC->AN = tmp1;
                mC->AN[mC->JA[0]] = mult_ij;
                mC->JA[mC->JA[0]] = j;
            }
            node_jbt = node_jbt->next;
        }

        node_t new = new_node((mC->JA[0]) + 1);
        add_node(tmp, new);
        tmp = tmp->next;
        node_ia = node_ia->next;
    }

    int *tmp2 = realloc(mC->JA, (mC->JA[0] + 1) * sizeof(int));
    mC->JA = tmp2;
    double *tmp1 = realloc(mC->AN, (mC->JA[0] + 1) * sizeof(double));
    mC->AN = tmp1;

    mC->nia -= set_last(mC->IA);
    return mC;
}

mat1_t * matrix_change_2(mat2_t *mA2)
{
    //matrix_print_2(*mA);
    int n = (int) mA2->a[1][0];

    mat1_t *mB1 = malloc(sizeof(mat1_t));
    mB1->JA = malloc((n + 1) * sizeof(int));
    mB1->AN = malloc((n + 1) * sizeof(double));

    mB1->JA[0] = 0;
    mB1->nia = 1;
    mB1->IA = new_node(1);
    node_t tmp = mB1->IA;

    for (int i = 1; i <= mA2->n; i++)
    {
        for (int j = 1; j <= mA2->m; j++)
        {
            if (mA2->a[i][j] != 0)
            {
                //printf("i = %d j = %d %lf %d\n", i, j, mA2->a[i][j], mB1->JA[0]);

                (mB1->JA[0])++;
                mB1->JA[mB1->JA[0]] = j;
                mB1->AN[mB1->JA[0]] = mA2->a[i][j];
            }
        }
        (mB1->nia)++;
        node_t new = new_node(mB1->JA[0] + 1);
        add_node(tmp, new);
        tmp = new;
        (tmp->value) += 0;
    }
    mB1->nia = mB1->nia - set_last(mB1->IA);
    return mB1;
}

mat1_t * matrix_input_1(void)
{
    fflush(stdin);
    mat1_t *mA = malloc(sizeof(mat1_t));
    if (!mA)
    {
        printf("ERR ALLOC MATRiX_INPUT\n");
        return NULL;
    }
    int tmp;
    printf("Input number element: ");
    if (scanf("%d", &tmp) != 1 ||tmp <= 0)
    {
        matrix_free_1(mA);
        printf("ERR ALLOC MATRiX_INPUT\n");
        return NULL;
    }


    mA->AN = malloc(tmp * sizeof(double));
    if (!mA->AN)
    {
        matrix_free_1(mA);
        printf("ERR ALLOC MATRiX_INPUT\n");
        return NULL;
    }

    mA->JA = malloc(tmp * sizeof(int));
    if (!mA->JA)
    {
        matrix_free_1(mA);
        printf("ERR ALLOC MATRiX_INPUT\n");
        return NULL;
    }

    mA->JA[0] = tmp;

    printf("Input Vector AN: ");
    for (int i = 1; i <= mA->JA[0]; i++)
        if (scanf("%lf", mA->AN + i) != 1)
        {
            matrix_free_1(mA);
            printf("ERR ALLOC MATRiX_INPUT\n");
            return NULL;
        }
    printf("Input Vector JA: ");
    for (int i = 1; i <= mA->JA[0]; i++)
        if (scanf("%d", mA->JA + i) != 1 || mA->JA[i] <= 0)
        {
            matrix_free_1(mA);
            printf("ERR ALLOC MATRiX_INPUT\n");
            return NULL;
        }

    printf("Input Row Number");
    if (scanf("%d", &(mA->nia)) != 1 || mA->nia <= 0)
    {
        matrix_free_1(mA);
        printf("ERR ALLOC MATRiX_INPUT\n");
        return NULL;
    }
    (mA->nia)++;

    printf("Input Vector PA: ");
    node_t last = mA->IA;
    for (int i = 1; i <= mA->nia; i++)
    {
        int tmp;
        if (scanf("%d", &tmp)!= 1 || tmp <= 0 || (i != 1 && tmp < last->value))
        {
            matrix_free_1(mA);
            printf("ERR ALLOC MATRiX_INPUT\n");
            return NULL;
        }

        node_t new = new_node(tmp);
        if (!new)
        {
            matrix_free_1(mA);
            printf("ERR ALLOC MATRiX_INPUT\n");
            return NULL;
        }

        if (i == 1)
            mA->IA = new;
        else
            add_node(last, new);
        last = new;
    }
    mA->nia -= set_last(mA->IA);
    return mA;
}

mat1_t *matrix_input_2(void)
{
    fflush(stdin);
    mat2_t *mA2 = malloc(sizeof(mat2_t));
    if (!mA2)
    {
        printf("ERR_MATRIX_INPUT_2\n");
        return NULL;
    }
    printf("Input n(row nummber) and m(col number): ");
    if (scanf("%d %d", &(mA2->n), &(mA2->m)) != 2 || mA2->n <=0 || mA2->m <=0)
        return NULL;

    mA2->a = matrix_alloc(mA2->n, mA2->m);
    printf("n = %d m = %d\n", mA2->n, mA2->m);
    printf("Input elelemts: \n");
    printf("Input row = 0 && col = 0 to finish\n");
    while (1)
    {
        int row, col;
        double value;
        printf("Input row-index and col-index: ");
        if (scanf("%d %d", &row, &col) != 2)
            return NULL;
        if (row == 0 && col == 0 && mA2->a[1][0] != 0)
        {
            mat1_t *mA1 = matrix_change_2(mA2);
            mA1->nia -= set_last(mA1->IA);
            return mA1;
        }
        if ( row <= 0 || col <=0 || row > mA2->n || col > mA2->m)
            return NULL;
        printf("Input Value:\n ");
        if (scanf("%lf", &value) != 1)
            return NULL;
        (mA2->a[1][0])++;
        mA2->a[row][col] = value;
        printf("%lf \n", mA2->a[row][col]);
    }
}

mat2_t *matrix_mult_2(mat2_t *mA, mat2_t *mB)
{
    mat2_t *mC = malloc(sizeof(mat2_t));
    int n = mA->n;
    mC->n = N_MAX;
    mC->m = N_MAX;
    int mult = 0;
    //printf("n = %d\n", n);
    //mC->a = malloc((mC->n + 1) * (mC->m + 1) * sizeof(double));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            mult = 0;
            for (int k = 1; k <=n; k++)
                mult += 1 * 2;
        }
    return mA;
}

float my_rand(int a, int b)
{
    return (int) a + rand() % (b - a + 1);
}

mat2_t *matrix_cre(int n, float pro)
{
    mat2_t * mA = malloc(sizeof(mat2_t));
    mA->n = n;
    mA->m = n;
    mA->a = matrix_alloc(mA->n, mA->m);
    mA->a[1][0] = 0;
    /*int count = n * n * pro / 100;
    if (fabs(pro - 100) < 1e-6)
    {
        for (int i = 1; i <=n; i++)
            for (int j = 1; j <=n; j++)
            {
                    mA->a[i][j] = rand() % 100 + 1;
                    (mA->a[1][0])++;
            }
        return mA;
    }
    int c = 0;
    while (c < count)
    {
        int x = my_rand(1, n);
        int y = my_rand(1, n);
        while (mA->a[x][y] != 0)
        {
           x = my_rand(1, n);
           y = my_rand(1, n);
        }

        mA->a[x][y] = my_rand(1, 10);
        (mA->a[1][0])++;
        c++;
    }
    return mA;*/
    int c = 0;
    int k = 100 / pro - 1;
    for (int i = 1; i <=n; i++)
        for (int j = 1; j <=n; j++)
        {
            if (c == k)
            {
                c = 0;
                mA->a[i][j] = rand() % 100 + 1;
                (mA->a[1][0])++;
            }
            else
            {
                mA->a[i][j] = 0;
                c++;
            }
        }
    return mA;
}

mat2_t *matrix_cre_1(int n, int m, float pro)
{
    mat2_t * mA = malloc(sizeof(mat2_t));
    mA->n = n;
    mA->m = m;
    mA->a = matrix_alloc(mA->n, mA->m);
    mA->a[1][0] = 0;
    int count = n * n * pro / 100;
    if (fabs(pro - 100) < 1e-6)
    {
        for (int i = 1; i <=n; i++)
            for (int j = 1; j <=m; j++)
            {
                    mA->a[i][j] = rand() % 10 + 1;
                    (mA->a[1][0])++;
            }
        return mA;
    }
    int c = 0;
    while (c < count)
    {
        int x = my_rand(1, n);
        int y = my_rand(1, m);
        while (mA->a[x][y] != 0)
        {
           x = my_rand(1, n);
           y = my_rand(1, n);
        }

        mA->a[x][y] = my_rand(1, 10);
        (mA->a[1][0])++;
        c++;
    }
    return mA;
}

size_t matrix_size_1(mat1_t *mA1)
{
    size_t size = 0;
    size += sizeof(mA1->AN) * mA1->JA[0];
    size += sizeof(mA1->JA) * mA1->JA[0];
    size += sizeof(mA1->IA) * mA1->nia;
    size += sizeof(mat1_t);
    return size;
}

size_t matrix_size_2(mat2_t *mA2)
{
    size_t size = 0;
    size += sizeof(float) * mA2->m * mA2->m;
    size += sizeof(mat2_t);
    return size;
}

int time_mult_1(int n, float k)
{
    mat2_t *mA2 = matrix_cre(n, k);
    mat1_t *mA1 = matrix_change_2(mA2);
    //matrix_free_2(mA2);

    mat2_t *mB2 = matrix_cre(n, k);
    mat1_t *mB1 = matrix_change_2(mB2);
    //matrix_print_2(*mB2);
    //matrix_free_2(mB2);

    clock_t start, end;
    start =clock();

    matrix_mult_1(mA1, mB1);
    end = clock();
    //printf("check free\n");
   // matrix_free_1(mA1);
    return end - start;
}

int time_mult_2(int n, float k)
{
    mat2_t *mA2 = matrix_cre(n, k);
    mat2_t *mB2 = matrix_cre(n, k);
    clock_t start, end;
    start =clock();
    matrix_mult_2(mA2, mB2);
    end = clock();
    matrix_free_2(mB2);
    matrix_free_2(mA2);
    return end - start;

}

float mem_mult_1(int n, int k)
{
    mat2_t *mA2 = matrix_cre(n, k);
    mat1_t *mA1 = matrix_change_2(mA2);
    mA2 = matrix_change_1(mA1);
    mat2_t *mB2 = matrix_cre(n, k);
    mat1_t *mB1 = matrix_change_2(mB2);

    return (matrix_size_1(mA1) + matrix_size_1(mB1)) / 1024.0;
}

float mem_mult_2(int n, int k)
{
    mat2_t *mA2 = matrix_cre(n, k);
    mat2_t *mB2 = matrix_cre(n, k);
    return (matrix_size_2(mA2) + matrix_size_2(mB2)) / 1024.0;
}

mat1_t *matrix_input_3(void)
{
    fflush(stdin);
    int n, m;
    printf("Input n(row nummber) and m(col number): ");
    if (scanf("%d %d", &(n), &(m)) != 2 || n <=0 || m <=0)
        return NULL;
    int ptr;
    printf("Input Procent: ");
    if (scanf("%d", &ptr) != 1 )
        return NULL;
    mat2_t *mA2 = matrix_cre_1(n, m, ptr);
    mat1_t *mA1 = matrix_change_2(mA2);
    return mA1;

}

int p1(void)
{
    mat1_t *mA1, *mB1, *mC1 = NULL;
    mat2_t *mA2, *mB2, *mC2;

    printf("Input Matrix A: \n");

    mA1 = matrix_input_2();
    if (!mA1)
        return -1;

    printf("Input matrix B: \n");
    mB1 = matrix_input_2();
    if (!mB1)
        return -1;

    printf("Matrix A: \n");
    matrix_print_1(*mA1);
    mA2 = matrix_change_1(mA1);
    if (mA2->n < N_PRINT && mA2->m < N_PRINT)
        matrix_print_2(*mA2);

    printf("Matrix B: \n");
    matrix_print_1(*mB1);
    mB2 = matrix_change_1(mB1);
    if (mB2->n < N_PRINT && mB2->m < N_PRINT)
        matrix_print_2(*mB2);

    mC1 = matrix_mult_1(mA1, mB1);

    printf("Matrix C: \n");
    matrix_print_1(*mC1);
    mC2 = matrix_change_1(mC1);
    if (mC2->n < N_PRINT && mC2->m < N_PRINT)
        matrix_print_2(*mC2);

    //matrix_free_1(mA1);
    //matrix_free_1(mB1);
    //matrix_free_1(mC1);

    return 0;
}



void p2(void)
{
    int a[] = { 200, 500, 800 };
    float phtram[] = {0.1, 1.0, 5.0, 50.0, 100.0};
    int n1 = 5;
    int n = 3;
    /*int *a = calloc(n, sizeof(int));
    a[0] = 10;
    a[1] = 100;
    a[2] = 1000;*/
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("| %10s |", "N");
    for (int i = 0; i < n; i++)
        printf(" %-42d |", a[i]);
    printf("\n");

    printf("| %10s |", "Phtram");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
            printf(" %6.1f |", phtram[j]);
    }
    printf("\n");


    printf("| %10s |", "Time1:");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            float k = phtram[j];
            int t1 = time_mult_1(a[i], k);
            printf(" %6d |", t1);
        }

    }
    printf("\n");

    printf("| %10s |", "Time2:");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            float k = phtram[j];
            int t2 = time_mult_2(a[i], k);
            printf(" %6d |", t2);
        }

    }
    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    printf("| %10s |", "Mem1:");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            int k = phtram[j];
            float mem1 = mem_mult_1(a[i], k);
            printf(" %6.1f |", mem1);
        }

    }

    printf("\n");
    printf("| %10s |", "Mem2:");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            int k = phtram[j];
            float mem2 = mem_mult_2(a[i], k);
            printf(" %6.1f |", mem2);
        }

    }
    printf("\n");

    printf("\n");
    printf("Finish\n");
}



int main(void)
{
    printf("size = %d\n", (int) sizeof(int));
    printf("1. Multiplication 2 matrix\n");
    printf("2. Compare \n");
    printf("Input your Choose: ");
    int choose;
    if (scanf("%d", &choose) != 1 || (choose != 1 && choose != 2))
    {
        printf("ERRORR!!!\n");
        return -1;
    }
    if (choose == 1)
    {
        if (p1())
            printf("ERRORRRRRR!!!!!\n");
    }
    else
        p2();
    return 0;
}
