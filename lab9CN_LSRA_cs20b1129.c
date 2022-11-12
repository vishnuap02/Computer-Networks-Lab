// Vishnu Abhay PArvatikar
// CS20B1129
// Link state routing algorithm
#include <stdio.h>
#include <stdlib.h>
int m, noEdges = 0, i, j, k, b[3][3], matrix[30][30], dist;
;
struct nd
{
    int d[35];
    int nh[35];
} t[35];

int main()
{
    printf("Enter the number of nodes: ");
    scanf("%d", &m);
    printf("\nEnter the no. of edges: ");
    scanf("%d", &noEdges);
    printf("\nEnter the values as: A B x ; where x is weight between A,B. \n");
    printf("\nEnter the edges and their weigths: \n");
    for (i = 0; i < noEdges; i++)
    {
        for (j = 0; j < 3; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            matrix[i][j] = 9999999;
            if (i == j)
            {
                matrix[i][j] = 0;
            }
        }
    }
    for (i = 0; i < noEdges; i++)
    {
        matrix[b[i][0]][b[i][1]] = b[i][2];
        matrix[b[i][1]][b[i][0]] = b[i][2];
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j = j + 1)
        {
            t[i].d[j] = matrix[i][j];
            t[i].nh[j] = j;
        }
    }
    for (i = 0; i < m; i++)
    {
        int choosed[35] = {0}, min;
        if (i == 0)
            min = 1;
        else
        {
            min = 0;
        }
        choosed[i] = 1;
        // find minimum
        // this will work for everything except last node as apart from it no node is left to
        // choose as minimum.
        for (j = 0; j < m - 1; j++)
        {
            if ((t[i].d[j] < t[i].d[min]) && (choosed[j] == 0) && (i != j))
            {
                min = j;
                printf("\n %d %d - %d %d", t[i].d[j], t[i].d[min], i, min);
            }
        }
        // min when i is last node
        if (i == m - 1)
        {
            min = i;
        }
        choosed[min] = 1;

        // after getting minimum weight perform relaxation for min node.
        // relaxation for all nodes except last
        if (i < m - 1)
        {
            for (j = 0; j < m; j++)
            {

                if ((t[i].d[j] > matrix[min][j] + t[i].d[min]) && (min != j))
                {
                    t[i].d[j] = matrix[min][j] + t[i].d[min];
                    t[i].nh[j] = k;
                }
            }
        }

        else // relaxation for last node.
        {
            for (j = 0; j < m; j++)
            {
                t[i].d[j] = t[j].d[i];
            }
        }
    }

    printf("\nMinimum distances Using Link state routing algorithm  : \n (which uses Dijkstra)\n");
    for (i = 0; i < m; i++)
    {
        printf("\nRouter %d -\n", (i + 1));
        printf("Destination Distance Next Hop\n");
        for (int j = 0; j < m; j++)
        {
            printf("Router %d\t\t %d\t\t\tRouter %d\n", j + 1, t[i].d[j], t[i].nh[j] + 1);
        }
    }
    return 0;
}
