#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define COUNT 20
#define MAX_LEN_A 100000
#define REPEAT_TIME 100000
#define MAX_RAND 100000

int cmp[4];

#define FILE_O 3
#define BST_O 1
#define AVL_O 2
#define HASH_O 0

struct node
{
     long int data;                 //Data element
     struct node * left;          //Pointer to left node
     struct node * right;         //Pointer to right node
};

typedef struct node node_t;

struct arr
{
    int a[MAX_LEN_A + 1];
    int n;
};

typedef struct arr arr_t;

node_t *MakeNode(int value)
{
    node_t * temp=(node_t *)malloc(sizeof(node_t));
    temp->data = value;
    temp->left = temp->right=NULL;
    return temp;
}

int LeftOf( const int value, const node_t* root )
{
    // Nếu bạn muốn cây BST cho phép giá trị trùng lặp, hãy sử dụng dòng code thứ 2
    return value < root->data;
//    return value <= root->data;
}

int RightOf( const int value, const node_t* root )
{
    return value > root->data;
}

node_t* node_insert_bst(node_t* root, const int value)
{
    if ( root == NULL )
    {
        node_t* node = (node_t*)malloc( sizeof( node_t ) );
        node->left = NULL;
        node->right = NULL;
        node->data = value;
        return node;
    }
    if ( LeftOf( value, root ) )
        root->left = node_insert_bst( root->left, value );
    else if ( RightOf( value, root ) )
        root->right = node_insert_bst( root->right, value );
    return root;
}

node_t * bin_tree_build(arr_t *arr)
{
    node_t *root = NULL;

    for (int i = 0; i < arr->n; i++)
        root = node_insert_bst(root, arr->a[i]);
    return root;
}

int BST_Search( const node_t* root, int value )
{
    if ( root == NULL )
        return 0;
    cmp[BST_O]++;
    if(root->data == value)
    {
        return 1;
    }
    else if ( LeftOf( value, root ) ){
        return BST_Search( root->left, value );
    }else if( RightOf( value, root ) ){
        return BST_Search( root->right, value );
    }
    return true;
}

int AVL_Search( const node_t* root, int value )
{
    if ( root == NULL )
        return 0;
    cmp[AVL_O]++;
    if(root->data == value){
        return 1;
    }else if ( LeftOf( value, root ) ){
        return AVL_Search( root->left, value );
    }else if( RightOf( value, root ) ){
        return AVL_Search( root->right, value );
    }
    return true;
}

int LeftMostValue( const node_t* root )
{
    while ( root->left != NULL )
        root = root->left;
    return root->data;
}

node_t* Delete( node_t* root, int value )
{
    if ( root == NULL )
        return root;
    if ( LeftOf( value, root ) )
        root->left = Delete( root->left, value );
    else if ( RightOf( value, root ) )
        root->right = Delete( root->right, value );
    else
    {
        // root->data == value, delete this node
        if ( root->left == NULL )
        {
            node_t* newRoot = root->right;
            free( root );
            return newRoot;
        }
        if ( root->right == NULL )
        {
            node_t* newRoot = root->left;
            free( root );
            return newRoot;
        }
        root->data = LeftMostValue( root->right );
        root->right = Delete( root->right, root->data );
    }
    return root;
}

void PreOrder(node_t* root){
    if(root != NULL)
    {
        printf("%ld ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(node_t* root, arr_t *arr)
{
    if(root != NULL)
    {
        InOrder(root->left, arr);
        arr->a[arr->n] = root->data;
        arr->n += 1;
        InOrder(root->right, arr);
    }
}

node_t *buildTree(arr_t *arr, int start, int end)
{
    // base case
    if (start > end)
        return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    node_t *root = MakeNode(arr->a[mid]);

    /* Using index in Inorder traversal, construct
       left and right subtress */
    root->left  = buildTree(arr, start, mid-1);
    root->right = buildTree(arr, mid+1, end);

    return root;
}

node_t *avl_tree_build(node_t *root)
{
    arr_t arr;
    arr.n = 0;
    InOrder(root, &arr);
    node_t *new_root = buildTree(&arr, 0, arr.n - 1);
    return new_root;
}

void print2DUtil(node_t *root, int space)
{
    // Base case
    if (root == NULL)
    {
        space += COUNT;
        for (int i = COUNT; i < space; i++)
        {
            if (i % COUNT)
                printf(" ");
            else
                printf(" ");
        }
        printf("Nil\n\n");
        return;
    }
    printf("\n");
    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    //printf("\n");
    for (int i = COUNT; i < space; i++)
    {
        if (i % COUNT)
            printf(" ");
        else
            printf(" ");
    }
    printf("%ld\n", root->data);

    // Process left child
    print2DUtil(root->left, space);
    //printf("\n\n");
}

int my_rand(int max)
{
    max = MAX_RAND;
    return rand() % (2 * max);
}

void file_create(char *s, int n)
{
    FILE *f = fopen(s, "w");
    for (int i = 0; i < n; i++)
    {
        int i = my_rand(MAX_LEN_A);
        fprintf(f, " %d", i);
    }
    fclose(f);
}

void file_read(char *s, arr_t *arr)
{
    FILE *f = fopen(s, "r");
    arr->n = 0;
    while (fscanf(f, "%d", &(arr->a[(arr->n)])) == 1)
        (arr->n)++;

    fclose(f);
}

int file_search(char *fname, int value)
{
    FILE *f = fopen(fname, "r");
    if (!f)
        return 0;
    int num = 0;
    while (fscanf(f, "%d", &num) == 1)
    {
        cmp[FILE_O]++;
        if (num == value)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}


int hashfunc(int a, int max_value)
{
    //max_value = MAX_LEN_A;
    if (a < 0)
        a *= -1;
    return a % (max_value + (max_value + 1) % 2);
}

void hash_insert(arr_t *hashtable, int value)
{
    int index = hashfunc(value, hashtable->n);
    int h = 1;
    while(hashtable->a[index] != -1)
    {
        //printf("h = %d", h);
        index = (index + h * h) % (hashtable->n + (hashtable->n + 1) % 2);
        //printf("-\n");
        h++;
    }
    hashtable->a[index] = value;
}

int hash_search(arr_t *hashtable, int value)
{
    //Compute the index using the Hash Function
    int index = hashfunc(value, hashtable->n);
     //Search for an unused slot and if the index will exceed the hashTableSize roll back
    int h = 1;
    cmp[HASH_O]++;
    while(hashtable->a[index] != value && hashtable->a[index] != -1)
    {
        cmp[HASH_O]++;
        index = (index + h*h) % hashtable->n;
        h++;
    }
    if(hashtable->a[index] == value)
        return 1;
    else
        return 0;
}

node_t* node_input(void)
{
    int value;
    printf("Input value: ");
    if (scanf("%d", &value) != 1)
        return NULL;
    node_t *node = MakeNode(value);
    return node;
}



clock_t BST_Search_Time(node_t *root, int value)
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < REPEAT_TIME; i++)
    {
        cmp[BST_O] = 0;
        BST_Search(root, value);
    }
    end = clock();
    return end - start;
}

clock_t AVL_Search_Time(node_t *root, int value)
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < REPEAT_TIME; i++)
    {
        cmp[AVL_O] = 0;
        AVL_Search(root, value);
    }
    end = clock();
    return end - start;
}

clock_t File_Search_Time(char *name, int value)
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < REPEAT_TIME; i++)
    {
        cmp[FILE_O] = 0;
        file_search(name, value);
    }
    end = clock();
    return end - start;
}

clock_t Hash_Search_Time(arr_t *hashtable, int value)
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < REPEAT_TIME; i++)
    {
        cmp[HASH_O] = 0;
        hash_search(hashtable, value);
    }
    end = clock();
    return end - start;
}

void timer(void)
{
    {
        int a[] = {10, 100, 500, 1000, 5000, 10000, 20000, 50000, 100000};
        //int a[] = {7};
        int n = sizeof(a) / sizeof(a[0]);
        int time[4][n];
        int cmp_time[4][n];
        int s = 3;
        for (int i = n - 1; i >= 0; i--)
        {
            arr_t *arr = malloc(sizeof(arr_t));
            arr->n = 0;
            char file_name[] = "inp1.txt";

            arr_t *hashtable = malloc(sizeof(arr_t));
            hashtable->n = MAX_LEN_A + 1;
            memset(hashtable->a, -1, sizeof(hashtable->a));

            // Input From File
            file_create(file_name, a[i]);
            file_read(file_name, arr);

            // Build Bin Tree
            node_t *root_bst = bin_tree_build(arr);

            //Build Balancce Bin Tree
            node_t *root_avl = avl_tree_build(root_bst);

            // Buil Hash Table
            for (int i = 0; i < arr->n; i++)
            {
                hash_insert(hashtable, arr->a[i]);
            }

            int value = arr->a[(int) fabs(my_rand(MAX_LEN_A)) % arr->n];
            printf("Value = %d\n", value);

            time[HASH_O][i] = Hash_Search_Time(hashtable, value);
            if (time[HASH_O][i] == 0)
                time[HASH_O][i] += 1;
            time[BST_O][i] = BST_Search_Time(root_bst, value);
            time[AVL_O][i] = AVL_Search_Time(root_avl, value);
            //time[FILE_O][i] = File_Search_Time(file_name, value);

            for (int k = 0; k < s; k++)
                cmp_time[k][i] = (int) cmp[k];
        }

        char format[] = "%10d|";

        for (int i = 0; i < n; i++)
            printf(format, a[i]);
        printf("\n---------------------------------------------------------------------------------\n");

        for (int k = 0; k < s; k++)
        {
            for (int i = 0; i < n; i++)
                if (k == 0)
                    printf(format, time[k][i]);
                else
                    printf("%10.3f|", time[k][i] * 1.0 / time[0][i] * 100);
            printf("\n");
        }
        printf("\n---------------------------------------------------------------------------------\n");

        for (int k = 0; k < s; k++)
        {
            for (int i = 0; i < n; i++)
                printf(format, cmp_time[k][i]);
            printf("\n");
        }

    }
}

int menu(void)
{
    printf("0.Exit\n");
    printf("1.Print Tree\n");
    printf("2.Insert Node\n");
    printf("3.Search\n");
    printf("4.Delete Node\n");
    printf("5.Balan Tree\n");
    printf("Input Ur Choise: ");
    int choise;
    if (scanf("%d", &choise) != 1 || choise < 0 || choise >= 6)
        choise = -1;
    return choise;
}

int process(void)
{
    arr_t *arr = malloc(sizeof(arr_t));
    arr->n = 0;

    char file_name[] = "inp1.txt";

    // Input From File
    //file_create(file_name, MAX_LEN_A - 1);
    file_read(file_name, arr);

    // Build Bin Tree
    node_t *root_bst = bin_tree_build(arr);
    //print2DUtil(root_bst, 0);
    //printf("\n\n\n\n");

    //Build Balancce Bin Tree
    node_t *root_avl = avl_tree_build(root_bst);
    //print2DUtil(root_avl, 0);
    //printf("\n\ncheck\n\n");

    arr_t *hashtable = malloc(sizeof(arr_t));
    hashtable->n = arr->n + 1;
    memset(hashtable->a, -1, sizeof(hashtable->a));

    // Buil Hash Table
    for (int i = 0; i < arr->n; i++)
    {
        hash_insert(hashtable, arr->a[i]);
    }
    for (int i = 0; i <= hashtable->n; i++)
        printf("|%5d|%10d|\n", i, hashtable->a[i]);
    while (1)
    {
        int choise = menu();
        switch (choise)
        {
            case -1:
            {
                printf("ERROR INPUT!!!!");
            }
        case 0:
        {
            return 0;
        }
        case 1:
        {
            print2DUtil(root_bst, 0);
            printf("\n\n\n\n\n");

            break;
        }
        case 2:
        {
            node_t* node = node_input();
            if (!node)
            {
                printf("ERROR INPUT!!\n");
            }
            else
            {
                root_bst = node_insert_bst(root_bst, node->data);
                root_avl = node_insert_bst(root_avl, node->data);
                FILE *f = fopen(file_name, "w");
                fseek(f, SEEK_END, 0);
                fclose(f);
            }
            break;
        }
        case 3:
        {
            node_t* node = node_input();
            int rc = BST_Search(root_bst, node->data);
            if (rc == 1)
                printf("Node is in Tree\n");
            else
            {
                if (root_bst)
                    printf("Node isnt in Tree\n");
                else
                    printf("Empty Tree\n");
            }
            break;
        }
        case 4:
        {
            node_t* node = node_input();
            int rc = BST_Search(root_bst, node->data);
            if (rc == 1)
            {
                root_bst = Delete(root_bst, node->data);
            }
            else
            {
                if (root_bst)
                    printf("Node isnt in Tree\n");
                else
                    printf("Empty Tree\n");
            }
            break;
        }
        case 5:
        {
            root_avl = avl_tree_build(root_bst);
            print2DUtil(root_avl, 0);
            printf("\n\n\n\n\n");

        }
        }
    }

    /*char format[] = "%20s : %d\n";
    int value = my_rand(MAX_LEN_A);
    printf("Value = %d\n", value);

    int rc = BST_Search(root_bst, value);
    printf(format, "BST SEARCH", rc);

    rc = BST_Search(root_avl, value);
    printf(format, "AVL SEARCH", rc);

    rc = file_search(file_name, value);
    printf(format, "FILE SEARCH", rc);

    rc = hash_search(hashtable, value);
    printf(format, "HASH SEARCH", rc);*/
    return 0;
}

int main(void)
{
    timer();
    //process();

    return 0;
}



/*

node_t *right_rotate(node_t *root)
{
    node_t *left = root->left;
    if (left == NULL)
        return root;
    root->left = left->right;
    left->right = root;
    return left;
}

node_t *left_rotate(node_t *root)
{
    node_t *right = root->right;
    if (right == NULL)
        return right;

}

 * */
