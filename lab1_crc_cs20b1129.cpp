// CS20B1129 Vishnu Abhay Parvatikar.
// Lab-1 , Cyclic Redundancy Check.

#include <iostream>
#include <string.h>
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
        // Below calling XOR bitwise divisor method and getting remainder
        // to check Check if error persists or not.
        string rem;
        rem = xordivision(decodedmsg, key);
        cout << "\n The received remainder after dividing decode message is : " << rem;
        // to check and compare received remainder whether it's value is 0 , we need
        // to iterate and check if there exists a bit '1'.
        for (int i = 0; i < key.length(); i++)
        {
            if (rem[i] != '0')
            {
                return "\n  <--- Error Detected !!--->";
            }
        }
        return "\n SUCCESS..";
    }
};

int main()
{
    // Below line generating Object of 'Class CRC'
    CRC c;
    string message, key, successMsg;
    cout << "Enter messqage and key : ";
    std::cin >> message >> key;
    string encodedmsg;
    encodedmsg = c.encodeMessage(message, key);
    cout << "\n The encoded message is : " << encodedmsg;
    successMsg = c.decodeMessage(key);
    cout << successMsg;
    return 0;
}
