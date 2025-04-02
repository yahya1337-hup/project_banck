
#ifndef BANCK_H
#define BANCK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

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

enum enMainMenueOptionsUsers
{
    eListUser = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eManiMenue = 6,
};

enum enBool
{
    TRUE = 'y',
    FALSE = 'N'
};

// String Manipulation
vector<string> SplitString(string S1, string Delim);

// Client Record Conversion
sClient ConvertLinetoRecord(string Line, string Seperator);
string ConvertRecordToLine(sClient Client, string Seperator);

// Client Existence Check
bool ClientExistsByAccountNumber(string AccountNumber, string FileName);

// Client Data Handling
sClient ReadNewClient();
vector<sClient> LoadCleintsDataFromFile(string FileName);
void PrintClientRecordLine(sClient Client);
void ShowAllClientsScreen();
void PrintClientCard(sClient Client);
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client);
sClient ChangeClientRecord(string AccountNumber);
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients);
vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients);
void AddDataLineToFile(string FileName, string stDataLine);
void AddNewClient();
void AddNewClients();
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients);
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients);
string ReadClientAccountNumber();
void ShowDeleteClientScreen();
void ShowUpdateClientScreen();
void ShowAddNewClientsScreen();
void ShowFindClientScreen();

// User Record Conversion
sUser user_ConvertLineToRecord(string Line, string Separater);
vector<sUser> LoadUsersDataFromFile(string FileName);
string user_ConvertRecordToLine(sUser User, string Seperator );
void ShowListUsers();
void user_AddDataLineToFile(string FileName, string stDataLine);
bool UserExistsByAccountNumber(string Name, string FileName);
void ReadMoreInfo(sUser &User);
void SetPerrmission(sUser &User);
sUser ReadNewUser();
void AddNewUser();
void AddNewUsers();
void ShowAddNewUserScreen();
void PrintClientCard(sUser User);
bool FindUserByUserName(string Name, vector<sUser> vUser, sUser &User);
bool MarkUserForDeleteByUserName(string UserName, vector<sUser> &vUser);
vector<sUser> SaveUserssDataToFile(string FileName, vector<sUser> vUser);
bool DeleteUserByUserName(string UserName, vector<sUser> &vUser);
string ReadUserNametoDelete();
void ShowDeleteUserScreen();
sUser ChangeUserRecord(string UserName);
bool UpdateUserByUserName(string UserName, vector<sUser> &vUser);
void ShowUpdateUser();
void ShowFindUserScreen();

// Main Menu and User Authentication
string ReadUserName();
string ReadPasswd();
bool CheckPermmision(int Num, ePermmision Permmision);
bool CheckPasswordUserName(string UserName, string Passwrd);
sUser ExtractUser(string UserName);
void ShowPermmisionDenid();
void PerfromMainMenueOptionUser(enMainMenueOptionsUsers MainMenue);
void ShowManageMenueUser();
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption);
void ShowMainMenue();
void GoBackToMainMenue();
short ReadMainMenueOption();
void GoBackToManageUsersScreen();
void ShowLoginSccren();

#endif