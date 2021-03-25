#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n, S, **M;

int *dist, *pred, *processed_vertices;

/* Helper function which returns the vertex which is not yet processed and has minimum distance */
int leastDistanceVertex(int num_vertices)
{
    int temp = INT_MAX;
    int least_distance_vertex;
    for (int i = 0; i < num_vertices; i++)
    {
        if (processed_vertices[i] == 0 && dist[i] < temp)
        {
            least_distance_vertex = i;
            temp = dist[i];
        }
    }
    return least_distance_vertex;
}

/* Helper function to update the distance and predecessor of a vertex */
void relax(int v, int x)
{
    dist[x] = dist[v] + M[v][x];
    pred[x] = v;
}

/* Dijkstra function */
void dijkstra(int num_vertices, int source)
{
    int temp_min_vertex;
    for (int i = 0; i < num_vertices - 1; i++)
    {
        /* Getting the vertex which has the least distance */
        temp_min_vertex = leastDistanceVertex(num_vertices);
        /* Marking it as processed */
        processed_vertices[temp_min_vertex] = 1;

        for (int k = 0; k < num_vertices; k++)
        {
            if (M[temp_min_vertex][k] != 0 && processed_vertices[k] == 0)
            {
                if (dist[k] > dist[temp_min_vertex] + M[temp_min_vertex][k])
                {
                    /* If the condition is true, then RELAX the vertex */
                    relax(temp_min_vertex, k);
                }
            }
        }
    }
}

int main()
{
    int temp1, temp2;
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp != NULL)
    {
        fscanf(fp, "%d %d", &n, &S); /* assuming that n is a positive integer. */
        M = (int **)malloc(sizeof(int *) * n);
        for (temp1 = 0; temp1 < n; temp1++)
            M[temp1] = (int *)malloc(sizeof(int) * n);
        for (temp1 = 0; temp1 < n; temp1++)
            for (temp2 = 0; temp2 < n; temp2++)
                fscanf(fp, "%d", &M[temp1][temp2]);
        /* the above code reads the data from the file into the square matrix M */
        /* Your code will come here */
        // free the memory allocated by malloc yourself
        fclose(fp);

        dist = (int *)malloc(n * sizeof(int));
        pred = (int *)malloc(n * sizeof(int));
        processed_vertices = (int *)malloc(n * sizeof(int));

        /* Initializing the distance and predecessor for each vertex */
        for (int i = 0; i < n; i++)
        {
            dist[i] = INT_MAX;
            pred[i] = -1;
            processed_vertices[i] = 0;
        }
        /* Setting the distance of Source to be 0 */
        dist[S - 1] = 0;

        /* Calling Dijkstra's algorithm */
        dijkstra(n, S - 1);

        for (int i = 0; i < n; i++)
        {
            if (dist[i] == INT_MAX)
            {
                if (i == n - 1)
                {
                    printf("-1\n");
                }
                else
                {
                    printf("-1 ");
                }
            }
            else
            {
                if (i == n - 1)
                {
                    printf("%d\n", dist[i]);
                }
                else
                {
                    printf("%d ", dist[i]);
                }
            }
        }

        free(M);
        free(dist);
        free(pred);
        free(processed_vertices);
    }
    else
    {
        fclose(fp);
        printf("fp is NULL");
    }

    return 0;
}
