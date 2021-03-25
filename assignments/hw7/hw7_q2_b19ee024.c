#include <stdio.h>
#include <stdlib.h>

int n, **M;

/* Structure of an edge */
typedef struct EDGE
{
    int weight;
    int start;
    int finish;
} edge;

/* Structure of graph */
typedef struct GRAPH
{
    int num_vertex;
    int num_edges;
    struct EDGE *edges;
} graph;

/* Helper function to sort edges based on their weight */
void sort_weight(edge edges[], int number_edges)
{
    int min;
    edge temp;
    for (int i = 0; i < number_edges - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < number_edges; j++)
        {
            if (edges[j].weight < edges[min].weight)
            {
                min = j;
            }
        }
        temp = edges[i];
        edges[i] = edges[min];
        edges[min] = temp;
    }
}

/* Helper function to find the parent of a vertex */
int vertex_parent(int vertex, int *parents)
{
    if (parents[vertex] == vertex)
    {
        return vertex;
    }
    parents[vertex] = vertex_parent(parents[vertex], parents);
    return parents[vertex];
}

/* Kruskal function */
void kruskal(graph *g, int count_edges)
{
    sort_weight(g->edges, count_edges);

    int *parents = (int *)malloc(n * sizeof(int));
    edge *mst_edges = malloc((n - 1) * sizeof(edge));

    for (int i = 0; i < n; i++)
    {
        parents[i] = i;
    }

    int temp_counter = 0, k = 0, start_parent, finish_parent;
    edge curr_edge;

    while (temp_counter != n - 1)
    {
        curr_edge = g->edges[k];
        start_parent = vertex_parent(curr_edge.start, parents);
        finish_parent = vertex_parent(curr_edge.finish, parents);

        if (start_parent != finish_parent)
        {
            mst_edges[temp_counter] = curr_edge;
            temp_counter++;
            parents[start_parent] = finish_parent;
        }
        k++;
    }

    int min_weight = 0;
    for (int i = 0; i < n - 1; i++)
    {
        min_weight = min_weight + mst_edges[i].weight;
    }
    printf("Weight of MST = %d\n", min_weight);

    free(parents);
    free(mst_edges);
}

int main()
{
    int temp1, temp2;
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp != NULL)
    {
        fscanf(fp, "%d", &n); /* assuming that n is a positive integer. */
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

        graph *g = malloc(sizeof(graph));
        g->num_vertex = n;
        int count_edges = 0;

        /* Counting the number of edges */
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (M[i][j] != 0)
                {
                    count_edges++;
                }
            }
        }

        if (count_edges == 0)
        {
            printf("Weight of MST = 0\n");
        }
        else
        {

            g->num_edges = count_edges;
            g->edges = malloc((g->num_edges) * sizeof(edge));

            int temp = 0;

            /* Initializing all the edges */
            for (int i = 0; i < n; i++)
            {
                for (int j = i; j < n; j++)
                {
                    if (M[i][j] != 0)
                    {
                        g->edges[temp].weight = M[i][j];
                        g->edges[temp].start = i;
                        g->edges[temp].finish = j;
                        temp++;
                    }
                }
            }

            kruskal(g, count_edges);
        }

        free(g);
        free(M);
    }
    else
    {
        fclose(fp);
        printf("fp is NULL");
    }

    return 0;
}
