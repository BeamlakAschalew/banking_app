// Use at(i) for code saftey
// Avoid goto as much
// red color for withdraw transaction in the table


#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    const int maxAccounts = 50;
    const int maxTransactions = 500;

    string names[maxAccounts], passwords[maxAccounts], tempPass = "";
    double balances[maxAccounts];
    bool navigateMenu = true;
    int userChoice, currentAccountIndex = 0, accountNumbers[maxAccounts], currentTransactionIndex = 0;

    int transactionAccountNumbers[maxTransactions] = {0}; double transactionMoneyAmount[maxTransactions]; string transactionType[maxTransactions];




    menuIterator: while (navigateMenu) {
        system("cls");
           cout << ".______        ___      .__   __.  __  ___  __  .__   __.   _______         ___      .______   .______   \n"
                "|   _  \\      /   \\     |  \\ |  | |  |/  / |  | |  \\ |  |  /  _____|       /   \\     |   _  \\  |   _  \\  \n"
                "|  |_)  |    /  ^  \\    |   \\|  | |  '  /  |  | |   \\|  | |  |  __        /  ^  \\    |  |_)  | |  |_)  | \n"
                "|   _  <    /  /_\\  \\   |  . `  | |    <   |  | |  . `  | |  | |_ |      /  /_\\  \\   |   ___/  |   ___/  \n"
                "|  |_)  |  /  _____  \\  |  |\\   | |  .  \\  |  | |  |\\   | |  |__| |     /  _____  \\  |  |      |  |      \n"
                "|______/  /__/     \\__\\ |__| \\__| |__|\\__\\ |__| |__| \\__|  \\______|    /__/     \\__\\ | _|      | _|      \n";
        cout << "1. Create an account: \n";
        cout << "2. Deposit money into your account: \n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. View past transactions\n";
        cin >> userChoice;


        switch (userChoice) {
            case 1: {
                system("cls");
                cout << "Great. You wanted to create an account! Follow the following procedures.";

                cout << "\nEnter your name: ";
                getline(cin.ignore(), names[currentAccountIndex]);

                passRetry:
                cout << "\nEnter the password for your account: " << endl;
                getline(cin, tempPass);

                if (tempPass.length() < 7) {
                    cout << "The password entered is too short, try again.\n";
                    goto passRetry;
                } else {
                    passwords[currentAccountIndex] = tempPass;
                    cout << "pass: "<< passwords[currentAccountIndex] << endl;
                }

                balances[currentAccountIndex] = 0;


                int currentRand = rand() % 100000;
                bool uniqueFound = false;

                for (int i = 0; i < maxAccounts; i++) {
                    if (accountNumbers[i] != currentRand) {
                        accountNumbers[currentAccountIndex] = currentRand;
                        uniqueFound = true;
                    }

                    while (!uniqueFound) {
                        currentRand = rand() % 100000;
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
                    continue;
                } else if (menuChoice == 'N' || menuChoice == 'n') {
                    navigateMenu = false;
                } else {
                    cout << "Wrong choice option entered!" << endl;
                    continue;
                }


            }

            break;

            case 2: {
                system("cls");
                cout << "Deposit into your account: \n";

                bool accountFound = false;
                int accountIndex;

                while (accountFound == 0) {
                    cout << "Enter your account number: \n";

                    int accountNumber;

                    cin >> accountNumber;

                    for (int i = 0; i < maxAccounts; i++) {
                        if (accountNumbers[i] == accountNumber) {
                            accountFound = true;
                            accountIndex = i;
                            break;
                        }
                    }

                    if (accountFound == 0) {
                        cout << "The account number you entered is not found, try again.\n";
                    }
                }

                string accountPassword; bool passwordValidated = false; int passwordTries = 4;



                while (!passwordValidated && passwordTries > 0) {
                    cout << "Please enter the password of your account: \n";
                    getline(cin.ignore(), accountPassword);

                    if (accountPassword == passwords[accountIndex]) {
                        passwordValidated = true;

                    } else {
                        cout << "The password you entered is incorrect!\n";
                        --passwordTries;
                        if (passwordTries >= 1)
                            cout << "You have " << passwordTries << " trials left, try again.\n";
                        else
                            break;
                    }
                }

                char choice;

                if (passwordValidated) {
                    cout << "Welcome back, " << names[accountIndex] << "!\n";
                    amountIterator: double moneyAmount;
                    cout << "Enter the amount of money you want to deposit: ";
                    cin >> moneyAmount;

                    if (moneyAmount >= 0.1) {
                        balances[accountIndex] += moneyAmount;


                        transactionMoneyAmount[currentTransactionIndex] = moneyAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                        transactionType[currentTransactionIndex] = "Deposit";

                        cout << "mny " << transactionMoneyAmount[currentTransactionIndex] << endl;
                        cout << "ac num" << transactionAccountNumbers[currentAccountIndex] << endl;
                        cout << "typ " << transactionType[currentAccountIndex] << endl;

                        currentTransactionIndex++;
                        cout << "You have successfully deposited " << moneyAmount << "birr into your account.\nYour current balance: " << balances[accountIndex] << "birr\nClick 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        } else {
                            break;
                        }

                    } else {
                        cout << "The amount you entered is too low, try again.\n";
                        goto amountIterator;
                    }
                } else {

                    cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto menuIterator;
                    } else {
                        break;
                    }
                }


            }

            break;

            case 3: {
                system("cls");
                cout << "Withdraw from your account: \n";

                bool accountFound = false;
                int accountIndex;

                while (accountFound == 0) {
                    cout << "Enter your account number: \n";

                    int accountNumber;

                    cin >> accountNumber;

                    for (int i = 0; i < maxAccounts; i++) {
                        if (accountNumbers[i] == accountNumber) {
                            accountFound = true;
                            accountIndex = i;
                            break;
                        }
                    }

                    if (accountFound == 0) {
                        cout << "The account number you entered is not found, try again.\n";
                    }
                }

                string accountPassword; bool passwordValidated = false; int passwordTries = 4;



                while (!passwordValidated && passwordTries > 0) {
                    cout << "Please enter the password of your account: \n";
                    getline(cin.ignore(), accountPassword);

                    if (accountPassword == passwords[accountIndex]) {
                        passwordValidated = true;

                    } else {
                        cout << "The password you entered is incorrect!\n";
                        --passwordTries;
                        if (passwordTries >= 1)
                            cout << "You have " << passwordTries << " trials left, try again.\n";
                        else
                            break;
                    }
                }

                char choice;

                if (passwordValidated) {
                    withdrawAmountIterator: double moneyAmount;
                    cout << "Enter the amount of money you want to withdraw: ";
                    cin >> moneyAmount;

                    if ((balances[accountIndex] - moneyAmount) <= 25) {
                        cout << "Your balance is insufficient!" << "Your balance is " << balances[accountIndex] << "birr\n";
                        goto withdrawAmountIterator;
                    } else {
                        balances[accountIndex] -= moneyAmount;
                        cout << "You have successfully withdrawn " << moneyAmount << "birr from your account.\nYour current balance: " << balances[accountIndex] << "birr\nClick 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        } else {
                            break;
                        }
                    }


                } else {

                    cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto menuIterator;
                    } else {
                        break;
                    }
                }


            }

            break;

            case 4: {
                system("cls");
                cout << "Transfer: \n";

                bool accountFound = false;
                int accountIndex;

                while (accountFound == 0) {
                    cout << "Enter your account number: \n";

                    int accountNumber;

                    cin >> accountNumber;

                    for (int i = 0; i < maxAccounts; i++) {
                        if (accountNumbers[i] == accountNumber) {
                            accountFound = true;
                            accountIndex = i;
                            break;
                        }
                    }

                    if (accountFound == 0) {
                        cout << "The account number you entered is not found, try again.\n";
                    }
                }

                bool recieverAccountFound = false;
                int recieverAccountIndex;

                while (recieverAccountFound == 0) {
                    cout << "Enter the receiver's account number: \n";

                    int receiverAccountNumber;

                    cin >> receiverAccountNumber;

                    for (int i = 0; i < maxAccounts; i++) {
                        if (accountNumbers[i] == receiverAccountNumber) {
                            recieverAccountFound = true;
                            recieverAccountIndex = i;
                            break;
                        }
                    }

                    if (recieverAccountFound == 0) {
                        cout << "The account number you entered is not found, try again.\n";
                    }
                }



                string accountPassword; bool passwordValidated = false; int passwordTries = 4;


                cout << "Welcome back, " << names[accountIndex] << "!\n";
                while (!passwordValidated && passwordTries > 0) {
                    cout << "Please enter the password of your account: \n";
                    getline(cin.ignore(), accountPassword);

                    if (accountPassword == passwords[accountIndex]) {
                        passwordValidated = true;

                    } else {
                        cout << "The password you entered is incorrect!\n";
                        --passwordTries;
                        if (passwordTries >= 1)
                            cout << "You have " << passwordTries << " trials left, try again.\n";
                        else
                            break;
                    }
                }

                char choice;

                if (passwordValidated) {
                    transferAmountIterator: double moneyAmount;
                    cout << "Enter the amount of money you want to transfer: ";
                    cin >> moneyAmount;

                    if ((balances[accountIndex] - moneyAmount) <= 25) {
                        cout << "Your balance is insufficient!" << "Your balance is " << balances[accountIndex] << "birr\n";
                        goto transferAmountIterator;
                    } else {
                        balances[accountIndex] -= moneyAmount;
                        balances[recieverAccountIndex] += moneyAmount;
                        cout << "You have successfully transferred " << moneyAmount << "birr from your account. To " << names[recieverAccountIndex] << "\nYour current balance: " << balances[accountIndex] << "birr\nClick 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        } else {
                            break;
                        }
                    }


                } else {

                    cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto menuIterator;
                    } else {
                        break;
                    }
                }


            }
                break;

            case 5: {
                system("cls");
                cout << "Past transactions:\n";
                cout << "Enter your account number";

                bool accountFound = false;
                int accountIndex;

                while (accountFound == 0) {
                    cout << "Enter your account number: \n";

                    int accountNumber;

                    cin >> accountNumber;

                    for (int i = 0; i < maxAccounts; i++) {
                        if (accountNumbers[i] == accountNumber) {
                            accountFound = true;
                            accountIndex = i;
                            break;
                        }
                    }

                    if (accountFound == 0) {
                        cout << "The account number you entered is not found, try again.\n";
                    }
                }

                string accountPassword; bool passwordValidated = false; int passwordTries = 4;


                cout << "Welcome back, " << names[accountIndex] << "!\n";
                while (!passwordValidated && passwordTries > 0) {
                    cout << "Please enter the password of your account: \n";
                    getline(cin.ignore(), accountPassword);

                    if (accountPassword == passwords[accountIndex]) {
                        passwordValidated = true;

                    } else {
                        cout << "The password you entered is incorrect!\n";
                        --passwordTries;
                        if (passwordTries >= 1)
                            cout << "You have " << passwordTries << " trials left, try again.\n";
                        else
                            break;
                    }
                }

                char choice;

                if (passwordValidated) {
                    const int columnWidth = 15;
                    cout << "tr index " << currentAccountIndex << endl;
                    cout << "ac index " << accountIndex << endl;

                    cout << "+-----------------+-----------------+-----------------+\n";
                    cout << "| Transaction Type|     Amount      |      Date       |\n";
                    cout << "+-----------------+-----------------+-----------------+\n";

                   for (int i = 0; i < currentTransactionIndex; i++) {
                       if (transactionAccountNumbers[i] == accountNumbers[accountIndex]) {
                           cout << "| " << std::left << std::setw(columnWidth) << transactionType[i];
                           cout << "| " << std::right << std::setw(columnWidth) << transactionMoneyAmount[i];
                           cout << "| " << std::left << std::setw(columnWidth) << "monday" << "|\n";
                       }
                   }
                   cout << "+-----------------+-----------------+-----------------+\n";
                   cout << "Click 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                   cin >> choice;

                   if (choice == 'Y' || choice == 'y') {
                       goto menuIterator;
                   } else {
                       exit;
                   }

                } else {

                    cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto menuIterator;
                    } else {
                        break;
                    }
                }



            }
            break;




                

            default:
                break;
        }

        cout << names[0];
        break;
    }

    return 0;
}

