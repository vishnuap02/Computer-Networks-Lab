// cs20b1129
// Vishnu abhay Parvatkar

#include <stdio.h>
#include <stdlib.h>
int size = 10;
int store[10] = {0}; // store is array where data is stored.

int *receiver(int sendarr[], int i, int j)
{
    int k = 0;
    int *p, ctr = 0;
    p = (int *)malloc((j - i + 1) * sizeof(int));

    int ch;
    for (int x = i; x <= j; x++)
    {
        printf("\n Press 1 if want to store %d else 0 : ", sendarr[k]);

        scanf("%d", &ch);
        if (ch == 1)
        {
            *(p + ctr) = x;
            store[x] = sendarr[k];
        }
        else
        {
            *(p + ctr) = -1;
        }
        k++;
        // printf(" %d ",*(p+ctr));
        ctr++;
    }

    return p;
}

void sender(int n, int data[])
{
    int i = 0, j = n - 1;
    for (int i = 0; i < size; i++)
    {
        printf("%d ", data[i]);
    }
    // int received=0; // this is used to keep track in loop wether ACK is received in sender. which is used as timeout.
    while (1)
    {
        int sendarr[n], x = 0;
        // storing elements in a array to send to recever side.
        for (int k = i; k <= j; k++)
        {
            sendarr[x++] = data[k];
        }
        int *p = receiver(sendarr, i, j);
        // below snippet will check ACK received and updates 'FRAME'
        // below also shows cumulative ack.

        int max = -1;
        for (int x = 0; x < n; x++)
        {
            // printf(" %d ",*(p+x));
            if (*(p + x) >= i || *(p + x) <= j)
            {
                max = *(p + x);
                printf("\n %d ", max);
            }
        }
        if (max == -1)
        {
            printf("\n Invalid ACK or may be noice , so neglet and hear to receuiver agin!");
            continue;
        }
        // for(int k=i;k<=j;k++){
        // for(int x=0;x<=n;x++){
        // if(*(p+x)==k){
        i = max + 1;
        j = i + n - 1;
        //}
        //}
        //}
        // if index goes beyond size ten exit
        if (j >= size)
        {
            printf("\n sent all data successfuly , exiting!");
            break;
        }
        // after this loop ends it considers timeout so sends same data to it nd waits again for acknowledgement.
    }
}

int main()
{
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //	for(int i=0;i<n;i++){
    //	scanf("%d",&data[i]);
    //	}

    int n;
    printf("\n Enter frame size : ");
    scanf("%d", &n);
    sender(n, data);
    printf("\n stored till now : ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", store[i]);
    }
    return 0;
}
