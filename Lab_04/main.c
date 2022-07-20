#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 128
#define ERR -1
#define OK 0
#define MAX 100000
#define INPUT_FILE "inp.txt"

struct node
{
    char value[MAX_LEN + 1];
    struct node * next;
};

typedef struct node * node_t;

struct stack_1
{
    node_t head;
    int n;
};

typedef struct stack_1 * stack_1_t;

struct stack_2
{
    char ** a;
    int n;
};

typedef struct stack_2 * stack_2_t;

void stack_free_1(stack_1_t sta1)
{
    node_t tmp = sta1->head;
    node_t tmp1 = tmp->next;
    while (tmp1)
    {
        free(tmp);
        tmp = tmp1;
        tmp1 = tmp->next;
    }
    free(tmp);
    free(sta1);
}

node_t pop_del(stack_1_t sta1)
{
    if (!((sta1)->head))
        return NULL;
    if (!(sta1)->head->next)
    {
        node_t tmp = (sta1)->head;
        (sta1)->head = NULL;
        (sta1)->n = 0;
        return tmp;
    }
    node_t tmp = (sta1)->head;
    /*while (tmp->next->next)
        tmp = tmp->next;
    node_t re = tmp->next;*/
    (sta1)->n -= 1;
    (sta1)->head = tmp->next;
    tmp->next = NULL;
    return tmp;
}

node_t pop(stack_1_t sta1)
{
    if (sta1->n == 0)
        return NULL;
    int count = 0;
    node_t tmp = sta1->head;
    /*while (count < sta1->n)
        tmp = tmp->next;*/
    sta1->n -= 1;
    return tmp;
}

void push(stack_1_t sta1, node_t node)
{
    if (!((sta1)->head))
    {
        (sta1)->head = node;
        (sta1)->n = 1;
        return;
    }
    if ((sta1)->n >= MAX)
    {
        printf("Stack is Full\n");
        return;
    }
    /*
    node_t tmp = (*sta1)->head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;*/
    node->next = (sta1)->head;
    (sta1)->head = node;
    (sta1)->n += 1;
}

char *pop_arr(stack_2_t sta2)
{
    return sta2->a[sta2->n - 1];
}

void str_print(char *str)
{
    int l = strlen(str);
    for (int i = l -1; i  >= 0; i--)
        printf("%c", str[i]);
    //printf("\n");
}

void stack_print1(stack_1_t sta1)
{
    while (sta1->head)
    {
        node_t node = pop(sta1);
        printf(">%-30s< >%30p<\n", node->value, node);
    }
}

void stack_print_2(stack_2_t sta)
{
    for (int i = 0; i < sta->n; i++)
        //str_print(sta->a[i]);
        printf(">%-30s<>%30p<\n", sta->a[i], sta->a[i]);
}

void address_print_1(node_t head)
{
    printf("Address: \n");
    node_t tmp = head;
    while (tmp)
    {
        printf(">%30p<\n", tmp);
        tmp = tmp->next;
    }
}

void address_print_2(stack_2_t sta)
{
    for (int i = 0; i < sta->n; i++)
        printf(">%30p<\n", (sta->a[i]));
}

node_t new_node(char *str)
{
    node_t new = calloc(1, sizeof(struct node));
    if (!new)
        return NULL;
    strcpy(new->value, str);
    new->next = NULL;
    return new;
}

void insert_node(node_t node1, node_t node2)
{
    node2->next = node1->next;
    node1->next = node2;
}

void stack_print_1(node_t head)
{
    if (head)
    {
        printf(">%-30s< >%30p<\n", head->value, head);
        stack_print_1(head->next);
        //str_print(head->value);
    }
}

int arr_push(stack_2_t sta, char *str)
{
    if (sta->n == MAX)
    {
        printf("STACK IS FULL \n");
        return OK;
    }
    char **tmp = realloc(sta->a, (sta->n + 1) * sizeof(char *));
    if (!tmp)
        return ERR;
    sta->a = tmp;
    sta->n += 1;
    sta->a[sta->n - 1] = str;
    return OK;
}

int input_file(FILE *f, stack_1_t sta1, stack_2_t sta2)
{
   fseek(f, 0, SEEK_SET);
   char str[MAX_LEN];
   while (!feof(f))
   {
       fgets(str, sizeof(str), f);
       int l = strlen(str);
       while (str[l - 1] == '\n')
       {
           str[l - 1] = '\0';
           l -= 1;
       }

       node_t new = new_node(str);
       if (!new)
           return ERR;
       push(sta1, new);

       l = strlen(str);
       char * ins_str = malloc((l + 1) * sizeof(char));
       strcpy(ins_str,str);
       ins_str[l + 1] = 0;
       arr_push(sta2, ins_str);
   }
   return OK;
}

char *arr_pop(stack_2_t *sta)
{
    if ((*sta)->n == 0)
    {
        printf("Stack Empty---!!!\n\n\n");
        return NULL;
    }
    char **tmp;
    char *str = (*sta)->a[(*sta)->n - 1];
    if ((*sta)->n == 1)
        tmp = NULL;
    else
        tmp = realloc((*sta)->a, ((*sta)->n - 1) * sizeof(char*));

    (*sta)->a = tmp;
    (*sta)->n -=1;
    return str;
}

clock_t time_1(int n)
{
    clock_t beg, end;
    beg = clock();
    for (int k = 0; k < 10; k++)
    {
        stack_1_t sta1 = calloc(1, sizeof(stack_1_t));
        sta1->n = 0;
        for (int i = 0; i < n; i++)
        {
            node_t node = new_node("ABCDEF");
            push(sta1,node);
        }

        for (int i = 0; i < n; i++)
            pop_del(sta1);
    }
    end = clock();
    return end - beg;
}

clock_t time_2(int n)
{
    clock_t beg, end;
    stack_2_t sta2 = calloc(1, sizeof(stack_2_t));
    sta2->n = 0;
    beg = clock();
    for (int k = 0; k < 10; k++)
    {
        for (int i = 0; i < n; i++)
        {
            char value[] = "ABCDEF";
            int l = strlen(value);
            char * ins_str = malloc((l + 1) * sizeof(char));
            strcpy(ins_str,value);
            ins_str[l + 1] = 0;
            arr_push(sta2, ins_str);
        }

        for (int i = 0; i < n; i++)
            arr_pop(&sta2);

    }
    end = clock();
    return end - beg;
}

float mem_1(int n)
{
    int size = 0;
    for (int i = 0; i < n; i++)
    {
        size += sizeof(struct node);
    }
    size += sizeof(struct stack_2);
    return size / 1024.0;
}

float mem_2(int n)
{
    int size = 0;
    for (int i = 0; i < n; i++)
    {
        size += 128 + sizeof(char *);
    }

    size += sizeof(struct stack_2);
    return size / 1024.0;
}

int menu(void)
{
    int choose;
    printf("0. Exit\n");
    printf("1. Print Stack\n");
    printf("2. Insert new\n");
    printf("3. Delete\n");
    printf("4. Read from File\n");
    printf("5. Time\n");
    printf("6. Input Sentense\n");

    printf("Input Your Choise\n");
    if (scanf("%d", &choose) != 1 || choose < 0 || choose > 6)
        return -1;
    return choose;
}

int main(void)
{
    stack_1_t sta1 = calloc(1, sizeof(stack_1_t));
    sta1->n = 0;

    stack_1_t sta_del_1 = calloc(1, sizeof(stack_1_t));

    stack_2_t sta2 = calloc(1, sizeof(stack_2_t));
    sta2->n = 0;

    stack_2_t sta_del_2 = calloc(1, sizeof(stack_2_t));

    while (1 == 1)
    {
        int ch = menu();
        switch (ch)
        {
        case -1:
            printf("ERRROR INPUT\n");

        case 0:
            {
                printf("Finished\n");
                return 0;
            }

        case 1:
            {
                printf("\nn = %d\n", sta1->n);
                if (sta1->n == 0)
                    printf("Stack Empty!!!\n");
                else
                {
                    printf("Stack1: \n");
                    stack_print_1(sta1->head);
                    printf("End stack\n");

                    printf("\n\n");
                    printf("Stack2:\n");
                    printf("n = %d\n", sta2->n);
                    stack_print_2(sta2);

                    printf("ENd\n");
                    printf("\n");
                }
                if (sta_del_1->head)
                {
                    printf("Address Delete:\n");
                    address_print_1(sta_del_1->head);

                    printf("\n\n\n");
                    /*printf("Address Delete: \n");
                    address_print_2(sta_del_2);*/
                }
                printf("\n\n\n");

                break;
            }

        case 2:
            {
                char value[MAX_LEN + 1];
                printf("Insert Value (String) to Insert: \n");
                if (scanf("%s", value) != 1)
                {
                    printf("ERRR!!!");
                    break;
                }

                node_t new = new_node(value);
                if (!new)
                    return ERR;
                push(sta1, new);

                int l = strlen(value);
                char * ins_str = malloc((l + 1) * sizeof(char));
                strcpy(ins_str,value);
                ins_str[l + 1] = 0;

                arr_push(sta2, ins_str);

                break;
            }

        case 3:
            {
                node_t node = pop_del(sta1);
                if (!node)
                    printf("Stack is Empty\n");
                else
                    push(sta_del_1, node);

                char *str = arr_pop(&sta2);
                if (str)
                    arr_push(sta_del_2, str);
                break;
            }

        case 4:
            {
                FILE *f;
                f = fopen("E:/Cau_Truc_Du_Lieu/Lab_04/inp1.txt", "r");
                if (f != NULL)
                    printf("STack\n");

                input_file(f, sta1, sta2);
                break;
            }

        case 5:
            {
                sta1->head = NULL;
                sta1->n = 0;
                sta2->a = NULL;
                sta2->n = 0;

                /*FILE *f;
                f = fopen("E:/Cau_Truc_Du_Lieu/Lab_04/inp.txt", "r");
                if (f != NULL)
                    printf("STack\n");
                input_file(f, &sta1, sta2);*/

                int a[] = { 100, 300, 500, 700, 900, 1000, 2000, 3000, 4000, 5000, 7000, 8000, 9000, 10000 };
                int n = sizeof(a) / sizeof(a[0]);
                int time[2][n];
                printf("%7s", "N=:");
                for (int i = 0; i < n; i++)
                    printf("|%7d", a[i]);
                printf("\n");

                printf("%7s", "Time1:");
                for (int i = 0; i < n; i++)
                {
                    time[0][i] = time_1(a[i]);
                    printf("|%7d", time[0][i]);
                }
                printf("\n");

                printf("%7s", "Time2:");
                for (int i = 0; i < n; i++)
                {
                    time[1][i] = time_2(a[i]);
                    printf("|%7d", time[1][i]);
                }

                printf("\n");

                printf("%7s", "Aver1:");
                for (int i = 0; i < n; i++)
                {
                    printf("|%7.3f", (float) time[0][i] / a[i]);
                }

                printf("\n");
                printf("%7s", "Aver2:");
                for (int i = 0; i < n; i++)
                {
                    printf("|%7.3f", (float) time[1][i] / a[i]);
                }

                printf("\n");

                /*for (int i = 0; i < n; i++)
                {
                    float mem1 = mem_1(a[i]);
                    printf("|%7.2f", mem1);
                }
                printf("\n");

                for (int i = 0; i < n; i++)
                {
                    float mem2 = mem_2(a[i]);
                    printf("|%7.2f", mem2);
                }
                printf("\n");*/

                /*int mem1 = mem_1(sta1);
                int mem2 = mem_2(sta2);*/

                /*printf("Mem1:  %8.3f\n", mem1 / 1024.0);
                printf("Mem2:  %8.3f\n", mem2 / 1024.0);*/

                break;
            }

        case 6:
        {
            char str[10000];
            printf("Input Sentense:\n");
            fgets(str, sizeof(str), stdin);
            fgets(str, sizeof(str), stdin);
            int i = 0;
            int l = strlen(str);

            if (str[l - 1] == '\n')
                str[l - 1] = 0;
            l -= 1;
            printf("str = [%s]\n", str);
            while (i < l)
            {
                while (i < l && str[i] == ' ')
                    i++;
                int beg = i;
                while (i < l && str[i] != ' ')
                    i++;
                int end = i;
                if (beg != end)
                {
                    char value[1000];
                    memset(value, '\0', sizeof(value));
                    strncpy(value, str + beg, end - beg);
                    node_t new = new_node(value);
                    if (!new)
                        return ERR;
                    push(sta1, new);

                    int l = strlen(value);
                    char * ins_str = malloc((l + 1) * sizeof(char));
                    strcpy(ins_str,value);
                    ins_str[l + 1] = 0;

                    arr_push(sta2, ins_str);
                }
                i++;
            }
            break;
        }

        }

    }
    //stack_free_1(sta1);
    return 0;
}
