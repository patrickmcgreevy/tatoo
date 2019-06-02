#include <iostream>
#include <string>

using namespace std;
int main()
{
    string input;
    getline(cin, input);

    if(input == "1")
    {
        cout << "I GOT THE MONEY" << endl;
    }
    else
    {
        cout << "i'm poor" << endl;
    }
    
}