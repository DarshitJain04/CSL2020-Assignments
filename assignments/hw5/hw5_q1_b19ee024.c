#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Helper function to initialize hash table with -1 */
void initialize_hash_table(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = -1;
    }
}

/* Hash function */
int hashFunction(int key, int tableSize)
{
    return (key % tableSize);
}

/* Function which inserts elements in the hash table */
void insertElement(int arr[], int index, int val, int size)
{
    if (arr[index] != -1)
    {
        int temp = val;
        while (arr[index] != -1)
        {
            temp++;
            index = hashFunction(temp, size);
        }
    }

    arr[index] = val;
}

/* Function which looks for a given value in the hash table */
bool searchElement(int arr[], int val, int size)
{
    int index = hashFunction(val, size);
    if (arr[index] == -1)
    {
        return false;
    }
    if (arr[index] == val)
    {
        return true;
    }
    else
    {
        int temp_size = 1;
        int temp_val = val;
        bool present = false;
        index = hashFunction(temp_val + 1, size);
        while (arr[index] != -1 && temp_size <= size)
        {
            if (arr[index] == val)
            {
                present = true;
                break;
            }
            temp_val++;
            index = hashFunction(temp_val + 1, size);
            temp_size++;
        }
        return present;
    }
}

/* Helper function to print the values in the hash table */
void printArray(int arr[], int size)
{
    bool flag = false;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != -1)
        {
            flag = true;
            printf("%d ", arr[i]);
        }
    }
    if (flag)
    {
        printf("\n");
    }
}

int main()
{
    int n, m, temp;
    int *a;
    int *b;

    scanf("%d", &n);
    a = (int *)malloc(n * sizeof(int));
    initialize_hash_table(a, n);
    for (int i = 0; i < n; i++)
    {
        scanf(", %d", &temp);
        insertElement(a, hashFunction(temp, n), temp, n);
    }

    scanf("%d", &m);
    b = (int *)malloc(m * sizeof(int));
    initialize_hash_table(b, m);
    for (int i = 0; i < m; i++)
    {
        scanf(", %d", &temp);
        insertElement(b, hashFunction(temp, m), temp, m);
    }

    if (n == 0 && m == 0)
    {
        printf("C : \n");
        printf("D : \n");
    }
    else if (n == 0 & m != 0)
    {
        printf("C : ");
        printArray(b, m);
        printf("D : \n");
    }
    else if (n != 0 && m == 0)
    {
        printf("C : ");
        printArray(a, n);
        printf("D : \n");
    }
    else if (n != 0 && m != 0)
    {
        int *c = (int *)malloc((n + m) * sizeof(int));
        initialize_hash_table(c, n + m);

        for (int i = 0; i < n; i++)
        {
            if (searchElement(b, a[i], m) == false)
            {
                insertElement(c, hashFunction(a[i], (n + m)), a[i], n + m);
            }
        }

        for (int i = 0; i < m; i++)
        {
            if (searchElement(a, b[i], n) == false)
            {
                insertElement(c, hashFunction(b[i], (n + m)), b[i], n + m);
            }
        }

        printf("C : ");
        printArray(c, n + m);

        int d_size;
        int *d;
        if (n < m)
        {
            d = (int *)malloc(n * sizeof(int));
            d_size = n;
        }
        else
        {
            d = (int *)malloc(m * sizeof(int));
            d_size = m;
        }
        initialize_hash_table(d, d_size);

        for (int i = 0; i < n; i++)
        {
            if (searchElement(b, a[i], m))
            {
                insertElement(d, hashFunction(a[i], d_size), a[i], d_size);
            }
        }

        printf("D : ");
        printArray(d, d_size);

        free(c);
        free(d);
    }
    free(a);
    free(b);
    return 0;
}