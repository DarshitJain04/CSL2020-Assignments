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

int main()
{
    int n, k, x, y, temp;
    int *a;
    bool possible = false;

    scanf("%d", &n);
    a = (int *)malloc(n * sizeof(int));
    initialize_hash_table(a, n);
    for (int i = 0; i < n; i++)
    {
        scanf(", %d", &temp);
        insertElement(a, hashFunction(temp, n), temp, n);
    }

    int *b = (int *)malloc(n * sizeof(int));
    initialize_hash_table(b, n);

    scanf("%d", &k);

    for (int i = 0; i < n; i++)
    {
        x = a[i];
        y = k - a[i];
        if (searchElement(a, y, n) && x != y)
        {
            possible = true;
            if ((!searchElement(b, x, n)) && (!searchElement(b, y, n)))
            {
                insertElement(b, hashFunction(x, n), x, n);
            }
        }
    }

    if (!possible)
    {
        printf("Not found\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (b[i] != -1)
            {

                printf("(%d,%d)\n", b[i], k - b[i]);
            }
        }
    }

    free(a);
    free(b);

    return 0;
}