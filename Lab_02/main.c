#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN_MARK 50
#define MAX_LEN_COUNTRY 50
#define MAX_LEN_COLOR 10
#define OK 0
#define MAX 70000
#define ERR -1;

int car_id = 0;
int count_for = 0;

struct old_car
{
    int year;
    int miles;
    int num_repairs;
    int num_owners;
};

union car_status
{
    int guarantee;
    struct old_car detail;
};

struct car_infor
{
    int id;
    char mark[MAX_LEN_MARK];
    char country[MAX_LEN_COUNTRY];
    int price;
    char color[MAX_LEN_COLOR];
    int new;
    union car_status status;
};

void title_print(void)
{
    for (int i = 0; i < 155; i++)
        printf("-");
    printf("\n");
    printf("| %2s | %-20s | %-20s | %10s | %10s | %10s | %10s | %10s | %10s | %10s | %10s |\n", "Id", "Mark", "Country", "Price", "Color", "Status", "Guarantee", "Year", "Miles", "NRepair", "NOwner");
    for (int i = 0; i < 155; i++)
        printf("-");
    printf("\n");
}

void car_arr_resize(struct car_infor *** car, int * n, int new_n)
{
    struct car_infor ** tmp = realloc(*car, new_n);
    if (!tmp)
        printf("ERROR---------------------\n");
    *car = tmp;
    *n = new_n;
}

void car_free(struct car_infor ** car, int n)
{
    for (int i = 0; i < n; i++)
        free(car[i]);
    //free(car);
}

void car_print(struct car_infor car)
{
    printf("| %03d | %-20s | %-20s | %10d | %-10s |", car.id, car.mark, car.country, car.price, car.color);
    if (car.new)
    {
        printf(" %10s |", "New");
        printf(" %10d |", car.status.guarantee);
        printf(" %10s | %10s | %10s | %10s |", "-", "-", "-", "-");
    }

    else
    {
        printf(" %10s | %10s |", "Old", "-");
        printf(" %10d | %10d | %10d | %10d |", car.status.detail.year, car.status.detail.miles, car.status.detail.num_repairs, car.status.detail.num_owners);
    }
    printf("\n");
    for (int i = 0; i < 155; i++)
        printf("-");
    printf("\n");
}

void car_arr_print(struct car_infor ** car_arr, int n)
{
    title_print();
    for (int i = 0; i < n; i++)
        car_print(*(car_arr[i]));
    printf("\n");
}

void str_input(char * str, FILE *f, int size)
{
    if (f == stdin)
       fflush(f);
    fgets(str, size, f);
    int len = strlen(str);
    if (str[len - 1] == '\n')
    {
        len--;
        str[len] = 0;
    }
}

int int_input(FILE *f, int * n)
{
    if (f == stdin)
        fflush(f);
    char tmp[50];
    tmp[0] = 0;
    str_input(tmp, f, sizeof(tmp));
    for (int i = 0; i < strlen(tmp); i++)
        if (!(tmp[i] <= '9' && tmp[i] >= '0'))
            return 0;
    *n = atoi(tmp);
    return 1;
}

int car_input(struct car_infor **car_infor, FILE *f)
{
    struct car_infor * car = calloc(1, sizeof(struct car_infor));
    car->id = car_id;
    fflush(stdin);
    car_id++;
    printf("Input Mark: ");
    str_input(car->mark, f, sizeof(car->mark));
    printf("Input Country: ");
    str_input(car->country, f, sizeof(car->mark));
    printf("Input price: ");
    if (int_input(f, &(car->price)) != 1 || (car->price) < 0)
    {
        printf("ERROR INPUT");
        return ERR;
    }
    printf("Input Color: ");
    str_input(car->color, f, sizeof(car->color));
    printf("Input Car_Status [0 - OLD/ 1 - NEW]: ");
    if (int_input(f, &(car->new)) != 1 || (car->new != 0 && car->new != 1))
    {
        printf("ERROR\n");
        return ERR;
    }
    if (car->new)
    {
        printf("Input Guarantee: ");
        if (int_input(f, &((car->status).guarantee)) != 1 || (car->status).guarantee < 0)
        {
            printf("ERROR\n");
            return ERR;
        }
    }
    else
    {
        printf("Input Year: ");
        if (int_input(f, &((car->status).detail.year)) != 1)
        {
            printf("ERROR\n");
            return ERR;
        }
        printf("Input Miles: ");
        if (int_input(f, &((car->status).detail.miles)) != 1|| (car->status).detail.miles < 0)
        {
            printf("ERROR\n");
            return ERR;
        }
        printf("Input Numbrer Repairs: ");
        if (int_input(f, &((car->status).detail.num_repairs)) != 1 || (car->status).detail.num_repairs < 0)
        {
            printf("ERROR\n");
            return ERR;
        }
        printf("Input Number owners: ");
        if (int_input(f, &((car->status).detail.num_owners)) != 1 || (car->status).detail.num_owners < 0)
        {
            printf("ERROR\n");
            return ERR;
        }
    }
    *car_infor = car;
    return OK;
}

struct car_infor * car_input_file(FILE *f)
{
    struct car_infor * car = malloc(sizeof(struct car_infor));
    car->id = car_id;
    car_id++;
    char tmp[50];
    str_input(car->mark, f, sizeof(car->mark));
    str_input(car->country, f, sizeof(car->mark));
    int_input(f, &(car->price));
    str_input(car->color, f, sizeof(car->color));
    int_input(f, &(car->new));
    if (car->new)
    {
        int_input(f, &((car->status).guarantee));
    }
    else
    {
        int_input(f, &((car->status).detail.year));
        int_input(f, &((car->status).detail.miles));
        int_input(f, &((car->status).detail.num_repairs));
        int_input(f, &((car->status).detail.num_owners));
    }
    str_input(tmp, f, sizeof(tmp));

    return car;
}

int menu_field(void)
{
    printf("Choose a number:\n");
    printf("0. Id\n");
    printf("1. Mark\n");
    printf("2. Country\n");
    printf("3. Price\n");
    printf("4. Color\n");
    printf("5. Status\n");
    printf("6. Guarantee\n");
    printf("7. Year\n");
    printf("8. Miles\n");
    printf("9. Number Repairs\n");
    printf("10. Number owners\n");
    printf("Input Your Choise: ");
    int i;
    if (int_input(stdin, &i) == 1 && i >= 0 && i < 11)
        return i;
    else
        return -1;
}

int menu(int beg, int end)
{
    fflush(stdin);
    int count = 0;
    while (count < 5)
    {
        printf("\n\n\n");
        printf("0. Exit\n");
        printf("1. Print infor of all car\n");
        printf("2. Insert New Car\n");
        printf("3. Delete Car\n");
        printf("4. Find Car by Fields\n");
        printf("5. Sort by Field\n");
        printf("6. Find and print result\n");
        printf("7. Sort by Key( Price )\n");
        printf("8. Sort by Price\n");
        printf("9. Sort Time \n");
        printf("Input Your Choise: ");
        int i;
        if (int_input(stdin, &i) != 1 || i < beg || i > end)
        {
            printf("Wrong Input !!!\n");
            count++;
        }
        else
        {
            return i;
        }
    }
    return -1;
}

int arr_str_cmp(char s1[10][50], char s2[10][50], int n)
{
    for (int i = 0; i < n; i++)
        if (strcmp(s1[i], s2[i]) != 0)
            return 0;
    return 1;
}

void int_to_str(int i, char str[50])
{
    sprintf(str, "%d", i);
}

int arr_car_input_file(struct car_infor * * * car_arr, int *n, FILE *f)
{
    *n
            = 0;
    *car_arr = calloc(MAX, sizeof(struct car_infor *));
    while (!feof(f))
    {
        /*struct car_infor ** tmp = calloc(*n + 1, sizeof(struct car_infor *));
        *car_arr = tmp;*/
        (*car_arr)[*n] = car_input_file(f);
        (*n)++;
    }
    return OK;
}

int car_insert(struct car_infor *** car_arr, int *n)
{
    //car_arr_resize(car_arr, n, *n + 1);
    int rc = car_input(*car_arr + *n, stdin);
    if (rc == OK)
        (*n)++;
    else
        car_id--;
    return rc;
}

void find_field_infor(struct car_infor car, int field, char * str)
{
    switch (field)
    {
        case 0: int_to_str(car.id, str);
            return;
        case 1: strcpy(str, car.mark);
                return;
        case 2: strcpy(str, car.country);
            return;
        case 3: int_to_str(car.price, str);
            return;
        case 4: strcpy(str, car.color);
            return;
        case 5: int_to_str(car.new, str);
            return;
        case 6:
            if (car.new == 0)
                int_to_str(0, str);
            else
                int_to_str(car.status.guarantee, str);
            return;
        case 7:
            if (car.new == 1)
                int_to_str(0, str);
            else
                int_to_str(car.status.detail.year, str);
            return;
        case 8:
            if (car.new == 1)
                int_to_str(0, str);
            else
                int_to_str(car.status.detail.miles, str);
            return;
        case 9:
            if (car.new == 1)
                int_to_str(0, str);
            else
                int_to_str(car.status.detail.num_repairs, str);
            return;
        case 10:
            if (car.new == 1)
                int_to_str(0, str);
            else
                int_to_str(car.status.detail.num_owners, str);
            return;
    }
}

void find_arr_field(struct car_infor car, char result[][50], int * field, int n)
{
    for (int i = 0; i < n; i++)
    {
        char s[50];
        find_field_infor(car, field[i], s);
        strcpy(result[i], s);
    }
}

void car_find(struct car_infor ** car, int beg, int end,  int * result, int *count)
{
    *count = 0;
    int field[10];
    int num = 0;
    char infor[10][50];
    printf("Input Number of field: ");
    if (int_input(stdin, &num) != 1 || num < 1 || num > 9)
    {
        printf("ERROR INPUT\n");
        return;
    }
    for (int i = 0; i < num; i++)
    {
        field[i] = menu_field();
        printf("Input Infor: ");
        str_input(infor[i], stdin, sizeof(infor[i]));
    }

    for (int i = beg; i < end; i ++)
    {
        char tmp[10][50];
        find_arr_field(*car[i], tmp, field, num);
        if (arr_str_cmp(tmp, infor, num))
        {
            result[*count] = (*car[i]).id;
            (*count)++;
        }
    }
}

int car_delete_id(struct car_infor *** car_arr, int *n, int id)
{
    int check = 0;
    for (int i = 0; i < *n - 1; i++)
    {
        if ((*car_arr)[i]->id == id)
            check = 1;
        if (check)
            (*car_arr)[i] = (*car_arr)[i + 1];
    }
    //car_arr_resize(car_arr, n, *n - 1);
    (*n)--;
    return 0;
}

int car_delete(struct car_infor *** car_arr, int * n)
{
    int arr_id[MAX];
    int num;
    car_find(*car_arr, 0, *n, arr_id, &num);
    for (int i = 0; i < num; i++)
    {
        car_delete_id(car_arr, n, arr_id[i]);
    }
    return 0;
}

void car_swap(struct car_infor *car1, struct car_infor *car2)
{
    struct car_infor tmp;
    tmp = *car1;
    *car1 = *car2;
    *car2 = tmp;
}

void car_sort(struct car_infor ** car, int n)
{
    int choise = menu_field();
    printf("Input order: [1 - increase / 0 - Decrease");
    int order = -1;
    if (scanf("%d", &order) != 1 || (order != 1 && order != 0))
    {
        printf("ERROR_INPUT\n");
        return;
    }
    if (order == 0)
        order = -1;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            char str1[50] = "";
            char str2[50] = "";
            int check = 0;
            find_field_infor(*car[i], choise, str1);
            find_field_infor(*car[j], choise, str2);
            if (choise == 1 || choise == 2 || choise == 4)
                check = 1;

            if ((check && strcmp(str1, str2) == order) || (atoi(str1) - atoi(str2)) * order > 0)
            {
                /*struct car_infor * tmp = car[j];
                car[j] = car[i];
                car[i] = tmp;*/
                car_swap(car[j], car[i]);
            }
        }
}

struct car_infor * car_get_by_id(struct car_infor ** car, int n, int id)
{
    for (int i = 0; i < n; i++)
        if (car[i]->id == id)
        {
            return car[i];
        }
    return NULL;
}

void find_result(struct car_infor ** car, int n)
{
    int result[MAX];
    int num = 4;
    //int num_re, num_own;
    char infor[10][50];
    int field[] = {5, 1, 9, 10};
    strcpy(infor[0], "0");
    printf("Input Mark: ");
    str_input(infor[1], stdin, sizeof(infor[0]));
    /*printf("Input Number of repairs and number of owner: ");
    if (scanf("%d %d", &num_re, &num_own) != 2 || num_re < 0 || num_own < 0)
    {
        printf("ERROR INPUT\n");
        return;
    }
    int_to_str(num_re, infor[2]);
    int_to_str(num_own, infor[3]);*/
    strcpy(infor[2], "1");
    strcpy(infor[3], "1");
    int price_beg, price_end;
    printf("Input Range of Price: ");
    if (scanf("%d %d", &price_beg, &price_end) != 2 || price_beg < 0 || price_end < 0)
    {
        printf("ERROR\n");
        return;
    }
    int count = 0;

    for (int i = 0; i < n; i ++)
    {
        char tmp[10][50];
        find_arr_field(*car[i], tmp, field, num);
        if (arr_str_cmp(tmp, infor, num))
        {
            result[count] = (*car[i]).id;
            (count)++;
        }
    }
    title_print();
    for (int i = 0; i < count; i++)
    {
        struct car_infor * tmp = car_get_by_id(car, n, result[i]);
        if (tmp->price <= price_end && tmp->price >= price_beg)
            car_print(*tmp);
    }
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void quickSort(int arr[MAX][2], int low, int high)
{
    if (low < high)
    {
        /* pi là chỉ số nơi phần tử này đã đứng đúng vị trí
         và là phần tử chia mảng làm 2 mảng con trái & phải */
        int pivot = arr[high][1];    // pivot
        int left = low;
        int right = high - 1;
        while(1 == 1)
        {
            count_for++;
            while(left <= right && arr[left][1] < pivot)
            {
                count_for++;
                left++; // Tìm phần tử >= arr[pivot]
            }
            while(right >= left && arr[right][1] > pivot)
            {
                count_for++;
                right--; // Tìm phần tử <= arr[pivot]
            }
            if (left >= right) break; // Đã duyệt xong thì thoát vòng lặp
            swap(&arr[left][0], &arr[right][0]); // Nếu chưa xong, đổi chỗ.
            swap(&arr[left][1], &arr[right][1]); // Nếu chưa xong, đổi chỗ.
            left++; // Vì left hiện tại đã xét, nên cần tăng
            right--; // Vì right hiện tại đã xét, nên cần giảm
        }
        swap(&arr[left][0], &arr[high][0]);
        swap(&arr[left][1], &arr[high][1]);
        int pi = left;

        // Gọi đệ quy sắp xếp 2 mảng con trái và phải
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sort_by_key(struct car_infor **car, int n)
{
    int key[MAX][2];
    for (int i = 0; i < n; i++)
    {
        key[i][0] = i;
        key[i][1] = car[i]->price;
    }
    quickSort(key, 0, n - 1);
}

void car_quickSort(struct car_infor **car, int low, int high)
{
    if (low < high)
    {
        int pivot = car[high]->price;    // pivot
        int left = low;
        int right = high - 1;
        while(1 == 1){
            while(left <= right && car[left]->price < pivot) left++; // Tìm phần tử >= arr[pivot]
            while(right >= left && car[right]->price > pivot) right--; // Tìm phần tử <= arr[pivot]
            if (left >= right) break; // Đã duyệt xong thì thoát vòng lặp
            car_swap(car[left], car[right]); // Nếu chưa xong, đổi chỗ.
            left++; // Vì left hiện tại đã xét, nên cần tăng
            right--; // Vì right hiện tại đã xét, nên cần giảm
        }
        car_swap(car[left], car[high]);
        int pi = left;

        // Gọi đệ quy sắp xếp 2 mảng con trái và phải
        car_quickSort(car, low, pi - 1);
        car_quickSort(car, pi + 1, high);
    }
}

void sort_by_price(struct car_infor **car, int n)
{
    car_quickSort(car, 0, n - 1);
}

int time_bubble_sort(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    struct car_infor ** mcar;
    int n;
    arr_car_input_file(&mcar, &n, f);
    clock_t start, end;
    start = clock();
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (mcar[i]->price > mcar[j]->price)
                car_swap(mcar[i], mcar[j]);
    end = clock();
    return end - start + 1;
}

int time_bubble_sort_key(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    struct car_infor ** mcar;
    int n;
    int key[MAX][2];
    arr_car_input_file(&mcar, &n, f);
    clock_t start, end;
    for (int i = 0; i < n; i++)
    {
        count_for++;
        key[i][0] = i;
        key[i][1] = mcar[i]->price;
    }
    start = clock();
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j ++)
            if (key[i][1] > key[j][1])
            {
                swap(&key[i][1], &key[j][1]);
                swap(&key[i][0], &key[j][0]);
            }
    end = clock();
    return end - start + 1;
}

int time_qsort(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    struct car_infor ** mcar;
    int n;
    arr_car_input_file(&mcar, &n, f);
    clock_t start, end;
    start = clock();
    car_quickSort(mcar, 0, n - 1);
    end = clock();
    return end - start + 1;
}

int time_qsort_key(FILE *f)
{
    fseek(f, 0, SEEK_SET);
    struct car_infor ** mcar;
    int n;
    int key[MAX][2];
    arr_car_input_file(&mcar, &n, f);
    clock_t start, end;
    for (int i = 0; i < n; i++)
    {
        count_for++;
        key[i][0] = i;
        key[i][1] = mcar[i]->price;
    }
    start = clock();
    quickSort(key, 0, n - 1);
    end = clock();
    return end - start + 1;
}

int main()
{
    struct car_infor ** car;
    //int key_arr[2][1000];
    int n = 0;
    FILE *f = fopen("E:/Cau_Truc_Du_Lieu/Lab_02/input.txt", "r");
    arr_car_input_file(&car, &n, f);
    int key[MAX][2];
    for (int i = 0; i < n; i++)
    {
        count_for++;
        key[i][0] = i;
        key[i][1] = car[i]->price;
    }
    int choise = -1;
    while (choise != 0)
    {
        choise = menu(0, 9);
        switch (choise)
        {
        case 0:
            break;
        case 1: car_arr_print(car, n);
            break;
        case 2: car_insert(&car, &n);
            break;
        case 3: car_delete(&car, &n);
            break;
        case 4:
        {
            int result[MAX];
            int count;
            car_find(car, 0, n, result, &count);
            title_print();
            for (int i = 0; i < count; i++)
            {
                car_print(*car_get_by_id(car, n, result[i]));
            }
            printf("\n");
            break;
        }
        case 5: car_sort(car, n);
            break;
        case 6: find_result(car, n);
            break;
        case 7:
        {
            for (int i = 0; i < n; i++)
            {
                count_for++;
                key[i][0] = i;
                key[i][1] = car[i]->price;
            }

            printf("| %5s | %5s | %10s |\n", "No", "i", "Key(Price)");
            for (int i = 0; i < n; i++)
                printf("| %5d | %5d | %10d |\n", i, key[i][0], key[i][1]);

            quickSort(key, 0, n - 1);

            printf("| %5s | %5s | %10s |\n", "No", "i", "Key(Price)");
            for (int i = 0; i < n; i++)
                printf("| %5d | %5d | %10d |\n", i, key[i][0], key[i][1]);
            // sawp xep noi bot
            /*for (int i = 0; i < n - 1; i++)
                for (int j = i + 1; j < n; j ++)
                    if (key[i][1] > key[j][1])
                    {
                        swap(&key[i][1], &key[j][1]);
                        swap(&key[i][0], &key[j][0]);
                    }*/

            title_print();
            for (int i = 0; i < n; i++)
                car_print(*car[key[i][0]]);
            break;
        }
            break;
        case 8:
        {
            //sort_by_price(car, n);

            car_quickSort(car, 0, n - 1);

            /*for (int i = 0; i < n - 1; i++)
                for (int j = i + 1; j < n; j++)
                    if (car[i]->price > car[j]->price)
                        car_swap(car[i], car[j]);*/
            car_arr_print(car, n);
            break;
        }
		case 9:
		{
            printf("n = %d\n", n);
            printf("| %10s | %10s | %10s |\n", "", "Key", "Table");
            int t1, t2, t3, t4;
            t1 = time_qsort_key(f);
            t2 = time_qsort(f);
            if (t2 <= t1)
                t2 += t1;

            printf("Quick Sort : | %10d | %10d |\n", t1, t2);

            t3 = time_bubble_sort_key(f);
            t4 = time_bubble_sort(f);
            if (t4 < t3)
                t4 += t3;
            printf("Bubble Sort: | %10d | %10d |\n", t3, t4);
            break;
		}
        default: printf("Input Wrong more than 5 times !!!\n");
            choise = 0;
            break;
        }
    }
    car_free(car, n);

    fclose(f);
    return OK;
}
