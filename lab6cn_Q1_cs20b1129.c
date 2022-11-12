#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define IPSIZE 15
void coverttobin(int iparr[], int ipbinarr[4][8])
{
    for (int i = 0; i < 4; i++)
    {
        int m = iparr[i], rem, j = 7;
        while (m > 0)
        {
            rem = m % 2;
            m /= 2;
            ipbinarr[i][j--] = rem;
        }
    }
}
void strtointip(char *str, int lens, int iparr[])
{
    int k = 0, j = 0;
    for (int i = 0; i < lens; i++)
    {
        if (str[i] == 'x')
        {
            k = 0;
            continue;
        }
        if (str[i] == '.')
        {
            iparr[j++] = k;
            k = 0;
            continue;
        }
        int m = str[i];
        k *= 10;
        k += m - 48;
        // printf("%d ", k);
    }
    iparr[j++] = k;
}
void idclass(int iparr[])
{
    // if ((iparr[0] < 255) || (iparr[1] < 255) || (iparr[2] < 255) || (iparr[3] < 255))
    // {
    //     printf("\n Invalid IP address");
    //     printf("\n Exiting!");
    //     exit(0);
    // }
    if (iparr[0] <= 127)
    {
        printf("\n Belongs to Class A");
    }
    else if (iparr[0] <= 191)
    {
        printf("\n Belongs to Class B");
    }
    else if (iparr[0] <= 223)
    {
        printf("\n Belongs to Class C");
    }
    else if (iparr[0] <= 239)
    {
        printf("\n Belongs to Class D");
    }
    else if (iparr[0] <= 255)
    {
        printf("\n Belongs to Class E");
    }
    else
    {
        printf("\n Invalid IP address");
        printf("\n Exiting!");
        exit(0);
    }
}
int main()
{
    char *str;
    int iparr[4];
    str = (char *)malloc(IPSIZE * sizeof(char));
    printf("\n Enter IP address : ");
    scanf("%s", str);
    int lens = strlen(str), j = 0, k = 0;
    strtointip(str, lens, iparr);
    for (int i = 0; i < 4; i++)
    {
        printf("%d.", iparr[i]);
    }
    printf("\n Identifying Class : ");
    idclass(iparr);
    int ipbinarr[4][8] = {0};
    coverttobin(iparr, ipbinarr);
    printf("\n The binary representation of IP address is : \n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d", ipbinarr[i][j]);
        }
        if (i < 3)
        {
            printf(".");
        }
    }
    return 0;
}