// Vishnu Abhay Parvatikar
// cs20b1129

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define IPSIZE 15
int allsubnt[100][4], k = 0;
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
void idclass(int iparr[], int n)
{
    // if ((iparr[0] < 255) || (iparr[1] < 255) || (iparr[2] < 255) || (iparr[3] < 255))
    // {
    //     printf("\n Invalid IP address");
    //     printf("\n Exiting!");
    //     exit(0);
    // }
    int noh = ((pow(2, 24)) / n) - (2 * n);
    printf("\n The number of Hosts is %d ", noh);
    printf("\n The number of HIP address is %d ", pow(2, 24) / n);
    if (iparr[0] <= 127)
    {
        printf("\n Belongs to Class A");

        int defmk[4], subnt[4], l;
        defmk[0] = 255;
        defmk[1] = 0;
        defmk[2] = 0;
        defmk[3] = 0;
        for (int i = 0; i < 4; i++)
        {
            subnt[i] = iparr[i] & defmk[i];
            // printf("%d.", subnt[i]);
        }
        l = 256 / n;
        // storing all subnets
        for (int i = 0; i < n; i++)
        {
            int j = 0;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = i * l;
            j++;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = subnt[j];
            j++;
            k++;
        }
        printf("\n \t\t\t\t ROUTING TABLE\n FROM HID | TO HID | DIRECT BROADCAST | LIMITED BROADCAST | INTERFACE");

        for (int i = 0; i < k; i++)
        {
            int val = 255;
            // printf("\n The %dth subnet range is  :  %d.%d.%d.%d  to %d.%d.%d.%d", i + 1, allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3], allsubnt[i][0], allsubnt[i][1] + l - 1, val, val);
            // printf("\n The number of HIP address is %d ", pow(2, 24) / n);
            // printf("\n The number of Hosts is %d ", noh);
            // printf("\n The direct broadcast is %d.%d.255.255 \n The limited broadcast is 255.%d.255.255", iparr[0], allsubnt[i][1] + l - 1, allsubnt[i][1] + l - 1);
            printf("\n %d.%d.%d.%d  | %d.%d.%d.%d | ", allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3], allsubnt[i][0], allsubnt[i][1] + l - 1, val, val);

            printf(" %d.%d.255.255 | 255.%d.255.255 | I%d", iparr[0], allsubnt[i][1] + l - 1, allsubnt[i][1] + l - 1, i);
        }
        // printf("\n Belongs to Class A");
        // int noh = pow(2, 24);
        // printf("\n The number of Hosts is %d ", noh);
        // int db, lb;
        // db=iparr[0]
    }
    else if (iparr[0] <= 191)
    {
        printf("\n Belongs to Class B");

        int defmk[4], subnt[4], l;
        defmk[0] = 255;
        defmk[1] = 255;
        defmk[2] = 0;
        defmk[3] = 0;
        for (int i = 0; i < 4; i++)
        {
            subnt[i] = iparr[i] & defmk[i];
            // printf("%d.", subnt[i]);
        }
        l = 256 / n;
        // storing all subnets
        printf("\n \t\t\t\t ROUTING TABLE\n FROM HID | TO HID | DIRECT BROADCAST | LIMITED BROADCAST | INTERFACE");

        for (int i = 0; i < n; i++)
        {
            int j = 0;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = i * l;
            j++;
            allsubnt[k][j] = subnt[j];
            j++;
            k++;
        }
        int noh = ((pow(2, 16)) / n) - (2 * n);
        for (int i = 0; i < k; i++)
        {
            int val = 255;
            // printf("\n The %dth subnet range is  :  %d.%d.%d.%d  to %d.%d.%d.%d", i + 1, allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3], allsubnt[i][0], allsubnt[i][1], allsubnt[i][2] + l - 1, val);
            // printf("\n The number of HIP address is %d ", pow(2, 16) / n);
            // printf("\n The number of Hosts is %d ", noh);
            // printf("\n The direct broadcast is %d.%d.%d.255 \n The limited broadcast is 255.255.%d.255", iparr[0], iparr[1], allsubnt[i][2] + l - 1, allsubnt[i][2] + l - 1);
            printf("\n  %d.%d.%d.%d  | %d.%d.%d.%d | ", allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3], allsubnt[i][0], allsubnt[i][1], allsubnt[i][2] + l - 1, val);
            printf(" %d.%d.%d.255 | 255.255.%d.255 | I%d", iparr[0], iparr[1], allsubnt[i][2] + l - 1, allsubnt[i][2] + l - 1, i);
        }
    }
    else if (iparr[0] <= 223)
    {
        printf("\n Belongs to Class C");

        int defmk[4], subnt[4], l;
        defmk[0] = 255;
        defmk[1] = 255;
        defmk[2] = 255;
        defmk[3] = 0;
        for (int i = 0; i < 4; i++)
        {
            subnt[i] = iparr[i] & defmk[i];
            // printf("%d.", subnt[i]);
        }
        l = 256 / n;
        // storing all subnets
        for (int i = 0; i < n; i++)
        {
            int j = 0;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = subnt[j];
            j++;
            allsubnt[k][j] = i * l;
            j++;
            k++;
        }
        int noh = ((pow(2, 8)) / n) - (2 * n);
        printf("\n \t\t\t\t ROUTING TABLE \n FROM HID | TO HID | DIRECT BROADCAST | LIMITED BROADCAST | INTERFACE");
        for (int i = 0; i < k; i++)
        {
            int val = 255;
            // printf("\n The %dth subnet range is  :  %d.%d.%d.%d  to %d.%d.%d.%d", i + 1, allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3], allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3] + l - 1);
            // printf("\n The number of HIP address is %d ", pow(2, 8) / n);
            // printf("\n The number of Hosts is %d ", noh);
            // printf("\n The direct broadcast is %d.%d.%d.%d \n The limited broadcast is 255.255.%d.255", iparr[0], iparr[1], iparr[2], allsubnt[i][3] + l - 1, allsubnt[i][3] + l - 1);
            printf("\n %d.%d.%d.%d  | %d.%d.%d.%d | ", allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3], allsubnt[i][0], allsubnt[i][1], allsubnt[i][2], allsubnt[i][3] + l - 1);
            printf(" %d.%d.%d.%d | 255.255.%d.255 | I%d", iparr[0], iparr[1], iparr[2], allsubnt[i][3] + l - 1, allsubnt[i][3] + l - 1, i);
        }
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
    int iparr[4], n;
    str = (char *)malloc(IPSIZE * sizeof(char));
    printf("\n Enter IP address : ");
    scanf("%s", str);
    printf("\n Enter number of subnets : ");
    scanf("%d", &n);
    int lens = strlen(str), j = 0, k = 0;
    strtointip(str, lens, iparr);
    for (int i = 0; i < 4; i++)
    {
        printf("%d.", iparr[i]);
    }
    printf("\n Identifying Class : ");
    idclass(iparr, n);
    int ipbinarr[4][8] = {0};

    return 0;
}