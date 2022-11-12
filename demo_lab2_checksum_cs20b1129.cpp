#include <iostream>
#include <string.h>
using namespace std;

class LRC
{

public:
    string encodedmsg, decodedmsg;
    int parts[100][4], decparts[5][100], sumarray[4], totalsum[4];
    void inverseBinary(int invsum[])
    {
        for (int i = 0; i < 4; i++)
        {
            if (sumarray[i] == 1)
                invsum[i] = 0;
            else
            {
                invsum[i] = 1;
            }
        }
    }

    void parityAdderEncoder(int n)
    {

        // Here i use Odd Parity generater and append it to each part.
        int carry = 0, sum = 0;
        for (int j = 1; j < n; j++)
        {
            for (int i = 3; i >= 0; i--)
            {
                if (j == 1)
                {
                    sum = parts[j][i] + parts[j - 1][i] + carry;
                    cout << sum << "\n";
                }
                else
                {
                    sum = parts[j][i] + sumarray[i] + carry;
                    cout << sum << "\n";
                }
                if (sum == 0)
                {
                    sum = 0;
                    carry = 0;
                }
                else if (sum == 1)
                {
                    sum = 1;
                    carry = 0;
                }
                else if (sum == 2)
                {
                    sum = 0;
                    carry = 1;
                }
                else
                {
                    sum = 1;
                    carry = 1;
                }
                sumarray[i] = sum;
                if ((carry == 1) && (i == 0))
                {
                    cout << "\n Entering spl If \n";
                    i = 3;
                    int sum2;
                    while (carry == 1)
                    {
                        // cout << "hi ";
                        if (i == -1)
                        {
                            i = 3;
                        }
                        sum2 = sumarray[i] + carry;
                        if (sum2 == 0)
                        {
                            sum2 = 0;
                            carry = 0;
                        }
                        else if (sum2 == 1)
                        {
                            sum2 = 1;
                            carry = 0;
                        }
                        else if (sum2 == 2)
                        {
                            sum2 = 0;
                            carry = 1;
                        }
                        else
                        {
                            sum2 = 1;
                            carry = 1;
                        }
                        sumarray[i] = sum2;
                        i--;
                    }
                    i = 0;
                }
            }
            // Appending 1 if there are even number of 1s.
        }
        int invsum[4];
        inverseBinary(invsum);
        for (int i = 0; i < 4; i++)
        {
            cout << invsum[i] << " ";
            parts[n][i] = invsum[i];
        }
        cout << endl
             << endl;
    }
    void parityAdderDecoder(int n)
    {
        // Here i use Odd PArity generater and append it to each part.
        int carry = 0, sum = 0;
        for (int j = 1; j < n; j++)
        {
            for (int i = 3; i >= 0; i--)
            {
                if (j == 1)
                {
                    sum = decparts[j][i] + decparts[j - 1][i] + carry;
                    cout << sum << "\n";
                }
                else
                {
                    sum = decparts[j][i] + sumarray[i] + carry;
                    cout << sum << "\n";
                }
                if (sum == 0)
                {
                    sum = 0;
                    carry = 0;
                }
                else if (sum == 1)
                {
                    sum = 1;
                    carry = 0;
                }
                else if (sum == 2)
                {
                    sum = 0;
                    carry = 1;
                }
                else
                {
                    sum = 1;
                    carry = 1;
                }
                sumarray[i] = sum;
                if ((carry == 1) && (i == 0))
                {
                    cout << "\n Entering spl If \n";
                    i = 3;
                    int sum2;
                    while (carry == 1)
                    {
                        // cout << "hi ";
                        if (i == -1)
                        {
                            i = 3;
                        }
                        sum2 = sumarray[i] + carry;
                        if (sum2 == 0)
                        {
                            sum2 = 0;
                            carry = 0;
                        }
                        else if (sum2 == 1)
                        {
                            sum2 = 1;
                            carry = 0;
                        }
                        else if (sum2 == 2)
                        {
                            sum2 = 0;
                            carry = 1;
                        }
                        else
                        {
                            sum2 = 1;
                            carry = 1;
                        }
                        sumarray[i] = sum2;
                        i--;
                    }
                    i = 0;
                }
            }
            // Appending 1 if there are even number of 1s.
        }
        for (int i = 0; i < 4; i++)
        {
            cout << sumarray[i] << " ";
            decparts[n][i] = sumarray[i];
        }
        cout << endl;
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
                cout << parts[k][j];
            }
            else
            {
                parts[k][j] = 0;
                cout << parts[k][j];
            }
            // the below logic will help to store values in terms of block.
            if (((i + 1) % 4) == 0)
            {
                k++;
                j = 0;
                cout << endl;
                continue;
            }
            j++;
        }
        cout << "\n Entering parity Encoder \n";
        parityAdderEncoder(n);
        // cout << n << endl;

        for (int i = 0; i <= n; i++)
        {
            for (int x = 0; x < 4; x++)
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
                cout << decparts[k][j];
            }
            else
            {
                decparts[k][j] = 0;
                cout << decparts[k][j];
            }
            // the below logic will help to store values in terms of block.
            if (((i + 1) % 4) == 0)
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
        for (int i = 0; i <= n; i++)
        {
            for (int x = 0; x < 4; x++)
            {
                cout << decparts[i][x] << " ";
            }
            cout << endl;
        }
        bool paritycheck = true;
        for (int x = 0; x < 4; x++)
        {
            if ((decparts[n][x] + parts[n][x]) == 1)
                continue;
            else
            {
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
    successMsg = c.decodeMessage(sizepart);
    cout << successMsg;
    return 0;
}
