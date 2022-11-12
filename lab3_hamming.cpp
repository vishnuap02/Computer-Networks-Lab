#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

class hamming
{
public:
    int totlen, encodedarr[1024], decodearr[1024], message[1024], parity[512], decpa;
    void genHamming(int len, int totlen)
    {
        int x = 0;
        for (int i = 0; i < totlen; i++)
        {

            if (encodedarr[i] != -1)
                continue;

            int x = log2(i + 1); // this will take to previous bit which is multiple of 2, means its power , i.e if i=4 , x=2
            int one_count = 0;

            for (int j = i + 2;
                 j <= totlen; ++j)
            {

                if (j & (1 << x)) // from that bit till next multiple of 2 bit  check if it must be present, ex: x=2 , 1<<x = 4
                // then j= 6 to 7 and 6 & 4 , which is 4 , so positive , similarly this will work for hamming conditin
                {
                    if (encodedarr[j - 1] == 1)
                    {
                        one_count++;
                    }
                }
            }

            // even parity
            if (one_count % 2 == 1)
            {
                encodedarr[i] = 1;
                parity[x++] = 1;
            }
            else
            {
                encodedarr[i] = 0;
                parity[x++] = 1;
            }
        }
    }
    void decodeHamming()
    {

        string decodestring;
        cout << "\n Enter code at receivers end : ";
        cin >> decodestring;
        for (int i = 0; i < totlen; i++)
        {
            if (decodestring[i] != encodedarr[i])
            {
                cout << "\n Error found in decode part ";
                break;
            }
        }

        // int position = 0;
        // for (int i = 0; i < totlen; i++)
        // {

        //     if (decodearr[i] != -1)
        //         continue;

        //     int x = log2(i + 1);
        //     int one_count = 0;

        //     for (int j = i;
        //          j <= totlen; ++j)
        //     {

        //         if (j & (1 << x))
        //         {
        //             if (decodearr[j - 1] == 1)
        //             {
        //                 one_count++;
        //             }
        //         }
        //     }

        //     // odd parity
        //     // if (one_count % 2 == 1)
        //     // {
        //     //     position += position + pow(2, i + 1);
        //     // }
        //     // else
        //     // {
        //     //     encodedarr[i] = 0;
        //     // }
        //     if (one_count % 2 == 1)
        //     {
        //         decodearr[i] = 1;
        //     }
        //     else
        //     {
        //         decodearr[i] = 0;
        //     }
        // }
        // cout << "\n At position " << position << " bit is changed!";
    }
    void encodeMessage(int len)
    {
        int k = 1, times = 1;
        while (k < len)
        {
            k = k * 2;
            times++;
        }
        // The length of encoded message is times+len
        totlen = times + len;
        int j;
        k = 1;
        j = totlen;
        // Filling the values to avoid filling in parity bits
        for (int i = totlen - 1; i >= 0; i--)
        {
            if (j - i == k)
            {
                encodedarr[i] = -1;
                k = k * 2;
            }
        }
        j = 0; // j is index of data
        for (int i = 0; i < totlen; i++)
        {
            if (encodedarr[i] == -1)
                continue;
            encodedarr[i] = message[j++];
        }
        for (int i = 0; i < totlen; i++)
        {
            cout << encodedarr[i];
        }
        cout << endl;
        for (int i = 0; i < totlen / 2; i++)
        {
            int temp = encodedarr[i];
            encodedarr[i] = encodedarr[totlen - i - 1];
            encodedarr[totlen - i - 1] = temp;
        }
        cout << endl;
        // Below is Function inserting parity bits according to odd parities

        for (int i = 0; i < totlen; i++)
        {
            cout << encodedarr[i];
        }
        cout << endl;
        genHamming(len, totlen);
        for (int i = 0; i < totlen / 2; i++)
        {
            int temp = encodedarr[i];
            encodedarr[i] = encodedarr[totlen - i - 1];
            encodedarr[totlen - i - 1] = temp;
        }
        for (int i = 0; i < totlen; i++)
        {
            cout << encodedarr[i];
        }
    }
    void decodeMessage(int len)
    {
        cout << "\n Enter data at receivers end : ";
        // cout << len;
        for (int i = 0; i < len; i++)
        {
            cin >> decodearr[i];
        }
        for (int i = 0; i < totlen / 2; i++)
        {
            int temp = decodearr[i];
            decodearr[i] = decodearr[totlen - i - 1];
            decodearr[totlen - i - 1] = temp;
        }
        cout << endl;
        decodeHamming();
        for (int i = 0; i < totlen / 2; i++)
        {
            int temp = decodearr[i];
            decodearr[i] = decodearr[totlen - i - 1];
            decodearr[totlen - i - 1] = temp;
        }
        for (int i = 0; i < totlen; i++)
        {
            cout << decodearr[i];
        }
    }
};

int main()
{
    hamming h;
    int n;
    cout << "\n Length of data : ";
    cin >> n;
    cout << "\n Enter data (Line by line)";
    for (int i = 0; i < n; i++)
    {
        cin >> h.message[i];
    }
    h.encodeMessage(n);
    h.decodeMessage(n);
    return 0;
}