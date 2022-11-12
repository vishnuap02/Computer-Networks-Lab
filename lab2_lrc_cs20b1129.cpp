#include <iostream>
#include <string.h>
using namespace std;

class LRC
{

public:
    string encodedmsg, decodedmsg;
    int parts[5][100], decparts[5][100];
    void parityAdderEncoder(int n)
    {
        // Here i use Odd PArity generater and append it to each part.
        for (int j = 0; j < n; j++)
        {
            int parCount = 0;

            for (int i = 0; i < 4; i++)
            {
                if (parts[i][j] == 1)
                {
                    parCount += 1;
                }
            }
            // Appending 1 if there are even number of 1s.
            if (parCount % 2 == 0)
            {
                parts[4][j] = 1;
            }
            else
            {
                parts[4][j] = 0;
            }
        }
    }
    void parityAdderDecoder(int n)
    {
        // Here i use Odd PArity generater and append it to each part.
        for (int j = 0; j < n; j++)
        {
            int parCount = 0;

            for (int i = 0; i < 4; i++)
            {
                if (decparts[i][j] == 1)
                {
                    parCount += 1;
                }
            }
            // Appending 1 if there are even number of 1s.
            if (parCount % 2 == 0)
            {
                decparts[4][j] = 1;
            }
            else
            {
                decparts[4][j] = 0;
            }
        }
    }
    int encodeMessage(string message)
    {
        encodedmsg = message;
        int len = message.size();
        // string divd = dividend;
        int n = len / 4;
        // Dividing into 4 parts into string arrays.
        int k = 0, j = 0;
        for (int i = 0; i < len; i++)
        {
            if (message[i] == '1')
            {
                parts[k][j] = 1;
                // cout << parts[k][j];
            }
            else
            {
                parts[k][j] = 0;
                // cout << parts[k][j];
            }
            // the below logic will help to store values in terms of block.
            if (((i + 1) % n) == 0)
            {
                k++;
                j = 0;
                cout << endl;
                continue;
            }
            j++;
        }
        parityAdderEncoder(n);
        cout << endl;

        for (int i = 0; i < 5; i++)
        {
            for (int x = 0; x < n; x++)
            {
                cout << parts[i][x] << " ";
            }
            cout << endl;
        }
        return n;
    }
    string decodeMessage(int n)
    {
        cout << "\n \n \n Enter String received from Encoder is : ";
        cin >> decodedmsg;
        int len = decodedmsg.size();
        // Dividing into 4 parts into string arrays.
        int k = 0, j = 0;
        for (int i = 0; i < len; i++)
        {
            if (decodedmsg[i] == '1')
            {
                decparts[k][j] = 1;
                // cout << decparts[k][j];
            }
            else
            {
                decparts[k][j] = 0;
                // cout << decparts[k][j];
            }
            // the below logic will help to store values in terms of block.
            if (((i + 1) % n) == 0)
            {
                k++;
                j = 0;
                cout << endl;
                continue;
            }
            j++;
        }
        parityAdderDecoder(n);
        cout << endl;
        cout << "Decoded : \n";
        for (int i = 0; i < 5; i++)
        {
            for (int x = 0; x < n; x++)
            {
                cout << decparts[i][x] << " ";
            }
            cout << endl;
        }
        bool paritycheck = true;
        for (int x = 0; x < n; x++)
        {
            if (decparts[4][x] == parts[4][x])
                continue;
            else
            {
                cout << "\n At index " << x << " decoded is different from encoded !";
                paritycheck = false;
                break;
            }
        }
        string stmt;
        if (paritycheck)
        {
            stmt = "Received Correct Input";
        }
        else
        {
            stmt = "Error!";
        }
        return stmt;
    }
};

int main()
{
    // Below line generating Object of 'Class CRC'
    LRC c;
    string message, key, successMsg;
    cout << "Enter message : ";
    std::cin >> message;
    int sizepart;
    sizepart = c.encodeMessage(message);
    // cout << "\n The parity bit message is : " << parityString;
    successMsg = c.decodeMessage(sizepart);
    cout << successMsg;
    return 0;
}
