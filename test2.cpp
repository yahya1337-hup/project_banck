#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

struct sUser
{
    string Name;
    string Password;
    int    Permissions;
};

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;
}

sUser ReadNewUser()
{
    sUser User;
    cout << "Enter UserName? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.Name);

    while (UserExistsByAccountNumber(User.AccountNumber, UsersFileName))
    {
        cout << "\nUser with [" << User.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, User.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, User.PinCode);

    cout << "Enter Name? ";
    getline(cin, User.Name);

    cout << "Enter Phone? ";
    getline(cin, User.Phone);

    cout << "Enter AccountBalance? ";
    cin >> User.AccountBalance;

    return User;
}


sUser user_ConvertLineToRecord(string Line, string Separater = "#//#")
{
    sUser User;
    vector <string>  vInfo = SplitString(Line, "#//#");

    User.Name = vInfo[0];
    User.Password = vInfo[1];
    User.Permissions = stoi(vInfo[2]);

    return User;
}

vector<sUser> LoadUsersDataFromFile(string FileName)
{
    vector<sUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = user_ConvertLineToRecord(Line);
            vUser.push_back(User);
        }
        MyFile.close();
    }
    return vUser;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecordToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        // system("clear");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}


int main()
{
    ShowListUsers();
}