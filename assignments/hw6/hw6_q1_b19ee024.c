#include <stdio.h>
#include <stdlib.h>

/* Structure of class node */
typedef struct CLASS
{
    int duration;
    int deadline;
    int order;
} prof_class;

/* Helper function to find maximum value between two numbers */
int MAX(int a, int b)
{
    return a > b ? a : b;
}

/* Partition function for quicksort function which sorts according to the deadline */
int partitionDeadline(prof_class classes[], int start, int end)
{
    int pivot = classes[end].deadline;
    int temp_i = (start - 1);
    prof_class temp;

    for (int j = start; j < end; j++)
    {
        if (classes[j].deadline < pivot)
        {
            temp_i++;
            temp = classes[temp_i];
            classes[temp_i] = classes[j];
            classes[j] = temp;
        }
    }
    temp = classes[temp_i + 1];
    classes[temp_i + 1] = classes[end];
    classes[end] = temp;
    return (temp_i + 1);
}

/* Quicksort function to sort according to the deadline */
void quickSortDeadline(prof_class classes[], int start, int end)
{
    if (start < end)
    {
        int index = partitionDeadline(classes, start, end);
        quickSortDeadline(classes, start, index - 1);
        quickSortDeadline(classes, index + 1, end);
    }
}

/* Partition function for quicksort function which sorts according to the duration */
int partitionDuration(prof_class classes[], int start, int end)
{
    int pivot = classes[end].duration;
    int temp_i = (start - 1);
    prof_class temp;

    for (int j = start; j < end; j++)
    {
        if (classes[j].duration < pivot)
        {
            temp_i++;
            temp = classes[temp_i];
            classes[temp_i] = classes[j];
            classes[j] = temp;
        }
    }
    temp = classes[temp_i + 1];
    classes[temp_i + 1] = classes[end];
    classes[end] = temp;
    return (temp_i + 1);
}

/* Quicksort function to sort according to the duration */
void quickSortDuration(prof_class classes[], int start, int end)
{
    if (start < end)
    {
        int index = partitionDuration(classes, start, end);
        quickSortDuration(classes, start, index - 1);
        quickSortDuration(classes, index + 1, end);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    prof_class *classes = (prof_class *)malloc(n * sizeof(prof_class));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &(classes[i].duration), &(classes[i].deadline));
        classes[i].order = i + 1;
    }

    /* Sorting according to the deadline first */
    /* Which means finishing jobs which have early deadlines */
    quickSortDeadline(classes, 0, n - 1);

    int count = 0, temp;
    while (count < n)
    {
        temp = count;
        while (classes[temp].deadline == classes[temp + 1].deadline)
        {
            temp++;
        }
        if (temp != count)
        {
            /* If the deadline is same, sort according to the duration */
            /* Do the short duration job first */
            quickSortDuration(classes, count, temp);
        }
        count = temp + 1;
    }

    printf("Order of classes = ");

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            printf("%d\n", classes[i].order);
        }
        else
        {
            printf("%d, ", classes[i].order);
        }
    }

    int start = 0, finish = 0, annoyance = 0;
    for (int i = 0; i < n; i++)
    {
        finish = start + classes[i].duration;
        annoyance = annoyance + MAX(finish - classes[i].deadline, 0);
        start = finish;
    }

    printf("Annoyance = %d\n", annoyance);

    free(classes);

    return 0;
}
