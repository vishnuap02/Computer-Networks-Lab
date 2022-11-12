// Vishnu Abhay Parvatikar
// cs20b1129
#include <iostream>
// #include <stdlib.h>
using namespace std;
class saw
{
public:
    void sender(int frames)
    {
        // Send 1 frame at a time to reciever
        int count = 1;
        int response = 0;
        while (count < frames + 1)
        {
            response = 0;
            cout << "Send The frame " << count << endl;
            cout << "Wait for response \n";
            response = reciever(count);
            if (response == 1)
            {
                cout << "Recieved ACK " << count << endl;

                count++;
            }
            else
            {
                cout << "\n again send " << count;
            }
        }
    }
    int reciever(int value)
    {
        int v;
        int even = 0; // for showcasing different cases.

        do
        {
            v = rand() % 10000;
            if (v % 2 == 0)
            {
                even = 1;
            }
            cout << "Waiting \n";
        } while (even != 1);
        cout << "\n Sending ACK for " << value;
        // sleep(1);
        cout << "\n Enter 1 to confirm acknowledgement , else 0 : ";
        int val;
        cin >> val;
        if (val == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

int main()
{
    saw s;
    int input;
    printf("Enter the number of frames you want to send \n");
    scanf("%d", &input);
    s.sender(input);
    return 0;
}