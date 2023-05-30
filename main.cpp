#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{

    const int maxAccounts = 50;

    string names[maxAccounts];
    double balances[maxAccounts];
    string passwords[maxAccounts];
    int accountNumbers[maxAccounts];
    string secretCodes[maxAccounts];

    int userChoice, currentAccountIndex = 0;

    string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string randomString = "";

    while (true)
    {
        cout << "1. Create an account";
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            system("cls");
            cout << "Great you wanted to create an account! Follow the following procedures." << endl;

            cout << "Enter your name: " << endl;
            getline(cin.ignore(), names[currentAccountIndex]);

            // TODO: check for appropriate password length
            cout << "Enter the password for your account: " << endl;
            getline(cin.ignore(), passwords[currentAccountIndex]);

            accountNumbers[currentAccountIndex] = rand() % 90000 + 10000;
            balances[currentAccountIndex] = 0;
            // hello

            int sum;

            // for (int i = 0; i < 5; ++i) {
            //     int randomIndex = rand() % characters.length();
            //     randomString += characters[randomIndex];
            // }

            secretCodes[currentAccountIndex] = "";

            // int currentRand = rand() % 90000 + 10000;
            // bool uniqueFound = false;

            // while (!uniqueFound) {
            //     for (int i = 0; i < maxAccounts; i++) {
            //         if (accountNumbers[i] != currentRand) {
            //             accountNumbers[currentAccountIndex] = currentRand;
            //             uniqueFound = true;
            //         }

            //     // while (!uniqueFound) {
            //     //     int currentRand = rand() % 90000 + 10000;

            //     //     if (accountNumbers[i] != currentRand) {
            //     //         accountNumbers[currentAccountIndex] = currentRand;
            //     //         uniqueFound = true;
            //     //     }
            //     // }
            //     }
            // }

            break;

        default:
            break;
        }

        cout << names[0];
        break;
    }

    return 0;
}