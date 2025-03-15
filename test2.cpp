#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

void ShowLoginSccren()
{
    cout << "=======================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "=======================================\n";

    
    while (!CheckPasswordUserName(ReadUserName(), ReadPasswd()))
    {
        cout << "User Name Or Password is Wrong, Try again\n";
    }

}

int main(int ac, char **av)
{
    ShowLoginSccren();
    
}