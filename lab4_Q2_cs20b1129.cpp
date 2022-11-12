#include <iostream>
#include <string>
using namespace std;

class bitStuff
{
    int encoded[100];

public:
    int operation(string data)
    {
        int len = data.length(), n, k, j, x, y, blocks;
        cout << "\n Enter number continupous 1s : ";
        cin >> n;
        // k = len / n;
        j = 0;
        // x = 0;
        y = 0;
        blocks = 0;
        for (int i = 0; i < len; i++)
        {
            if (data[i] == '1')
            {
                encoded[j++] = 1;
                y++;
            }
            else
            {
                encoded[j++] = 0;
                y = 0;
            }
            // if (data[i] == '1')
            // {
            //     x++;
            // }
            // y++;
            // The below condition will look after that n-1 blocks contain len/n data , except the last one
            if (y == n)
            {
                encoded[j++] = 0;
                y = 0;
                x = 0;
                // j++;
                // blocks++;
            }
            // if ((i == len - 1) && (blocks == n - 1))
            // {
            //     encoded[j - k - 1] = x;
            // }
        }
        return j;
    }
    void printEncodedData(int n)
    {
        cout << "\n Encoded Bit Stuff : " << endl;
        for (int i = 0; i < n; i++)
        {
            cout << encoded[i] << " ";
        }
    }
};
class charCount
{
    int encoded[100];

public:
    int operation(string data)
    {
        int len = data.length(), n, k, j, x, y;
        cout << "\n Enter number of division of blocks : ";
        cin >> n;
        k = len / n;
        j = 1;
        x = 0;
        y = 1;
        for (int i = 0; i < len; i++)
        {
            if (data[i] == '1')
                encoded[j++] = 1;
            else
            {
                encoded[j++] = 0;
            }
            x++;
            if (y == n)
            {
                encoded[(y - 1) * k] = x;
            }
            if (x == k)
            {

                y++;
                encoded[j - k - 1] = x;
                j++;
                x = 0;
            }
        }
        return j;
    }
    void printEncodedData(int n)
    {
        cout << "\n Encoded Bit Stuff : " << endl;
        for (int i = 0; i < n; i++)
        {
            cout << encoded[i] << " ";
        }
    }
};
class bytestuff
{
public:
    void operation(string data)
    {
        char st, end;
        cout << "\n Enter starting character and ending character : ";
        cin >> st >> end;
        char final[100];
        int j = 0;
        final[j++] = st;
        for (int i = 0; i < data.length(); i++)
        {
            if ((data[i] == st) || (data[i] == end))
            {
                final[j++] = data[i];
            }
            final[j++] = data[i];
        }
        final[j++] = end;
        cout << "\n The encoded Byte stuffed string is : ";
        for (int i = 0; i < j; i++)
        {
            cout << final[i];
        }
    }
};
int main()
{
    bitStuff bs;
    bytestuff by;
    charCount cc;
    string data;
    cout << "Enter data : ";
    cin >> data;
    cout << "\n Bit stuffing \n";
    int encsize = bs.operation(data);
    bs.printEncodedData(encsize);
    cout << "\n Character count \n";
    int n = cc.operation(data);
    cc.printEncodedData(n);
    cout << "\n Byte stuffing , Enter data preferrably in characters \n";
    cin >> data;
    by.operation(data);
    return 0;
}