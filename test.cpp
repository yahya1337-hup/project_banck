#include <iostream>
#include <cstdlib>

using namespace std;

class clsStudent
{

private:
    string _FirstName;
    string _LastName;
    int _Age;

public:
    void setFistName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string getFirstName()
    {
        return _FirstName;
    }

    // __declspec(property(get = getFirstName, put = setFistName)) string FirstName;

    void setLastName(string LastName)
    {
        _LastName = LastName;
    }

    void setAge(short Age)
    {
        _Age = Age;
    }

    string LastName()
    {
        return _LastName;
    }

    int Age()
    {
        return _Age;
    }

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }
};

int main()
{

    clsStudent S1;

    if ((17 & 1) == 1)
        cout << "it's equal 17 \n";
    else
        cout << "it's dosn't equal 17\n";
    if ((17 & 5) == 5)
            cout << "it's equal 17 \n";
    else 
        cout << "it's dosn't equal 17\n";
    // cout << "1 | 5 = " << (1 | 5) << endl;
    // S1.setFistName("Yahya");
    // S1.setLastName("Aboumeil");
    // S1.setAge(19);
    // cout << S1.Age() << endl;
    // cout << S1.FullName() << endl;
}