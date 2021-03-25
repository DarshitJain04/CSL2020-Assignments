#include <stdio.h>
#include <stdlib.h>

int n, **M;

/* Structure of a vertex */
typedef struct VERTEX
{
    int index;
    int color;
    int discovered;
    int finished;
    struct VERTEX *preced;
} vertex;

/* Initializing time parameter */
int time = 0;

/* White : Not yet discovered */
int white = -1;
/* Gray : Discovered but adjacent vertices not yet processed */
int gray = 0;
/* Black : Discovered and adjacent vertices also processed */
int black = 1;

/* DFS Visit Function for a given vertex u */
void dfs_visit(vertex *graph, vertex *u)
{
    time++;
    u->discovered = time;
    u->color = gray;
    for (int i = 0; i < n; i++)
    {
        if (M[u->index][i] == 1)
        {
            if (graph[i].color == white)
            {
                graph[i].preced = u;
                dfs_visit(graph, &(graph[i]));
            }
        }
    }
    u->color = black;
    time++;
    u->finished = time;
}

/* DFS Function */
void dfs(vertex *graph)
{
    /* Initialization */
    for (int i = 0; i < n; i++)
    {
        graph[i].index = i;
        graph[i].color = white;
        graph[i].discovered = 0;
        graph[i].finished = 0;
        graph[i].preced = NULL;
    }

    for (int i = 0; i < n; i++)
    {
        /* Calling DFS Visit if the vertex is not yet visited */
        if (graph[i].color == white)
        {
            dfs_visit(graph, &graph[i]);
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

        vertex *graph = malloc(n * sizeof(vertex));

        dfs(graph);

        for (int i = 0; i < n; i++)
        {
            printf("%d %d %d\n", graph[i].index + 1, graph[i].discovered, graph[i].finished);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (M[i][j] == 0)
                {
                    if (j == n - 1)
                    {
                        printf("0\n");
                    }
                    else
                    {
                        printf("0 ");
                    }
                }
                else
                {
                    if ((graph[i].discovered == graph[j].discovered) && (graph[i].finished == graph[j].finished))
                    {
                        if (j == n - 1)
                        {
                            printf("B\n");
                        }
                        else
                        {
                            printf("B ");
                        }
                    }
                    else if ((graph[i].discovered < graph[j].discovered) && (graph[i].finished > graph[j].finished) && (&(graph[i]) == graph[j].preced))
                    {
                        if (j == n - 1)
                        {
                            printf("T\n");
                        }
                        else
                        {
                            printf("T ");
                        }
                    }
                    else if ((graph[i].discovered > graph[j].discovered) && (graph[i].finished < graph[j].finished))
                    {
                        if (j == n - 1)
                        {
                            printf("B\n");
                        }
                        else
                        {
                            printf("B ");
                        }
                    }
                    else if ((graph[i].discovered > graph[j].discovered) && (graph[i].finished > graph[j].finished))
                    {
                        if (j == n - 1)
                        {
                            printf("C\n");
                        }
                        else
                        {
                            printf("C ");
                        }
                    }
                    else if ((graph[i].discovered < graph[j].discovered) && (graph[i].finished > graph[j].finished))
                    {
                        if (j == n - 1)
                        {
                            printf("F\n");
                        }
                        else
                        {
                            printf("F ");
                        }
                    }
                }
            }
        }

        free(graph);
        free(M);
    }
    else
    {
        fclose(fp);
        printf("fp is NULL");
    }
    return 0;
}
