#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n;
int **dp_table;
int **steps;

/* Helper function which returns maximum of two numbers */
int MAX(int a, int b)
{
    return a > b ? a : b;
}

/* Helper function which returns the minimum of two numbers */
int MIN(int a, int b)
{
    return a < b ? a : b;
}

/* Function which returns maximum value the player can get */
int findMax(int arr[], int size)
{
    bool isPlayer1;
    if (size % 2 == 0)
    {
        isPlayer1 = false;
    }
    else
    {
        isPlayer1 = true;
    }

    int temp = 1;

    for (int i = 0; i < size; i++)
    {
        if (isPlayer1 == false)
        {
            dp_table[i][i] = 0;
            steps[i][i] = 1;
        }
        else
        {
            dp_table[i][i] = arr[i];
            steps[i][i] = 1;
        }
    }

    isPlayer1 = !isPlayer1;

    while (temp < size)
    {

        for (int i = 0; i + temp < size; i++)
        {
            int temp1 = dp_table[i + 1][i + temp];
            int temp2 = dp_table[i][i + temp - 1];

            if (isPlayer1 == false)
            {
                if (temp1 < temp2)
                {
                    dp_table[i][i + temp] = temp1;
                    steps[i][i + temp] = 1;
                }
                else
                {
                    dp_table[i][i + temp] = temp2;
                    steps[i][i + temp] = -1;
                }
            }
            else
            {
                if (arr[i] + temp1 > arr[i + temp] + temp2)
                {
                    dp_table[i][i + temp] = arr[i] + temp1;
                    steps[i][i + temp] = 1;
                }
                else
                {
                    dp_table[i][i + temp] = arr[i + temp] + temp2;
                    steps[i][i + temp] = -1;
                }
            }
        }

        isPlayer1 = !isPlayer1;

        temp++;
    }

    return dp_table[0][n - 1];
}

int main()
{
    scanf("%d", &n);

    /* Array for input */
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    /* A temporary array to store the steps taken by Akshara */
    int *temp_steps = (int *)malloc(n * sizeof(int));

    /* n x n matrix to store the values the player can obtain */
    dp_table = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        dp_table[i] = (int *)malloc(n * sizeof(int));
    }

    /* n x n matrix to keep a track of the moves played by both the players */
    steps = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        steps[i] = (int *)malloc(n * sizeof(int));
    }

    int sum = findMax(a, n);
    printf("Sum = %d\n", sum);

    printf("Steps = ");

    int count_i = 0, count_j = n - 1, count = 0;
    bool isPlayer1 = true;

    while (count_i <= count_j)
    {
        if (steps[count_i][count_j] == 1)
        {
            if (isPlayer1)
            {
                temp_steps[count] = a[count_i];
                count++;
            }
            count_i++;
        }
        else if (steps[count_i][count_j] == -1)
        {
            if (isPlayer1)
            {
                temp_steps[count] = a[count_j];
                count++;
            }
            count_j--;
        }
        isPlayer1 = !isPlayer1;
    }

    for (int i = 0; i < count; i++)
    {
        if (i == count - 1)
        {
            printf("%d\n", temp_steps[i]);
        }
        else
        {
            printf("%d, ", temp_steps[i]);
        }
    }

    free(a);
    free(temp_steps);
    free(dp_table);
    free(steps);

    return 0;
}
