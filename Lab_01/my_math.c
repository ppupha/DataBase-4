#include "my_math.h"
#include <stdio.h>
#include "in_out.h"
#include "define.h"

// so sánh hai số dương
int comp_int(int *a, int *b)
{
    chuan_hoa(a);
    chuan_hoa(b);
    int la = len(a);
    int lb = len(b);
    if (la > lb)
        return 1;
    else if (la < lb)
        return -1;
    else
    {
        for (int i = 0; i < la; i++)
            if (a[i] < b[i])
                return -1;
            else if (a[i] > b[i])
                return 1;
    }
    return 0;
}

// thêm n số 0 vào đầu số dương a
int insert_0(int *a, int n)
{
    int la = len(a);
    for (int j = la; j >= 0; j--)
        a[j + n] = a[j];
    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
    }
    return 0;
}

// độ dài số dương
int len(int *a)
{
    int i = 0;
    while (a[i] != -2)
        i++;;
    return i;
}

// chuẩn hoá số nguyên
void chuan_hoa(int *a)
{
    //printf("chuan_hoa\n");
    int c = 0;
    int la = len(a);
    while (a[c] == 0)
        c++;
    for (int i = 0; i < len(a) - c; i++)
        a[i] = a[i + c];
    if (la - c == 0)
        c--;
    a[la - c] = -2;
}

// trừ hai số dương
void minus_int(int *a, int *b, int *result)
{
    chuan_hoa(a);
    chuan_hoa(b);
    int la = len(a);
    int lb = len(b);
    if (la > lb)
        insert_0(b, la - lb);
    int r = 0;
    for (int i = la - 1; i >= 0; i--)
    {
        result[i] = a[i] - b[i] - r;
        r = 0;
        if (result[i] < 0)
        {
            result[i] += 10;
            r+= 1;
        }
    }
    result[la] = -2;
    chuan_hoa(result);
}

// cộng hai số dương
void plus_int(int *a, int *b, int *result)
{
    chuan_hoa(a);
    chuan_hoa(b);

    int la = len(a);
    int lb = len(b);
    if (la > lb)
        insert_0(b, la - lb);
    else
        insert_0(a, lb - la);
    int r = 0;
    la = len(a);
    for (int i = la; i > 0; i--)
    {
        result[i] = a[i - 1] + b[i - 1] + r;
        r = (int) result[i] / 10;
        result[i] = result[i] % 10;
    }
    result[0] = r;
    result[la + 1] = -2;
    chuan_hoa(result);
}

// cộng hai số nguyên
void add_int(int *a, int *b, int *result)
{
    chuan_hoa(a + 1);
    chuan_hoa(b + 1);
    //int result[LEN];
    if (a[0] * b[0] == 1)
    {
        result[0] = a[0];
        plus_int(a + 1, b + 1, result + 1);
    }
    else
    {
        int sign = 1;
        if (comp_int(a + 1, b + 1) == -1)
            sign *= -1;

        if (sign == -1)
            minus_int(b + 1, a + 1, result + 1);
        else
            minus_int(a + 1, b + 1, result + 1);
        if (a[0] == -1)
            sign *= -1;
        result[0] = sign;
    }
    chuan_hoa(result + 1);
}

// nhân số nguyên với b
void mult(int *a, int b, int *result)
{
    chuan_hoa(a);

    int la = len(a);
    int r = 0;
    for (int i = la - 1; i >= 0; i --)
    {
        result[i + 1] = (int) (a[i] * b + r) % 10;
        r = (int) (a[i] * b + r) / 10;
    }
    result[0] = r;
    result[la + 1] = -2;
    chuan_hoa(result);

}

// thêm chữ số vào số dương
void add_c(int *a, int c)
{
    int la = len(a);
    a[la] = c;
    a[la + 1] = -2;
}

