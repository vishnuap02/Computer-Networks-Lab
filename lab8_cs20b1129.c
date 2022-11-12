// Vishnu Abhay PArvatikar
// CS20B1129
#include <stdio.h>
#include <stdlib.h>
int m, noEdges = 0, i, j, k, b[3][3], matrix[30][30], dist;
;
struct nd
{
    int d[35];
    int nh[35];
} t[35];
// int distance(int i, int target, int nextnd)
// {
//     //     if(target==i){
//     //         printf("\n In First If()");
//     // return t[i].d[target];
//     // }
//     if (target != nextnd)
//     {
//         int min = 0;
//         printf("\n In If() %d %d %d", i, target, nextnd);
//         for (int x = 0; x < m; x++)
//         {
//             printf("\n %d %d", x, m);

//             if ((t[i].d[min] < t[i].d[x]) && (min != i))
//             {
//                 min = x;
//             }
//         }
//         // exit(0);
//         if (t[i].nh[min] == target)
//         {
//             dist += t[i].d[min];
//             return dist;
//         }
//         dist = t[i].d[min] + distance(i, target, t[i].nh[min]);
//         return dist;
//     }
//     else
//     {
//         printf("\n In else ");
//         return t[i].d[target];
//     }
// }
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
        for (j = 0; j < m - 1; j++)
        {
            if ((t[i].d[j] < t[i].d[min]) && (choosed[j] == 0) && (i != j))
            {
                min = j;
                printf("\n %d %d - %d %d", t[i].d[j], t[i].d[min], i, min);
            }
        }
        if (i == m - 1)
        {
            min = i;
        }
        choosed[min] = 1;

        // after getting minimum weight perform relaxation for min node.
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
        else
        {
            for (j = 0; j < m; j++)
            {
                t[i].d[j] = t[j].d[i];
            }
        }
    }
    int num = m - 2;
    // for (i = 0; i < m; i++)
    // {
    //     for (j = 0; j < m; j++)
    //     {
    //         int target = t[i].nh[j];
    //         // k for next node.
    //         for (k = 0; k < m; k++)
    //         {
    //             dist = 9999999;
    //             printf("\n %d %d %d", i, j, t[i].nh[k]);
    //             if (i == target)
    //             {
    //                 dist = 0;
    //             }
    //             else
    //             {
    //                 dist = distance(i, target, t[i].nh[k]);
    //             }
    //             if (dist < t[i].d[j])
    //             {
    //                 printf("\n Hi %d %d", dist, t[i].d[j]);
    //                 t[i].d[j] = dist;
    //             }
    //         }

    // }

    // }
    printf("\nMinimum distances : \n");
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
