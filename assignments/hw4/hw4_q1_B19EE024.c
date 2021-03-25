#include <stdio.h>
#include <stdbool.h>

/* Creating two arrays 
    One for max heap and other for min heap
*/
int max_heap[100], min_heap[100];
int n_max_heap = 0, n_min_heap = 0;

/* Max Heapify Function 
It makes sure that the max heap property is satisfied
*/
void max_heapify(int arr[], int i)
{
    int l = 2 * i;
    int r = (2 * i) + 1;
    int larger;
    if ((l <= arr[0]) && (arr[l] > arr[i]))
    {
        larger = l;
    }
    else
    {
        larger = i;
    }
    if ((r <= arr[0]) && (arr[r] > arr[larger]))
    {
        larger = r;
    }
    if (larger != i)
    {
        int temp = arr[i];
        arr[i] = arr[larger];
        arr[larger] = temp;
        max_heapify(arr, larger);
    }
}

/* Min Heapify Function 
It makes sure that the min heap property is satisfied
*/
void min_heapify(int arr[], int i)
{
    int l = 2 * i;
    int r = (2 * i) + 1;
    int smaller;
    if ((l <= arr[0]) && (arr[l] < arr[i]))
    {
        smaller = l;
    }
    else
    {
        smaller = i;
    }
    if ((r <= arr[0]) && (arr[r] < arr[smaller]))
    {
        smaller = r;
    }
    if (smaller != i)
    {
        int temp = arr[i];
        arr[i] = arr[smaller];
        arr[smaller] = temp;
        min_heapify(arr, smaller);
    }
}

/* Function which creates max heap for a given array */
void create_max_heap(int arr[])
{
    int n = arr[0];
    for (int i = (n / 2); i >= 1; i--)
    {
        max_heapify(arr, i);
    }
}

/* Function which creates min heap for a given array */
void create_min_heap(int arr[])
{
    int n = arr[0];
    for (int i = (n / 2); i >= 1; i--)
    {
        min_heapify(arr, i);
    }
}

/* Function which prints the heap */
void print_heap(int arr[])
{
    for (int i = 1; i < arr[0] + 1; i++)
    {
        if (i == arr[0])
        {
            printf("%d\n", arr[i]);
        }
        else
        {
            printf("%d ", arr[i]);
        }
    }
}

/* Function which deletes a given value from the max heap */
void delete_max_heap(int arr[], int val)
{
    bool present = false;
    for (int i = 1; i < n_max_heap + 1; i++)
    {
        if (max_heap[i] == val)
        {
            present = true;
            max_heap[i] = max_heap[n_max_heap];
            n_max_heap--;
            max_heap[0] = n_max_heap;
            break;
        }
    }
    if (present)
    {
        create_max_heap(max_heap);
        print_heap(max_heap);
    }
}

/* Function which deletes a given value from min heap */
void delete_min_heap(int arr[], int val)
{
    bool present = false;
    for (int i = 1; i < n_min_heap + 1; i++)
    {
        if (min_heap[i] == val)
        {
            present = true;
            min_heap[i] = min_heap[n_min_heap];
            n_min_heap--;
            min_heap[0] = n_min_heap;
            break;
        }
    }
    if (present)
    {
        create_min_heap(min_heap);
        print_heap(min_heap);
    }
}

/* Function which sorts the heap */
void sort(int arr[], char operation)
{
    int temp = arr[0];
    int swap_temp;
    if (operation == 'X')
    {
        for (int i = temp; i >= 2; i--)
        {
            swap_temp = arr[1];
            arr[1] = arr[i];
            arr[i] = swap_temp;
            arr[0]--;
            max_heapify(arr, 1);
        }
        arr[0] = n_max_heap;
        print_heap(arr);
    }
    else
    {
        for (int i = temp; i >= 2; i--)
        {
            swap_temp = arr[1];
            arr[1] = arr[i];
            arr[i] = swap_temp;
            arr[0]--;
            min_heapify(arr, 1);
        }
        arr[0] = n_min_heap;
        for (int i = n_min_heap; i >= 1; i--)
        {
            if (i == 1)
            {
                printf("%d\n", arr[i]);
            }
            else
            {
                printf("%d ", arr[i]);
            }
        }
    }
}

int main()
{
    int input_val, menuInput;
    bool present;
    char operation;
    do
    {
        printf("Enter 0 to exit the program\n");
        printf("Enter 1 to create max/min heap\n");
        printf("Enter 2 to add data to existing max/min heap\n");
        printf("Enter 3 to delete data from existing max/min heap\n");
        printf("Enter 4 to delete max/min data from existing max/min heap\n");
        printf("Enter 5 to sort the array containing the max/min heap\n");

        scanf("%d", &menuInput);

        switch (menuInput)
        {
        case 0:
            break;
        case 1:
            scanf(" %c", &operation);
            if (operation == 'X')
            {
                scanf("%d", &n_max_heap);
                max_heap[0] = n_max_heap;
                for (int i = 1; i < n_max_heap + 1; i++)
                {
                    scanf("%d", &input_val);
                    max_heap[i] = input_val;
                }
                create_max_heap(max_heap);
                print_heap(max_heap);
            }
            else if (operation == 'N')
            {
                scanf("%d", &n_min_heap);
                min_heap[0] = n_min_heap;
                for (int i = 1; i < n_min_heap + 1; i++)
                {
                    scanf("%d", &input_val);
                    min_heap[i] = input_val;
                }
                create_min_heap(min_heap);
                print_heap(min_heap);
            }
            break;
        case 2:
            scanf(" %c", &operation);
            scanf("%d", &input_val);
            if (operation == 'X')
            {
                n_max_heap++;
                max_heap[0] = n_max_heap;
                max_heap[n_max_heap] = input_val;
                create_max_heap(max_heap);
                print_heap(max_heap);
            }
            else if (operation == 'N')
            {
                n_min_heap++;
                min_heap[0] = n_min_heap;
                min_heap[n_min_heap] = input_val;
                create_min_heap(min_heap);
                print_heap(min_heap);
            }
            break;
        case 3:
            scanf(" %c", &operation);
            scanf("%d", &input_val);
            if (operation == 'X')
            {
                delete_max_heap(max_heap, input_val);
            }
            else if (operation == 'N')
            {
                delete_min_heap(min_heap, input_val);
            }
            break;
        case 4:
            scanf(" %c", &operation);
            if (operation == 'X')
            {
                delete_max_heap(max_heap, max_heap[1]);
            }
            else if (operation == 'N')
            {
                delete_min_heap(min_heap, min_heap[1]);
            }
            break;
        case 5:
            scanf(" %c", &operation);
            if (operation == 'X')
            {
                sort(max_heap, operation);
            }
            else if (operation == 'N')
            {
                sort(min_heap, operation);
            }
            break;
        default:
            break;
        }
    } while (menuInput != 0);
    return 0;
}