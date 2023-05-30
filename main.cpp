#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {

    const int maxAccounts = 50;

    string names[maxAccounts];
    double balances[maxAccounts];
    string passwords[maxAccounts];
    int accountNumbers[maxAccounts] = {50000};
    string secretCodes[maxAccounts];
    int userChoice, currentAccountIndex = 0;
    string tempPass = "";



   menuIterator: while (true) {
        system("cls");
        cout << "1. Create an account";
        cin >> userChoice;


        switch (userChoice) {
            case 1: {
                system("cls");
                cout << "Great you wanted to create an account! Follow the following procedures." << endl;

                cout << "Enter your name: " << endl;
                getline(cin.ignore(), names[currentAccountIndex]);

                passRetry:
                cout << "Enter the password for your account: " << endl;
                getline(cin.ignore(), tempPass);

                if (tempPass.length() < 7) {
                    cout << "The password entered is too short, try again.\n";
                    goto passRetry;
                }

                balances[currentAccountIndex] = 0;


                int currentRand = rand() % 90000 + 10000;
                bool uniqueFound = false;

                for (int i = 0; i < maxAccounts; i++) {
                    if (accountNumbers[i] != currentRand) {
                        accountNumbers[currentAccountIndex] = currentRand;
                        uniqueFound = true;
                    }

                    while (!uniqueFound) {
                        currentRand = rand() % 90000 + 10000;
                        cout << currentRand;

                        if (accountNumbers[i] != currentRand) {
                            accountNumbers[currentAccountIndex] = currentRand;
                            uniqueFound = true;
                        }
                    }
                }
                

                cout << "Your account number is: " << accountNumbers[currentAccountIndex] << endl;
                cout << "Your account balance is: " << balances[currentAccountIndex] << endl;
               
                cout << "You're " << currentAccountIndex + 1 << " user\n";

                currentAccountIndex++;
                

                cout << "If you would like to go to main menu click \"Y\" else if you want to quit click \"N\"" << endl;

                char menuChoice;
                cin >> menuChoice;

                if (menuChoice == 'Y' || menuChoice == 'y') {
                    goto menuIterator;
                } else {
                    break;
                }

            }

            break;

            case 2: {

            }
                

            default:
                break;
        }

        cout << names[0];
        break;
    }

    return 0;
}