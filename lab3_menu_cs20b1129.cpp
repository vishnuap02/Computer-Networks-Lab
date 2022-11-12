#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
class CRC
{

public:
    string encodedmsg, decodedmsg;
    string xorBitwise(string x, string y)
    {
        string op = "";

        int nobits = y.length();
        // In below iteration it loops number_of_bits - 1 times & we dont consider
        // 1st bit i.e MSB as the function which called this is passing x & y such that
        for (int i = 1; i < nobits; i++)
        {
            if (x[i] == y[i])
                op += "0";
            else
                op += "1";
        }
        return op;
    }

    string xordivision(string dividend, string divisor)
    {
        int cursor = divisor.size();
        int n = dividend.size();
        string partdiv;
        // Below line zeroes string helps in adding string when rightmost bit is 0;
        string zeroes;
        zeroes = '\0';
        for (int i = 1; i < cursor; i++)
            zeroes += '0';
        partdiv = dividend.substr(0, cursor);
        for (int i = cursor; i < n; i++)
        {
            // 	cout<<"\n"<<partdiv<<" \t"<<partdiv.size();
            if (partdiv[0] == '1')
            {
                // 	cout<<"\n Before addition :"<<xorBitwise(partdiv,divisor);
                partdiv = xorBitwise(partdiv, divisor) + dividend[i];
                // 	cout<<"\n I am in 1 Dividend : "<<partdiv;
            }
            else
            {
                // 	cout<<"\n Before addition :"<<partdiv<<"\t"<<xorBitwise(partdiv,zeroes);

                partdiv = xorBitwise(partdiv, zeroes) + dividend[i];
                // cout<<"\n  I am in 0 Dividend : "<<partdiv;
            }
        }
        // except last xordivision operation , it weill be done.
        if (partdiv[0] == '1')
            partdiv = xorBitwise(partdiv, divisor);
        else
        {
            partdiv = xorBitwise(partdiv, zeroes);
        }
        return partdiv;
    }

    string encodeMessage(string dividend, string divisor)
    {
        int len = divisor.size();
        string divd = dividend;
        // 	dividend.copy(divd,len,0);
        // 	cout<<divd;
        // cout<<len;
        for (int i = 0; i < len - 1; i++)
        {
            dividend += '0';
        }
        // std::cout << dividend << std::endl;

        string rem;
        rem = xordivision(dividend, divisor);
        cout << "\n The reaminder for Xor bitwise division : " << rem << endl;
        // 		cout<<divd<<endl;

        encodedmsg = divd + rem;

        return encodedmsg;
    }
    string decodeMessage(string key)
    {
        decodedmsg = encodedmsg;
        cout << "\n \n \n String received from Encoder is : " << encodedmsg;
        int msgInd;
        cout << "\n Enter which index to modify in encoded message : ";
        cin >> msgInd;
        cout << "\n Enter the value to be stored in that indexed bit (0 or 1 only)";
        int val;
        cin >> val;
        if (val == 0)
        {
            decodedmsg[msgInd] = '0';
        }
        else if (val == 1)
        {
            decodedmsg[msgInd] = '1';
        }
        else
        {
            cout << "\n Invalid Bit , So Encoded Message is Unchanged . ";
        }
        cout << decodedmsg << endl;
        // Below calling XOR bitwise divisor method and getting remainder
        // to check Check if error persists or not.
        string rem;
        rem = xordivision(decodedmsg, key);
        cout << "\n The received remainder after dividing decode message is : " << rem;
        // to check and compare received remainder whether it's value is 0 , we need
        // to iterate and check if there exists a bit '1'.
        for (int i = 0; i < key.length() - 1; i++)
        {
            // cout << rem[i];
            if (rem[i] == '1')
            {
                return "\n  <--- Error Detected !!--->";
            }
        }
        return "\n SUCCESS..";
    }
};
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
class checksum
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
class hamming
{
public:
    int totlen, encodedarr[1024], decodearr[1024], message[1024], parity[512];
    void genHamming(int len, int totlen)
    {
        for (int i = 0; i < totlen; i++)
        {

            if (encodedarr[i] != -1)
                continue;

            int x = log2(i + 1);
            int one_count = 0;

            for (int j = i + 2;
                 j <= totlen; ++j)
            {

                if (j & (1 << x))
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
            }
            else
            {
                encodedarr[i] = 0;
            }
        }
    }
    void decodeHamming()
    {
        int position = 0;
        for (int i = 0; i < totlen; i++)
        {

            if (decodearr[i] != -1)
                continue;

            int x = log2(i + 1);
            int one_count = 0;

            for (int j = i;
                 j <= totlen; ++j)
            {

                if (j & (1 << x))
                {
                    if (decodearr[j - 1] == 1)
                    {
                        one_count++;
                    }
                }
            }

            // even parity
            if (one_count % 2 == 0)
            {
                position += position + pow(2, i + 1);
            }
            // else
            // {
            //     encodedarr[i] = 0;
            // }
        }
        cout << "\n At position " << position << " bit is changed!";
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
    void decodeMessage()
    {
        cout << "\n Enter data at receivers end : ";
        for (int i = 0; i < totlen; i++)
        {
            cin >> decodearr[i];
        }
        for (int i = 0; i < totlen / 2; i++)
        {
            int temp = decodearr[i];
            decodearr[i] = decodearr[totlen - i - 1];
            decodearr[totlen - i - 1] = temp;
        }
        decodeHamming();
    }
};

int main()
{
    while (1)
    {
        int ch;
        cout << "\n Enter choice \n 1) CRC \n 2) VRC \n 3) LRC \n 4) Checksum \n 5)Hamming : ";
        cin >> ch;
        CRC c;
        VRC v;
        LRC l;
        checksum ck;
        hamming h;
        string message, key, successMsg;
        string encodedmsg, parityString, parts[4];
        int n, sizepart;
        switch (ch)
        {
        case 1:
            cout << "Enter messqage and key : ";
            std::cin >> message >> key;
            encodedmsg = c.encodeMessage(message, key);
            cout << "\n The encoded message is : " << encodedmsg;
            successMsg = c.decodeMessage(key);
            cout << successMsg;
            break;
        case 2:
            cout << "Enter message : ";
            std::cin >> message;
            int hi;

            int sizepart;
            sizepart = v.encodeMessage(message, parts);
            // cout << "\n The parity bit message is : " << parityString;
            successMsg = v.decodeMessage(parts, sizepart);
            cout << successMsg;
            break;
        case 3:
            cout << "Enter message : ";
            std::cin >> message;
            sizepart = l.encodeMessage(message);
            // cout << "\n The parity bit message is : " << parityString;
            successMsg = l.decodeMessage(sizepart);
            cout << successMsg;
            break;
        case 4:
            cout << "Enter message : ";
            std::cin >> message;
            sizepart = ck.encodeMessage(message);
            successMsg = ck.decodeMessage(sizepart);
            cout << successMsg;
            break;
        case 5:
            cout << "\n Length of data : ";
            cin >> n;
            cout << "\n Enter data (Line by line)";
            for (int i = 0; i < n; i++)
            {
                cin >> h.message[i];
            }
            h.encodeMessage(n);
            h.decodeMessage();
            break;
        default:
            cout << "\n Exiting !!";
            return 0;
        }
    }
    return 0;
}
