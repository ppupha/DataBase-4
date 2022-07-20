#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "in_out.h"
#include "my_math.h"
#include "define.h"

// chuyển xâu thành số dương
int str_to_int(char * str, int * result)
{
    int l = strlen(str);
    for (int i = 0; i < l; i++)
    {
        if ('0' > str[i] || str[i] > '9')
            return ERR;
        result[i] = str[i] - 48;
    }
    result[l] = -2;
    return OK;
}

// chuyển xâu thành số nguyên
int str_to_num(char * str, int *num)
{
    str = strupr(str);
    char *ps, str1[32 + 1] = "", str2[10] = "";
    int ad[32 + 1];

    ps = strchr(str, 'E');
    if (ps == NULL)
    {
        strcat(str, "E0");
        ps = strchr(str, 'E');
    }
    if (ps == str)
        return ERR_FORMAT;

    // chuyển phần cơ số
    {
        num[0] = 1;
        char s1[32 + 1] = "", s2[32 + 1] = "", *s;
        strncpy(str1, str, ps - str);
        if (str1[0] == '-' || str1[0] == '+')
        {
            if (str1[0] == '-')
                num[0] = -1;
            strcpy(str1, str1 + 1);
        }

        s = strchr(str1, '.');

        if (s == NULL)
        {
            strcat(str1, ".");
            s = strchr(str1, '.');
        }

        strncpy(s1, str1, s - str1);
        strcpy(s2, s + 1);
        if (strlen(s1) + strlen(s2) > 30 || strlen(s1) + strlen(s2) == 0)
            return ERR_RANGE_BASE;

        int l1 = strlen(s1), l2 = strlen(s2);

        for (int i = 0; i < l1; i++)
        {
            if ('0' > s1[i] || s1[i] > '9')
                return ERR;
            num[i + 1] = s1[i] - 48;
        }

        for (int i = 0; i < l2; i++)
        {
            if ('0' > s2[i] || s2[i] > '9')
                return ERR;
            num[l1 + i + 1] = s2[i] - 48;
        }
        num[l1 + l2 + 1] = -2;
        sprintf(s1, "%d", l2);
        ad[0] = -1;
        str_to_int(s1, ad + 1);
    }

    // chuyển phần mũ
    {
        num[N1] = 1;
        strcpy(str2, ps + 1);
        if (str2[0] == '-' || str2[0] == '+')
        {
            if (str2[0] == '-')
                num[N1] = -1;
            strcpy(str2, ps + 2);
        }
        int l = strlen(str2);
        if (l > 5)
            return ERR_RANGE_EXP;
        //printf("strr = %s\n", str2);
        for (int i = 0; i < l; i++)
        {
            if ('0' > str2[i] || str2[i] > '9')
                return ERR_INPUT;
            num[N1 + 1 + i] = str2[i] - 48;
        }
        if (l <= 5)
            num[N1 + 1 + l] = -2;
    }

    add_int(num + N1, ad, num + N1);
    return OK;
}

// chia hai số dương
int del(int *a, int *b, int *result, int * count)
{
    chuan_hoa(a);
    chuan_hoa(b);
    //print_int(a);
    //print_int(b);

    if (b[0] == 0)
    {
        return ERR_DEVISE_ZERO;
    }

    int lb = len(b);
    int la = len(a);
    //printf("la = %d , lb = %d \n", la, lb);
    int m[LEN];
    int boo = 0;
    *count = 0;


        // lấy l số đàu tiên để chia
    int k = 0;
    while (k < la && k < lb)
    {
        m[k] = a[k];
        k++;
    }
    m[k] = -2;

    int num_c = 0;
    int zero[2] = ZERO;
    int check_out = 0;
    int i;
    while (!check_out)
    {
        // số cuối cùng - làm tròn
        if (num_c == 31)
        {
            if (i - 1 >= 5)
            {
                int remember = 1;
                for (int j = 29; j >= 0;  j--)
                {
                    result[j] += remember;
                    remember = result[j] / 10;
                    result[j] %= 10;
                }
            }
            (*count) -=2;
            check_out = 1;
        }
        //  không phải số cuối cùng
        else
        {
            int re[LEN] = ZERO;
            //print_int(m);
            // tìm kết quả chia
            for (i = 0; i < 10 && comp_int(re, m) != 1; i++)
                mult(b, i + 1, re);
            //printf("i = %d\n", i - 1);
            if (i - 1 != 0)
                boo = 1;

            if (boo)
            {
                /*if (k == la + 1)
                    k++;
                else*/
                {
                    result[num_c] = i - 1;
                    num_c++;
                }
            }

            mult(b, i - 1, re);
            minus_int(m, re, m);

            if (comp_int(m, zero) == 0 && num_c != 31 && k >= la)
                check_out = 1;

            if (k < la && check_out == 0)
            {
                add_c(m, a[k]);
                k++;
            }
            else if (check_out == 0)
            {
                add_c(m, 0);
                (*count)++;
            }
            chuan_hoa(m);
        }

    }

    if (num_c > N1 - 2)
        num_c = N1 - 2;
    /*if (*count > N1 - 1)
        *count = N1 - 1;*/

    result[num_c] = -2;
    chuan_hoa(result);
    return OK;
}


// chia hai số nguyên
int devision(int *a, int *b, int *result)
{
    chuan_hoa(a + 1);
    chuan_hoa(b + 1);
    int count = 0;
    if (*(a + 1) == 0)
        *a = 1;
    result[0] = a[0] * b[0];

    // chia cơ số
    int rc = del(a + 1, b + 1, result + 1, &count);
    /*for (int i = 0; i < 40; i++)
        printf("%d ", *(result + i));
    printf("\n");
    printf("count = %d \n", count);*/
    if (rc != OK)
    {
        return rc;
    }
    // tính phàn mũ
    b[N1] *= -1;
    add_int( a+ N1, b + N1,
             result + N1);
    {
        int tmp[7];
        char stmp[7];
        int t = len(result + 1) - count;;
        if (t < 0)
        {
            tmp[0] = -1;
            t *= -1;
        }
        else
            tmp[0] = 1;
        sprintf(stmp, "%d", t);
        str_to_int(stmp, tmp + 1);
        //printf("len(result + 1) - count = %d\n", len(result + 1) - count);

        add_int(result + N1, tmp, result + N1);
    }
    return OK;
}

void print_num(int * a)
{
    if (len(a + N1 + 1) > 5)
    {
        printf("Error: Too Big Number\n");
        return;
    }
    if (a[0] == -1)
        printf("-");
    else
        printf("+");
    printf("0.");
    int l = len(a + 1);
    if (l == 0)
        printf("0");
    while (*(a + l) == 0 && l > 1)
        l--;
    *(a + l + 1) = -2;
    //printf("l = %d\n", l);
    print_int(a + 1);

    printf("E");
    {
        if (a[N1] == -1)
            printf("-");
        else
            printf("+");
        print_int(a + N1 + 1);
    }
    printf("\n");
}

int main(void)
{
    int rc = 0;
    char str1[MAX_LEN + 1], str2[MAX_LEN + 1];

    rc = input_strnum(str1);
    if (rc != OK)
    {
        printf("ERROR_INPUT \n");
        return rc;
    }
    int *a1 = calloc(LEN, sizeof(int));
    rc = str_to_num(str1, a1);
    if (rc == 0)
    {
        chuan_hoa(a1 + 1);
        chuan_hoa(a1 + N2 + 1);
    }
    else
    {
        printf("ERROR_INPUT \n");
        return rc;
    }

    rc = input_strnum(str2);
    if (rc != OK)
    {
        free(a1);
        printf("ERROR_INPUT \n");
        return rc;
    }
    int *a2 = calloc(LEN, sizeof(int));
    rc = str_to_num(str2, a2);
    if (rc == 0)
    {
        chuan_hoa(a2 + 1);
        chuan_hoa(a2 + N2 + 1);
    }
    else
    {
        free(a1);
        free(a2);
        printf("ERROR_INPUT \n");
        return rc;
    }
    int *result = calloc(LEN, sizeof(int));
    rc = devision(a1, a2, result);
    if (rc == OK)
    {
        printf("Result is: ");
        print_num(result);
    }
    else
        printf("ERROR_DEVISE\n");
    free(a1);
    free(a2);
    free(result);

    return rc;
}
