#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16
#define OK 0
#define ERR_IO -1
#define ERR_CMD -2
#define ERR_RANGE -3

/**
 \fn int is_separator(char ch)
 \brief check is ch a space
 \param [in] ch
 \return check if is ch a word
 */

int is_separator(char ch)
{
    if (ch == ' ' || ch == '\n')
        return 1;
    return 0;
}
/**
 \fn int get_word_pos(const char *s, int *ibeg, int *iend)
 \brief get the beginning and ending position of word
 \param [in] s a pointer to stirng
 \param [out] ibeg beginning position of a word
 \param [out] iend ending position of a word
 \return can get word or not
 */
int get_word_pos(const char *s, int *ibeg, int *iend)
{
    int i = *ibeg;
    while (s[i] && is_separator(s[i]))
        i++;
    if (s[i])
    {
        *ibeg = i;
        while (s[i] && !is_separator(s[i]))
            i++;
        *iend = i - 1;
        return 1;
    }
    return 0;
}
/**
 \fn int divide(const char *s, char a[][MAX_WORD_LEN + 1], int *n)
 \brief assign words of string s to array
 \param [in] s a pointer to string
 \param [out] a a pointer to array
 \param [out] n number of elements of array
 \return error code
 */
int divide(const char *s, char a[][MAX_WORD_LEN + 1], int *n)
{
    int ibeg = 0, iend = 0, rc =OK;
    *n = 0;
    while (get_word_pos(s, &ibeg, &iend) && rc == OK)
    {
        memset(a[*n], '\0', MAX_WORD_LEN + 1);
        strncpy(a[*n], s + ibeg, iend - ibeg + 1);
        if (iend - ibeg + 1 > MAX_WORD_LEN)
            rc = ERR_IO;
        ibeg = iend + 1;
        (*n)++;
    }
    return rc;
}
/**
 \fn void sort_by_alpha(char a[][MAX_WORD_LEN + 1], int n)
 \brief sort words in array by alphabet
 \param [out] a array after sort
 \param [int] n number of elements of array
 */
int sort_by_alpha(char a[][MAX_WORD_LEN + 1], int n)
{
    if (n <= 0)
        return ERR_RANGE;
    char c[MAX_WORD_LEN + 1];
    int min_j;
    for (int i = 0; i < n - 1; i++)
    {
        min_j = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(a[min_j], a[j]) > 0)
                min_j = j;
        }
        if (min_j != i)
        {
            strcpy(c, a[min_j]);
            strcpy(a[min_j], a[i]);
            strcpy(a[i], c);
        }
    }
    return OK;
}
/*
int sort_by_alpha_as(char a[][MAX_WORD_LEN + 1], int n)
{
    assert(a != NULL);
    assert(n > 0);
    char c[MAX_WORD_LEN + 1];
    int min_j;
    for (int i = 0; i < n - 1; i++)
    {
        min_j = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(a[min_j], a[j]) > 0)
                min_j = j;
        }
        if (min_j != i)
        {
            strcpy(c, a[min_j]);
            strcpy(a[min_j], a[i]);
            strcpy(a[i], c);
        }
    }
    return OK;
}*/
int is_equal(char a[][MAX_WORD_LEN + 1], char b[][MAX_WORD_LEN + 1],int n)
{
    for (int i = 0; i < n; i++)
        if (strcmp(a[i], b[i]) != 0)
            return 0;
    return 1;
}
void test_sort_by_alpha(void)
{
    // sort array with 1 element
    {
        char a[][MAX_WORD_LEN + 1] = {"abc"};
        char b[][MAX_WORD_LEN + 1] = {"abc"};
        int rc = sort_by_alpha(a, sizeof(a) / sizeof(a[0]));
        printf("sort array a contain 1 elements: ");
        if (rc == OK && is_equal(a, b, 1))
            printf("OK\n");
        else
            printf("FAIL\n");
    }

    // sort array with 3 elements
    {
        char a[][MAX_WORD_LEN + 1] = {"a", "c", "b"};
        char b[][MAX_WORD_LEN + 1] = {"a", "b", "c"};
        int rc = sort_by_alpha(a, sizeof(a) / sizeof(a[0]));
        printf("sort array a contain 3 elements: ");
        if (rc == OK && is_equal(a, b, 3))
            printf("OK\n");
        else
            printf("FAIL\n");
    }
    //sort array with 5 elements was sorted
    {
        char a[][MAX_WORD_LEN + 1] = {"a", "b", "c", "d", "e"};
        char b[][MAX_WORD_LEN + 1] = {"a", "b", "c", "d", "e"};
        int rc = sort_by_alpha(a, sizeof(a) / sizeof(a[0]));
        printf("sort array a contain 5 elements was sorted: ");
        if (rc == OK && is_equal(a, b, 5))
            printf("OK\n");
        else
            printf("FAIL\n");
    }
    //sort array empty
    {
        int rc = sort_by_alpha(NULL, 0);
        printf("sort array a empty: ");
        if (rc == ERR_RANGE)
            printf("OK\n");
        else
            printf("FAIL\n");
    }

}
/**
 \fn void print_on_screen(const char a[][MAX_WORD_LEN + 1], int n)
 \brief print words in array on screen
 \param [int] a array of words
 \param [int] n number of elements of array
 */
void print_on_screen(const char a[][MAX_WORD_LEN + 1], int n)
{
    for (int i = 0; i < n; i++)
        printf("%s ", a[i]);
    printf("\n");
}
int main(int argc, char *argv[])
{
    char s[MAX_STR_LEN + 1];
    char a[MAX_STR_LEN][MAX_WORD_LEN + 1];
    int rc = OK, n;
    FILE *f;
    if (argc != 2)
    {
        rc = ERR_CMD;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            if (!fgets(s, MAX_STR_LEN + 1, f))
                rc = ERR_IO;
            if (rc == OK)
                rc = divide(s, a, &n);

            if (rc == OK)
            {
                printf("string in file :\n");
                print_on_screen(a, n);
                sort_by_alpha(a, n);
                printf("string after sort: \n");
                print_on_screen(a, n);

            }
        }
    }
    test_sort_by_alpha();
    return rc;
}
