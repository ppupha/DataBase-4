#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_LEN 128
#define ERR -1
#define OK 0
#define MAX 1000

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
    char a[MAX][MAX_LEN + 1];
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

void str_print(char *str)
{
    int l = strlen(str);
    for (int i = l -1; i  >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}

void stack_print_1(node_t head)
{
    if (head)
    {
        printf(">%p< >%s<\n", head, head->value);
        //str_print(head->value);
        stack_print_1(head->next);
    }
}

void stack_print_2(stack_2_t sta)
{
    for (int i = 0; i < sta->n; i++)
        //str_print(sta->a[i]);
        printf(">%p< >%s<\n", sta->a + i, sta->a[i]);
}

void address_print_1(node_t head)
{
    printf("Address: \n");
    node_t tmp = head;
    while (tmp)
    {
        printf(">%p< %s\n", tmp, tmp->value);
        tmp = tmp->next;
    }
}

void address_print_2(stack_2_t sta)
{
    for (int i = 0; i < sta->n; i++)
        printf(">%p<\n", sta->a[i]);
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

node_t find_node(node_t head, char *str)
{
    if (!head)
        return NULL;
    node_t tmp = head;
    while (tmp)
    {
        if (strcmp(tmp->value, str) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

node_t find_node_bef(node_t head, char *str)
{
    assert(head);
    node_t tmp = head;
    while (tmp->next)
    {
        if (strcmp(tmp->next->value, str) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

node_t get_last(node_t head)
{
    if (!head)
        return NULL;
    node_t tmp = head;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    return tmp;
}

void insert_node(node_t node1, node_t node2)
{
    node2->next = node1->next;
    node1->next = node2;
}

int stack_ins_1(stack_1_t sta, node_t new)
{

    if (!sta->head)
    {
        sta->n = 1;
        sta->head = new;
        return OK;
    }
    else if (sta->n == MAX)
    {
        printf("Stack is FULL!!!\n");
        return OK;
    }

    node_t tmp = sta->head;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    if (!tmp)
        return ERR;
    sta->n += 1;
    tmp->next = new;

    return OK;
}

int stack_ins_2(stack_2_t sta, char *str)
{
    if (sta->n == MAX)
    {
        printf("Stack is FULL!!!\n");
        return OK;
    }
    sta->n += 1;
    int k = sta->n - 1;
    sta->a[k][0] = 0;
    strcpy(sta->a[sta->n - 1], str);
    return OK;
}

int add_address_2(stack_2_t sta, char *add)
{
    sta->n++;
    strcpy(sta->a[sta->n - 1],add);
    return 0;
}

int stack_del_1(stack_1_t sta, stack_1_t stack_del)
{
    node_t tmp = sta->head;
    if (!tmp)
        return ERR;

    if (sta->n == 1)
    {
        stack_ins_1(stack_del, sta->head);
        sta->n -=1;
        sta->head = NULL;
        return OK;
    }
    while (tmp->next->next)
    {
        tmp = tmp->next;
    }
    //free(tmp->next);
    //printf(">>>%p<<<\n", tmp->next)
    stack_ins_1(stack_del, tmp->next);
    tmp->next = NULL;
    sta->n -=1;

    return OK;
}

int stack_del_2(stack_2_t sta, stack_2_t sta_del)
{
    if (sta->n == 1)
    {
        int rc = stack_ins_2(sta_del, sta->a[0]);
        sta->n = 0;
        return rc;
    }
    add_address_2(sta_del, sta->a[sta->n - 1]);
    sta->n -=1;
    return OK;
}

int menu(void)
{
    int choose;
    printf("0. Exit\n");
    printf("1. Print Stack\n");
    printf("2. Insert new\n");
    printf("3. Delete\n");

    printf("Input Your Choise\n");
    if (scanf("%d", &choose) != 1 || choose < 0 || choose > 3)
        return -1;
    return choose;
}

int main(void)
{
    stack_1_t sta1 = malloc(sizeof(stack_1_t));
    sta1->n = 0;
    sta1->head = NULL;//new_node("1");

    stack_1_t sta_del_1 = malloc(sizeof(stack_1_t));
    sta_del_1->n = 0;
    sta_del_1->head = NULL;


    stack_2_t sta2 = malloc(sizeof(struct stack_2));
    sta2->n = 0;

    stack_2_t sta_del_2 = malloc(sizeof(struct stack_2));
    sta_del_2->n = 0;

    while (1 == 1)
    {
        int ch = menu();
        switch (ch)
        {
        case 0:
        {
            printf("Finished\n");
            return 0;
        }
        case 1:
        {
            printf("\n\n\n");
            printf("n = %d\n", sta1->n);
            if (sta1->n == 0)
                printf("Stack Empty!!!\n");
            else
            {
                printf("Stack1: \n");
                stack_print_1(sta1->head);
                printf("End stack\n");

                /*printf("\n\n");
                printf("Stack2:\n");
                stack_print_2(sta2);

                printf("ENd\n");
                printf("\n");*/
            }
            if (sta_del_1->head)
            {
                printf("Address Delete:\n");
                address_print_1(sta_del_1->head);

                /*printf("\n\n\n");
                printf("Address Delete: \n");
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

            stack_ins_1(sta1, new);
            stack_ins_2(sta2, value);

            break;
        }
        case 3:
        {
            if (sta1->n == 0)
                printf("Stack Empty!!!\n");
            else
            {
                stack_del_1(sta1, sta_del_1);
                stack_del_2(sta2, sta_del_2);
            }
            break;
        }
        case 4:
        {
            FILE *f = fopen("Inp.txt", "r");
            while (!feof(f))
            {
                char value[MAX_LEN + 1];
                if (fgets(value, sizeof(value), f) != 1)
                {
                    printf("ERRR!!!");
                    break;
                }

                node_t new = new_node(value);
                if (!new)
                    return ERR;

                stack_ins_1(sta1, new);
                stack_ins_2(sta2, value);
            }
        }
        }

    }
    //stack_free_1(sta1);
    return 0;
}



/*
 *int stack_ins_1(stack_1_t sta, char *value, char *str)
{
    node_t new = new_node(value);
    if (!new)
        return ERR;
    if (!sta->head)
    {
        sta->head = new;
        return OK;
    }

    node_t tmp = find_node(sta->head, str);
    if (!tmp)
        tmp = get_last(sta->head);
    if (!tmp)
        return ERR;
    if (insert_node(tmp, new) == OK)
    {
        sta->n += 1;
        return OK;
    }
    else
        return ERR;
}

int stack_del_1(stack_1_t sta, char *str)
{
    if (strcmp(str, sta->head->value) == 0)
    {
        sta->n -= 1;
        sta->head = sta->head->next;
        if (sta->n == 0)
            return ERR;
        return OK;
    }
    node_t tmp = find_node_bef(sta->head, str);
    if (!tmp)
        return ERR;
    tmp->next = tmp->next->next;
    return OK;
}
*/
