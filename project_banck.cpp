#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";

void ShowMainMenue(sUser User);
void PerfromMainMenueOptionUser(enMainMenueOptionsUsers MainMenue, sUser User);

enum ePermmision
{
    ShowClientList = 1,
    addNewClient = 2,
    DeletClient = 4,
    UpateClient = 8,
    FindClient = 16,
    Transactions = 32,
    ManageUsers = 64
};

struct sPermisions
{
    char FullAccess;
    char ShowClientList;
    char AddNewClient;
    char DeletClient;
    char UpateClient;
    char FindClient;
    char Transactions;
    char ManageUsers;
};

struct sUser
{
    string Name;
    string Password;
    sPermisions PermissionsInfo;
    bool MarkForDelet;
    int Permission;
};

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
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

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to double
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();
    }
    return false;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    for (sClient &C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
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

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        // system("clear");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }

    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }

    cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

//----------------------------------------------------------------------------------

sUser user_ConvertLineToRecord(string Line, string Separater = "#//#")
{
    sUser User;
    vector<string> vInfo = SplitString(Line, "#//#");

    User.Name = vInfo[0];
    User.Password = vInfo[1];
    User.Permission = stoi(vInfo[2]);

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

string user_ConvertRecordToLine(sUser User, string Seperator = "#//#")
{

    string strUser = "";
    strUser += User.Name + Seperator;
    strUser += User.Password + Seperator;
    strUser += to_string(User.Permission);
    return strUser;
}

void ShowListUsers()
{
    cout << "\t\t Users List (" << ") User(s)\n";
    cout << "___________________________________________________________________________\n";
    cout << left << setw(18) << "| User Name";
    cout << left << setw(12) << "| Password";
    cout << left << setw(12) << "| Permissions";
    cout << "\n___________________________________________________________________________\n";

    vector<sUser> vUser = LoadUsersDataFromFile("Users.txt");
    for (int i = 0; i < vUser.size(); i++)
    {
        cout << "| " << left << setw(16) << vUser[i].Name;
        cout << "| " << left << setw(10) << vUser[i].Password;
        cout << "| " << left << setw(10) << vUser[i].Permission << endl;
    }
    cout << "\n___________________________________________________________________________\n";
}

void user_AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

bool UserExistsByAccountNumber(string Name, string FileName)
{

    vector<sUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser User;

        while (getline(MyFile, Line))
        {
            User = user_ConvertLineToRecord(Line);
            if (User.Name == Name)
            {
                MyFile.close();
                return true;
            }
            vUsers.push_back(User);
        }

        MyFile.close();
    }
    return false;
}

void ReadMoreInfo(sUser &User)
{
    cout << "\n\nShow client list? y/n?";
    cin >> User.PermissionsInfo.ShowClientList;
    cout << "Add New Client? y/n?";
    cin >> User.PermissionsInfo.AddNewClient;
    cout << "Show Delet Client? y/n?";
    cin >> User.PermissionsInfo.DeletClient;
    cout << "Add Update Client? y/n?";
    cin >> User.PermissionsInfo.UpateClient;
    cout << "Find Client ? y/n?";
    cin >> User.PermissionsInfo.FindClient;
    cout << "Transaction ? y/n?";
    cin >> User.PermissionsInfo.Transactions;
    cout << "Manage Users? y/n?";
    cin >> User.PermissionsInfo.ManageUsers;
}

void SetPerrmission(sUser &User)
{
    int Counter = 0;

    if (User.PermissionsInfo.FullAccess == 'y')
        Counter = -1;
    if (User.PermissionsInfo.ShowClientList == 'y')
        Counter = ePermmision::ShowClientList;
    if (User.PermissionsInfo.AddNewClient == 'y')
        Counter += ePermmision::addNewClient;
    if (User.PermissionsInfo.DeletClient == 'y')
        Counter += ePermmision::DeletClient;
    if (User.PermissionsInfo.FindClient == 'y')
        Counter += ePermmision::FindClient;
    if (User.PermissionsInfo.Transactions == 'y')
        Counter += ePermmision::Transactions;
    if (User.PermissionsInfo.ManageUsers == 'y')
        Counter += ePermmision::ManageUsers;

    User.Permission = Counter;
}

sUser ReadNewUser()
{
    sUser User;
    cout << "Enter UserName? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.Name);

    while (UserExistsByAccountNumber(User.Name, "Users.txt"))
    {
        cout << "\nUser with [" << User.Name << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, User.Name);
    }

    cout << "Enter password? ";
    getline(cin, User.Password);

    cout << "\n\ndo you want to give full access? N/Y?";
    cin >> User.PermissionsInfo.FullAccess;
    if (User.PermissionsInfo.FullAccess != 'Y' &&
        User.PermissionsInfo.FullAccess != 'y')
        ReadMoreInfo(User);

    SetPerrmission(User);

    return User;
}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    user_AddDataLineToFile("Users.txt", user_ConvertRecordToLine(User));
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

void ShowAddNewUserScreen()
{
    cout << "-------------------------------\n";
    cout << "Add User Info Screen\n";
    cout << "--------------------------------\n";

    AddNewUsers();
}

void PrintClientCard(sUser User)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name     : " << User.Name;
    cout << "\nUser Password : " << User.Password;
    cout << "\nPermission    : " << User.Permission;
    cout << "\n-----------------------------------\n";
}

bool FindUserByUserName(string Name, vector<sUser> vUser, sUser &User)
{
    for (sUser user : vUser)
    {

        if (user.Name == Name)
        {
            User = user;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUserName(string UserName, vector<sUser> &vUser)
{

    for (sUser &user : vUser)
    {

        if (user.Name == UserName)
        {
            user.MarkForDelet = true;
            return true;
        }
    }

    return false;
}

vector<sUser> SaveUserssDataToFile(string FileName, vector<sUser> vUser)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sUser user : vUser)
        {

            if (user.MarkForDelet == false)
            {
                // we only write records that are not marked for delete.
                DataLine = user_ConvertRecordToLine(user);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vUser;
}

bool DeleteUserByUserName(string UserName, vector<sUser> &vUser)
{
    sUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {

        PrintClientCard(User);

        cout << "\n\nAre you sure you want delete this user? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUserName(UserName, vUser);
            SaveUserssDataToFile("Users.txt", vUser);

            // Refresh Clients
            vUser = LoadUsersDataFromFile("Users.txt");

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }

    cout << "\nUser with User Name (" << UserName << ") is Not Found!";
    return false;
}

string ReadUserNametoDelete()
{
    string UserName;

    cout << "\n\nWhich user name do you want to delete?\n";
    getline(cin, UserName);

    return UserName;
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete user Screen";
    cout << "\n-----------------------------------\n";

    vector<sUser> vUser = LoadUsersDataFromFile("Users.txt");
    string UserName = ReadUserNametoDelete();
    DeleteUserByUserName(UserName, vUser);
}

sUser ChangeUserRecord(string UserName)
{
    sUser sUser;

    sUser.Name = UserName;

    cout << "Enter Password? ";
    getline(cin, sUser.Password);

    cout << "Enter Permissions? ";
    ReadMoreInfo(sUser);
    SetPerrmission(sUser);
    return sUser;
}

bool UpdateUserByUserName(string UserName, vector<sUser> &vUser)
{

    sUser User;
    char Answer = 'n';

    if (FindUserByUserName(UserName, vUser, User))
    {

        PrintClientCard(User);
        cout << "\n\nAre you sure you want update this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser &user : vUser)
            {
                if (user.Name == UserName)
                {
                    user = ChangeUserRecord(UserName);
                    break;
                }
            }

            SaveUserssDataToFile("Users.txt", vUser);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }

    cout << "\nClient with Account Number (" << UserName << ") is Not Found!";
    return false;
}


void ShowUpdateUser()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    string UserName = ReadUserName();
    vector<sUser>vUsers = LoadUsersDataFromFile("Users.txt");
    
    UpdateUserByUserName(UserName, vUsers);
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector<sUser> vUser = LoadUsersDataFromFile("User.txt");
    sUser User;
    string UserName = ReadClientAccountNumber();
    if (FindUserByUserName(UserName, vUser, User))
        PrintClientCard(User);
    else
        cout << "\nClient with Account Number[" << UserName << "] is not found!";
}

//----------------------------------------


enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eManagUsers = 7,
    eLogOut = 8,
};

void GoBackToMainMenue(sUser User)
{
    cout << "\n\nPress any key to go back to Main Menue...";
    cin.ignore();
    cin.get();
    ShowMainMenue(User);
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void ShowMainMenue(sUser User)
{
    system("clear");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption(), User);
}

string ReadUserName()
{
    string User;

    cout << "\nPleas enter User Name\n";
    getline(cin, User);

    return User;
}

string ReadPasswd()
{
    string Passwd;

    cout << "Pleas enter password?\n";
    getline(cin, Passwd);

    return Passwd;
}

bool CheckPasswordUserName(string UserName, string Passwrd)
{
    fstream MyFile;
    MyFile.open("Users.txt", ios::in);

    if (MyFile.is_open())
    {
        sUser user;
        string line;
        while (getline(MyFile, line))
        {
            user = user_ConvertLineToRecord(line);
            if (user.Name == UserName)
            {
                MyFile.close();
                if (user.Password == Passwrd)
                    return true;
                return false;
            }
        }
    }
    MyFile.close();
    return false;
}

sUser ExtractUser(string UserName)
{
    fstream MyFile;
    sUser user;

    MyFile.open("Users.txt", ios::in);

    if (MyFile.is_open())
    {
        string line;
        while (getline(MyFile, line))
        {
            user = user_ConvertLineToRecord(line);
            if (user.Name == UserName)
                break;
        }
    }
    return user;
}

void ShowLoginSccren()
{
    sUser User;

    cout << "=======================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "=======================================\n";

    string UserName = ReadUserName(), Passwd = ReadPasswd();

    while (!CheckPasswordUserName(UserName, Passwd))
    {
        cout << "User Name Or Password is Wrong, Try again\n";
        UserName = ReadUserName(), Passwd = ReadPasswd();
    }
    User = ExtractUser(UserName);

    ShowMainMenue(User);
}

void ShowPermmisionDenid()
{
    system("clear");
    cout << "-------------------------------------\n";
    cout << "Acces Denied,\n";
    cout << "you don't have permminsion to do this,\n";
    cout << "Pleas Contact Your Admin\n";
    cout << "-------------------------------------\n";
}

enum enMainMenueOptionsUsers
{
    eListUser = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eManiMenue = 6,
};

void PerfromMainMenueOptionUser(enMainMenueOptionsUsers MainMenue, sUser User)
{
    switch (MainMenue)
    {
        case enMainMenueOptionsUsers::eListUser:
        {
            ShowListUsers();
            break ;
        }
        case enMainMenueOptionsUsers::eAddNewUser:
        {
            ShowAddNewUserScreen();
            break ;
        }
        case enMainMenueOptionsUsers::eDeleteUser:
        {
            ShowDeleteUserScreen();
            break ;
        }
        case enMainMenueOptionsUsers::eUpdateUser:
        {
            ShowUpdateUser();
            break ;
        }
        case enMainMenueOptionsUsers::eFindUser:
        {
            ShowFindUserScreen();
            break ;
        }
        case enMainMenueOptionsUsers::eManiMenue:
        {
            ShowMainMenue(User);
            break ;
        }
    }
}

void ShowManageMenueUser(sUser User)
{
    system("clear");
    cout << "===========================================\n";
    cout << "\t\tMange User Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show User List.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromMainMenueOptionUser((enMainMenueOptionsUsers)ReadMainMenueOption(), User);
}

enum enBool
{
    TRUE = 'y',
    FALSE = 'N'
};

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption, sUser User)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("clear");
        if (User.PermissionsInfo.ShowClientList == TRUE)
            ShowAllClientsScreen();
        else
            ShowPermmisionDenid();
        GoBackToMainMenue(User);
        break;
    }
    case enMainMenueOptions::eAddNewClient:

        system("clear");
        if (User.PermissionsInfo.AddNewClient == TRUE)
            ShowAddNewClientsScreen();
        else
            ShowPermmisionDenid();
        GoBackToMainMenue(User);
        break;

    case enMainMenueOptions::eDeleteClient:

        system("clear");
        if (User.PermissionsInfo.DeletClient == TRUE)
            ShowDeleteClientScreen();
        else
            ShowPermmisionDenid();
        GoBackToMainMenue(User);
        break;

    case enMainMenueOptions::eUpdateClient:
        system("clear");
        if (User.PermissionsInfo.DeletClient == TRUE)
            ShowUpdateClientScreen();
        else
            ShowPermmisionDenid();
        GoBackToMainMenue(User);
        break;

    case enMainMenueOptions::eFindClient:

        system("clear");
        if (User.PermissionsInfo.DeletClient == TRUE)
            ShowFindClientScreen();
        else
            ShowPermmisionDenid();
        GoBackToMainMenue(User);
        break;

    case enMainMenueOptions::eManagUsers:
        system("clear");
        if (User.PermissionsInfo.ManageUsers == TRUE)
                ShowManageMenueUser(User);
        else
            ShowPermmisionDenid();
        GoBackToMainMenue(User);
        break;

    case enMainMenueOptions::eLogOut:
        system("clear");
        ShowLoginSccren();
        break;
    }
}



int main()

{
    ShowLoginSccren();
    return 0;
}