#include <iostream>
#include <string.h>
using namespace std;

class VRC
{

public:
    string encodedmsg, decodedmsg;
    void parityAdder(string parts[], int n)
    {
        // Here i use Odd PArity generater and append it to each part.
        for (int j = 0; j < 4; j++)
        {
            int parCount = 0;

            for (int i = 0; i < n; i++)
            {
                if (parts[j][i] == '1')
                {
                    parCount += 1;
                }
            }
            // Appending 1 if there are even number of 1s.
            if (parCount % 2 == 0)
            {
                parts[j] += '1';
            }
            else
            {
                parts[j] += '0';
            }
        }
    }
    int encodeMessage(string message, string parts[])
    {
        encodedmsg = message;
        int len = message.size();
        // string divd = dividend;
        int n = len / 4;
        // Dividing into 4 parts into string arrays.
        for (int i = 0; i < 4; i++)
        {
            parts[i] = "";
        }
        int k = 0;
        for (int i = 0; i < len; i++)
        {

            parts[k] += message[i];
            // cout << message[i];
            if (((i + 1) % n) == 0)
            {
                k++;
            }
        }
        parityAdder(parts, n);
        for (int i = 0; i < 4; i++)
        {
            cout << parts[i] << endl;
        }

        return n;
    }
    string decodeMessage(string parts[], int n)
    {
        cout << "\n \n \n Enter String received from Encoder is : ";
        cin >> decodedmsg;
        int len = decodedmsg.size();
        // string divd = dividend;
        string decparts[4];

        // Dividing into 4 parts into string arrays.
        for (int i = 0; i < 4; i++)
        {
            decparts[i] = "";
        }
        int k = 0;
        for (int i = 0; i < len; i++)
        {
            decparts[k] += decodedmsg[i];
            // cout << message[i];
            if (((i + 1) % n) == 0)
            {
                k++;
            }
        }
        parityAdder(decparts, n);
        for (int i = 0; i < 4; i++)
        {
            cout << decparts[i] << endl;
        }

        // Below check both encoded and decode parities;
        bool paritycheck = true;
        for (int i = 0; i < 4; i++)
        {
            if (decparts[i][n] == parts[i][n])
                continue;
            else
            {
                paritycheck = false;
                cout << "\n At index " << i << " decoded is different from encoded !";

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
    VRC c;
    string message, key, successMsg;
    cout << "Enter message : ";
    std::cin >> message;
    string parityString;
    int hi;
    string parts[4];

    int sizepart;
    sizepart = c.encodeMessage(message, parts);
    // cout << "\n The parity bit message is : " << parityString;
    successMsg = c.decodeMessage(parts, sizepart);
    cout << successMsg;
    return 0;
}
