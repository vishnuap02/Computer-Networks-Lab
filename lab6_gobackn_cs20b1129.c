// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int chkack(int ackmt[], int n)
{
    int val = 1;
    for (int i = 0; i < n; i++)
    {
        if (ackmt[i] == 1)
            continue;
        else
        {
            return 0;
        }
    }
    return val;
}
int main(int argc, char const *argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char *hello;
    // Below is the message to be sent.

    // Below vars st,end to track sliding window, n for window size.
    int st, end, n, m;
    int ack[1024] = {0}, ackctr = 0;
    printf("\n Enter Data size : ");
    scanf("%d", &m);
    // char *msg;
    // msg=(char*)malloc(m*(sizeof(char)));
    char msg[] = {'1', '2', '3', '4'};
    // for (int j = 0; j < m; j++)
    //       {
    //      printf("\n Enter %dth data item",j);
    //        scanf("%c",msg+j);
    //     }
    for (int j = 0; j < m; j++)
    {
        printf("\n %dth item : %c", j, msg[j]);
    }
    printf("\n Enter Sliding window size : ");
    scanf("%d", &n);

    st = 0;
    end = st + n - 1;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr,
                             sizeof(serv_addr))) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    // To count number of times
    int count = 0;
    for (int i = 0; i < strlen(msg); i++)
    {
        int ackmt[10] = {0};
        // if all acknowledgement not received , then repeat the process.
        while (chkack(ackmt, n) == 0)
        {
            int k = st;
            // all ackmt must be made =0 here.
            for (int j = st; j <= end; j++)
            {
                count++;

                // How to give value in character array of msg into hello variable ptr.
                sleep(1);
                // sprintf(hello,"%d",count);
                char ch = msg[j];
                // printf("\n %d is typecasting of msg.",atoi(&msg[k]));
                hello = &ch;
                send(sock, hello, strlen(hello), 0);
                // sleep(1);
                // printf("Hello message sent\n");
                //  There is error in below line
                //*hello = '1';
                // why below line is not rinting
                printf("Sending %s\n", hello);
                valread = read(sock, buffer, 1024);
                printf("Acknowledgement of %s\n", buffer);
                int recmsg = atoi(buffer);
                printf("%d is acknowledged received!", recmsg);
                char msgk = msg[k];
                if ((recmsg != 0) && (recmsg == atoi(&msgk)))
                {
                    ackmt[k - st] = 1;
                    k++;
                }
            }
            printf("%d is op if all are acknowledged", chkack(ackmt, n));
        }
        // moving sliding window
        st = st + n;
        end = st + n - 1;
        // printf("--> %s <--\n",hello);
    }
    printf("no.of times : %d", count);
    // closing the connected socket
    close(client_fd);
    return 0;
}
