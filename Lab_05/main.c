#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define TIME 100

float t_work[2] = {0, 0};
float t_in[2] = {0, 0};
float t_mophong = 0;
float t_free = 0;
int node_in[] = {0, 0};
int node_out[2] = {0, 0};
int node_oa = 0;

float t1[2] = {0.0, 1.0};
float t2[2] = {0.0, 3.0};
float t3[2] = {1.0, 5.0};
float t4[2] = {0.0, 1.0};

int len_q[2] = {0, 0};
float sum_len_q[2] = {0.0, 0.0};
int n = 0;

#define MAX 1000
#define MAX_N 10000000

struct node
{
    int type;
    float tin;
    float t1;
    float t2;
    float tout;
    struct node *next;
};

typedef struct node node_t;

struct queue
{
    node_t *front;
    node_t *rear;
};

typedef struct queue queue_t;

struct element
{
    int type;
    float tin;
    float t1;
    float t2;
    float tout;
};

typedef struct element element_t;

struct queue_arr
{
    struct element **a;
    int left;
    int right;
};

typedef struct queue_arr queue_arr_t;

node_t *pop(queue_t *q)
{
    if (!q->front)
        return NULL;
    node_t *node = q->front;
    q->front = node->next;
    return node;
}

void push(queue_t *q, node_t *node)
{
    if (!q->front)
    {
        q->rear = node;
        q->front = node;
    }
    else
    {
        (q->rear)->next = node;
        q->rear = node;
    }
}

element_t *pop_arr(queue_arr_t *q)
{
    if (q->right < q->left)
        return NULL;
    return q->a[(q->right)--];
}

void push_arr(queue_arr_t *q, element_t *ele)
{
    q->a[++(q->right)] = ele;
}


float my_rand(float a, float b)
{
    float rc = a + (rand() / (float) RAND_MAX) * (b - a);
    return (float) rc;
}

element_t *new_element(int now, int type)
{
    element_t *node = calloc(1, sizeof(element_t));
    node->type = type;
    if (type == 1)
    {
        node->t1 = my_rand(t1[0], t1[1]);
        node->t2 = my_rand(t3[0], t3[1]);
    }
    else
    {
        node->t1 = my_rand(t2[0], t2[1]);
        node->t2 = my_rand(t4[0], t4[1]);
    }
    node->tin = now + node->t1;
    return node;
}

node_t *node_new(float now, int type)
{
    node_t *node = calloc(1, sizeof(node_t));
    node->type = type;
    if (type == 1)
    {
        node->t1 = my_rand(t1[0], t1[1]);
        node->t2 = my_rand(t3[0], t3[1]);
    }
    else
    {
        node->t1 = my_rand(t2[0], t2[1]);
        node->t2 = my_rand(t4[0], t4[1]);
    }
    node->tin = now + node->t1;
    return node;
}

void node_print(node_t *node)
{
    printf("%d %4.2f %4.2f %4.2f %4.2f\n", node->type, node->tin, node->t1, node->t2, node->tout);
    //printf("%d %4.2f %4.2f\n", node->type, node->tin - node->tcre, node->tout - node->tin);

}

/*
int process(queue_t *q)
{
    int count = 1;
    node_t *node = pop(q);
    node_print(node);
    node_t *new_node = node_new(q->rear->tin, node->type);
    push(q, new_node);
    while (node && q->front && (q->front)->tin <= node->tout)
    {
        count++;
        node = pop(q);
        node_print(node);
        node_t *new_node = node_new(q->rear->tin, node->type);
        push(q, new_node);
    }
    return count;
}*/

int time_input(void)
{
    float time[2];


    printf("Time has form [a..b] (b > a)\n");
    printf("Input Time T1 (1st Type):");
    if (scanf("%f %f", time, time + 1) != 2 || time[0] < 0 || time[1] <= 0 || time[1] <= time[0])
        return -1;
    t1[0] = time[0];
    t1[1] = time[1];

    printf("Input Time T2 (1st Type):");
    if (scanf("%f %f", time, time + 1) != 2 || time[0] < 0 || time[1] <= 0 || time[1] <= time[0])
        return -1;
    t2[0] = time[0];
    t2[1] = time[1];

    printf("Input Time T3 (1st Type):");
    if (scanf("%f %f", time, time + 1) != 2 || time[0] < 0 || time[1] <= 0 || time[1] <= time[0])
        return -1;
    t3[0] = time[0];
    t3[1] = time[1];

    printf("Input Time T4 (1st Type):");
    if (scanf("%f %f", time, time + 1) != 2 || time[0] < 0 || time[1] <= 0 || time[1] <= time[0])
        return -1;
    t4[0] = time[0];
    t4[1] = time[1];
    return 0;
}

void queue_print(queue_t *q)
{
    node_t *node = q->front;
    if (!node)
        printf("Empty\n");
    else
        printf("check\n");
    while (node)
    {
        node_print(node);
        node = node->next;
    }
}

int process(void)
{
    queue_t *q1, *q2;
    float tnow = 0;
    q1 = calloc(1, sizeof(queue_t));
    q2 = calloc(1, sizeof(queue_t));

    for (int i = 0; i < 5; i++)
    {
        node_t *node = node_new(tnow, 1);
        push(q1, node);
        tnow = node->tin;
    }

    for (int i = 0; i < 5; i++)
    {
        node_t *node = node_new(tnow, 2);
        push(q2, node);
        tnow = node->tin;
    }

    /*queue_print(q1);
    queue_print(q2);*/
    queue_t *q = NULL;



    float t_now = 0;

    printf("process\n");
    int k = 0;
    while (k < MAX)
    {


        if ((q1->front)->tin <= (q2->front)->tin)
        {
            k++;
            q = q1;
        }
        else
        {
            q = q2;
        }

        node_t *node = pop(q);
        node_t *new_node = node_new(q->rear->tin, node->type);
        push(q, new_node);
        if (node->tin > t_now)
        {
            t_free += (node->tin - t_now);
            //printf("--------------------------------------------------------------%4.2f\n", t_free);
            t_now = node->tin + node->t2;
        }
        else
        {
            t_now += node->t2;
        }
        node->tout = t_now;
        t_work[node->type - 1] += node->t2;
        t_in[node->type - 1] += node->t1;
        node_out[node->type - 1] += 1;

        node_print(node);

        while (k < MAX && node && q->front && (q->front)->tin <= t_now && (q->front)->tin <= node->tout)
        {
            node = pop(q);
            node_t *new_node = node_new(q->rear->tin, node->type);
            push(q, new_node);
            if (node->type == 1)
                k++;
            t_now += node->t2;
            node->tout = t_now;
            t_work[node->type - 1] += node->t2;
            t_in[node->type - 1] += node->t1;
            node_out[node->type - 1] += 1;

            node_print(node);
            if (k % 100 == 0 && (int) k / 100 != n)
            {
                len_q[0] = 0;
                len_q[1] = 0;
                queue_t *q = q1;
                node_t *tmp = q->front;
                while (tmp->tin <= t_now)
                {
                    len_q[tmp->type - 1]++;
                    if (tmp->next == NULL)
                    {
                        node_t *new_node = node_new(q->rear->tin, tmp->type);
                        push(q, new_node);
                    }
                    tmp = tmp->next;
                }

                q = q2;
                tmp = q->front;
                while (tmp->tin <= t_now)
                {
                    len_q[tmp->type - 1]++;
                    if (tmp->next == NULL)
                    {
                        node_t *new_node = node_new(q->rear->tin, tmp->type);
                        push(q, new_node);
                    }
                    tmp = tmp->next;
                }

                sum_len_q[0] += len_q[0];
                sum_len_q[1] += len_q[1];
                n = k / 100;
                printf("\n\nn = %d\n", n);
                printf("T now = %4.2f\n", t_now);
                printf("T free = %4.2f\n", t_free);
                printf("%-20s = %4.2f\n", "Average len 1s Type", (float) sum_len_q[0] / n);
                printf("%-20s = %4.2f\n", "Average len 2nd Type", (float) sum_len_q[1] / n);
                printf("%-20s = %d\n", "Len 1st Type", (int) len_q[0]);
                printf("%-20s = %d\n\n", "Len 2nd Type", (int) len_q[1]);


            }

        }
        if (node_out[1] - node_out[0] > 10000)
            return 0;
    }



    node_in[0] = node_out[0];
    node_in[1] = node_out[1];

    q = q1;
    while(1)
    {
        node_t *node = pop(q);
        node_t *new_node = node_new(q->rear->tin, node->type);
        push(q, new_node);
        if (node->tin <= t_now)
        {
            node_in[node->type - 1]++;
            t_in[node->type - 1] += node->t1;
        }
        else
            break;
    }

    q = q2;
    while(1)
    {
        node_t *node = pop(q);
        node_t *new_node = node_new(q->rear->tin, node->type);
        push(q, new_node);
        if (node->tin <= t_now)
        {
            node_in[node->type - 1]++;
            t_in[node->type - 1]+= node->t1;
        }
        else
            break;
    }
    float sum_t_in = t_in[0] + t_in[1];
    int sum_node_in = node_in[0] + node_in[1];
    int sum_node_out = node_out[0] + node_out[1];
    float sum_t_work = t_work[0] + t_work[1];
    float t_oa = node_out[0] * (t3[1] - t3[0]) / 2 + node_out[1] * (t4[1] - t4[0]) / 2;
    if (sum_t_work < t_in[0])
        t_mophong = t_in[0];
    else
        t_mophong = sum_t_work;

    t_mophong = t_in[0];

        float time_ave1 = (t1[1] + t1[0]) / 2.0;
    float time_ave2 = (t2[1] + t2[0]) / 2.0;
    float node_cal = t_mophong / time_ave1 + t_mophong / time_ave2;
    float diff_node = fabs(sum_node_in - node_cal) / node_cal * 100;
    float diff_time = fabs(t_mophong - (sum_t_work + t_free)) / (sum_t_work + t_free) * 100;

    printf("\n\nResult: \n\n");

    printf("%15s = %4.2f\n", "Finish Time", t_now);
    printf("%15s = %d\n", "App 1st Type", k);
    printf("%15s = %4.2f %4.2f\n", "OA Working Time", t_work[0], t_work[1]);
    printf("%15s = %4.2f\n", "Sum Work Time", sum_t_work);
    printf("%15s = %4.2f %4.2f\n", "Time in", t_in[0], t_in[1]);
    printf("%15s = %4.2f\n", "simulation time", t_now);
    //printf("%15s = %4.2f\n", "t_oa", t_oa);
    printf("%15s = %4.2f\n", "Free time OA", t_free);
    printf("%15s = %d %d\n", "App in", node_in[0], node_in[1]);

    printf("%15s = %d\n", "Sum app in", sum_node_in);

    printf("%15s = %d %d\n", "App out", node_out[0], node_out[1]);

    //printf("%15s = %4.2f\n", "Sum app in cal", node_cal);

    printf("\n\nCheck:\n");

    printf("%15s = %4.2f\n", "Diff_app", diff_node);
    printf("%15s = %4.2f\n", "Diff_time", diff_time);
    return 0;
}

clock_t time_queue_list(int n)
{
    queue_t *q = calloc(1, sizeof(queue_t));
    clock_t start, end;
    start = clock();
    for (int k = 0; k < TIME; k++)
    {
        for (int i = 0; i < n; i++)
        {
            node_t *new = node_new(0, 1);
            push(q, new);
        }
        for (int i = 0; i < n; i++)
        {
            pop(q);
        }
    }
    end = clock();
    return end - start;
}

clock_t time_queue_arr(int n)
{
    queue_arr_t *q = calloc(1, sizeof(queue_arr_t));
    q->a = calloc(n, sizeof(element_t *));
    q->left = 0;
    q->right = 0;

    clock_t start, end;
    start = clock();
    for (int k = 0; k < TIME; k++)
    {
        for (int i = 0; i< n; i++)
        {
            element_t *new = new_element(0, 1);
            push_arr(q, new);
        }
        for (int i = 0; i < n; i++)
        {
            pop_arr(q);
        }
    }
    end = clock();

    return end - start;
}

void time_compare(void)
{
    int a[] = { 100, 300, 500, 700, 1000, 3000, 5000, 7000, 10000,  20000, 30000};
    int n = sizeof(a) / sizeof(a[0]);
    char format[] = "%10d|";
    char float_format[] = "%10.4f|";

    printf("%15s|", "N = ");
    for (int i = 0; i < n; i++)
        printf(format, a[i]);
    printf("\n");

    int time[2][n];

    printf("%15s|", "Link List");
    for (int i = 0; i < n; i++)
    {
        time[0][i] = (int) time_queue_list(a[i]);
        printf(format, time[0][i]);
    }
    printf("\n");

    printf("%15s|", "Array");
    for (int i = 0; i < n; i++)
    {
        time[1][i] = (int) time_queue_list(a[i]);
        printf(format, time[1][i]);
    }
    printf("\n");

    printf("%15s|", "Aver (List)");
    for (int i = 0; i < n; i++)
    {
        printf(float_format, (float) time[0][i] / a[i]);
    }
    printf("\n");

    printf("%15s|", "Aver (Array)");
    for (int i = 0; i < n; i++)
    {
        printf(float_format, (float) time[1][i] / a[i]);
    }
    printf("\n");

}

int main(void)
{
    int choise = -1;

    printf("T1 = [%4.2f..%4.2f]\n", t1[0], t1[1]);
    printf("T2 = [%4.2f..%4.2f]\n", t2[0], t2[1]);
    printf("T3 = [%4.2f..%4.2f]\n", t3[0], t3[1]);
    printf("T4 = [%4.2f..%4.2f]\n", t4[0], t4[1]);

    printf("Change Time? [No - 0 / Yes - Else]\n");
    if (scanf("%d", &choise) != 1)
        printf("ERROR INPUT!!!!!\n");
    else
    {
        if (choise != 0)
        {
            choise = time_input();
            printf("T1 = [%4.2f..%4.2f]\n", t1[0], t1[1]);
            printf("T2 = [%4.2f..%4.2f]\n", t2[0], t2[1]);
            printf("T3 = [%4.2f..%4.2f]\n", t3[0], t3[1]);
            printf("T4 = [%4.2f..%4.2f]\n", t4[0], t4[1]);
        }

        if (choise == 0)
            process();
        else
            printf("ERRORR INPUT!!!!\n");
    }
    time_compare();
    return choise;
}
