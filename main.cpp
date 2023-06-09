// Use at(i) for code saftey
// Avoid goto as much
// red color for withdraw transaction in the table
// use bettr randomizer


#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <windows.h>

using namespace std;

int main() {

    const int maxAccounts = 50;
    const int maxTransactions = 500;

    string menuOptions[7] = {"[1] Create an account", "[2] Deposit money into your account", "[3] Withdraw", "[4] Transfer", "[5] View past transactions", "[6] Edit Account details", "[7] Currency rates and currency converter"};
    string names[maxAccounts], passwords[maxAccounts], tempPass = "";
    double balances[maxAccounts];
    bool navigateMenu = true;
    int userChoice, currentAccountIndex = 0, accountNumbers[maxAccounts], currentTransactionIndex = 0;
    time_t currentTime;


    int transactionAccountNumbers[maxTransactions] = {0}; double transactionMoneyAmount[maxTransactions]; string transactionType[maxTransactions];
    string transactionDates[maxTransactions];

    double rates[3] = {54.4, 64.7, 58.3,};
    string currencyNames[3] = {"USD to Birr", "Pound to Birr", "Euro to Birr",};


    menuIterator: while (navigateMenu) {

        system("cls");
           cout << ".______        ___      .__   __.  __  ___  __  .__   __.   _______         ___      .______   .______   \n"
                "|   _  \\      /   \\     |  \\ |  | |  |/  / |  | |  \\ |  |  /  _____|       /   \\     |   _  \\  |   _  \\  \n"
                "|  |_)  |    /  ^  \\    |   \\|  | |  '  /  |  | |   \\|  | |  |  __        /  ^  \\    |  |_)  | |  |_)  | \n"
                "|   _  <    /  /_\\  \\   |  . `  | |    <   |  | |  . `  | |  | |_ |      /  /_\\  \\   |   ___/  |   ___/  \n"
                "|  |_)  |  /  _____  \\  |  |\\   | |  .  \\  |  | |  |\\   | |  |__| |     /  _____  \\  |  |      |  |      \n"
                "|______/  /__/     \\__\\ |__| \\__| |__|\\__\\ |__| |__| \\__|  \\______|    /__/     \\__\\ | _|      | _|      \n";


        cout << endl << endl;

        cout << string(5, ' ') + "+" << string(48, '-') << "+\n";
        for (int i = 0; i < 7; i++) {
            cout << string(5, ' ') + "|   " << setw(45) << left << menuOptions[i] << "|\n";
            (i < 6) ? cout << string(5, ' ') + string(50, '-') << endl : cout << "" ;
        }
        cout << string(5, ' ') + "+" << string(48, '-') << "+\n\n\n";
        cout << "Choose the action you want, click from 1 upto 7 respectively for each action: ";

        cin >> userChoice;

        switch (userChoice) {
            case 1: {
                system("cls");
                cout << "Great. You wanted to create an account! Follow the following procedures.";

                cout << "\nEnter your name: ";
                getline(cin.ignore(), names[currentAccountIndex]);

                passRetry:
                cout << "Enter the password for your account: ";
                getline(cin, tempPass);

                if (tempPass.length() < 7) {
                    cout << "The password entered is too short, try again.\n";
                    goto passRetry;
                } else {
                    passwords[currentAccountIndex] = tempPass;
                    cout << "pass: "<< passwords[currentAccountIndex] << endl;
                }

                balances[currentAccountIndex] = 0;

                random_device rd;
                mt19937 engine(rd());
                uniform_int_distribution<int> distribution(1, 99999);
                int randomGenerated = distribution(engine), currentRand;
                stringstream  ss;

                int leadingZeros = 5 - to_string(randomGenerated).length();
                    ss << string(leadingZeros, '0') << randomGenerated;
                    currentRand = stoi(ss.str());

                bool uniqueFound = false;

                for (int i = 0; i < maxAccounts; i++) {
                    if (accountNumbers[i] != currentRand) {
                        accountNumbers[currentAccountIndex] = currentRand;
                        uniqueFound = true;
                    }

                    while (!uniqueFound) {
                        randomGenerated = distribution(engine);
                        leadingZeros = 5 - std::to_string(randomGenerated).length();
                        ss << string(leadingZeros, '0') << randomGenerated;
                        currentRand = stoi(ss.str());

                        if (accountNumbers[i] != currentRand) {
                            accountNumbers[currentAccountIndex] = currentRand;
                            uniqueFound = true;
                        }
                    }
                }

                cout << "Your account number is: " << accountNumbers[currentAccountIndex] << endl;
                cout << "Your account balance is: " << balances[currentAccountIndex] << endl;

                currentAccountIndex++;

                cout << "If you would like to go to main menu click [Y] else if you want to quit click any key except" << endl;

                char menuChoice;
                cin >> menuChoice;

                if (menuChoice == 'Y' || menuChoice == 'y') {
                    continue;
                }  else {
                    navigateMenu = false;

                }
            }

            break;

            case 2: {
                system("cls");
                cout << "Deposit into your account: \n";

                bool accountFound = false;
                int accountIndex;


                while (accountFound == 0) {
                    cout << "Enter your account number: ";

                    int accountNumber;

                    cin >> accountNumber;

                    for (int i = 0; i < currentAccountIndex; i++) {
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
                    accountPassword = "";
                    cout << "Please enter the password of your account: ";
                    getline(cin, accountPassword);
                    cout << "pass " << accountPassword << endl;

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

                        ostringstream ossDate;
                        ostringstream ossTime;

                        string dateTimeNow;
                        currentTime = time(0);
                        tm* localTime = localtime(&currentTime);
                        ossDate << put_time(localTime, "%d-%m-%Y ");
                        ossTime << put_time(localTime, "%I:%M %p");
                        dateTimeNow = ossDate.str() + ossTime.str();

                        transactionMoneyAmount[currentTransactionIndex] = moneyAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                        transactionType[currentTransactionIndex] = "Deposit";
                        transactionDates[currentTransactionIndex] = dateTimeNow;


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

                        ostringstream ossDate;
                        ostringstream ossTime;

                        string dateTimeNow;
                        currentTime = time(0);
                        tm* localTime = localtime(&currentTime);
                        ossDate << put_time(localTime, "%d-%m-%Y ");
                        ossTime << put_time(localTime, "%I:%M %p");
                        dateTimeNow = ossDate.str() + ossTime.str();

                        transactionMoneyAmount[currentTransactionIndex] = -moneyAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                        transactionType[currentTransactionIndex] = "Withdrawal";
                        transactionDates[currentTransactionIndex] = dateTimeNow;


                        currentTransactionIndex++;

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
                    double moneyAmount;
                    cout << "Welcome back, " << names[accountIndex] << "!\n";

                    bool receiverAccountFound = false;
                    int receiverAccountIndex;

                    while (receiverAccountFound == 0) {
                        cout << "Enter the receiver's account number: ";
                        int receiverAccountNumber;
                        cin >> receiverAccountNumber;

                        for (int i = 0; i < currentAccountIndex; i++) {
                            if (accountNumbers[i] == receiverAccountNumber) {
                                receiverAccountFound = true;
                                receiverAccountIndex = i;
                                break;
                            }
                        }

                        if (receiverAccountFound == 0) {
                            cout << "The account number you entered is not found, try again.\n";
                        }
                    }
                    transferAmountIterator: cout << "Enter the amount of money you want to transfer: ";
                    cin >> moneyAmount;

                    if ((balances[accountIndex] - moneyAmount) <= 25) {
                        cout << "Your balance is insufficient!" << "Your balance is " << balances[accountIndex] << "birr\n";
                        goto transferAmountIterator;
                    } else {
                        balances[accountIndex] -= moneyAmount;
                        balances[receiverAccountIndex] += moneyAmount;

                        ostringstream ossDate;
                        ostringstream ossTime;

                        string dateTimeNow;
                        currentTime = time(0);
                        tm* localTime = localtime(&currentTime);
                        ossDate << put_time(localTime, "%d-%m-%Y ");
                        ossTime << put_time(localTime, "%I:%M %p");
                        dateTimeNow = ossDate.str() + ossTime.str();

                        transactionMoneyAmount[currentTransactionIndex] = -moneyAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                        transactionType[currentTransactionIndex] = "Transfer";
                        transactionDates[currentTransactionIndex] = dateTimeNow;

                        currentTransactionIndex++;

                        transactionMoneyAmount[currentTransactionIndex] = moneyAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[receiverAccountIndex];
                        transactionType[currentTransactionIndex] = "Transfer";
                        transactionDates[currentTransactionIndex] = dateTimeNow;

                        currentTransactionIndex++;

                        cout << "You have successfully transferred " << moneyAmount << "birr from your account. To " << names[receiverAccountIndex] << "\nYour current balance: " << balances[accountIndex] << "birr\nClick 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
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

                bool accountFound = false;
                int accountIndex;

                while (!accountFound) {
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
                    const int columnWidth = 15;
                    int typeWidth = 0;
                    int amountWidth = 0;
                    int dateWidth = 0;

                    cout << "Welcome back, " << names[accountIndex] << "!\n";

                    // Calculate maximum column widths
                    for (int i = 0; i < currentTransactionIndex; i++) {
                        typeWidth = max(typeWidth, static_cast<int>(transactionType[i].length()));
                        amountWidth = max(amountWidth, static_cast<int>(to_string(transactionMoneyAmount[i]).length()));
                        dateWidth = max(dateWidth, static_cast<int>(transactionDates[i].length()));
                    }

                    // Add some padding to the maximum widths
                    typeWidth += 2;
                    amountWidth += 2;
                    dateWidth += 2;

                    // Print table header
                    cout << "+" << string(typeWidth + 7, '-') << "+" << string(amountWidth, '-') << "+" << string(dateWidth, '-') << "+\n";
                    cout << "|" << setw(typeWidth + 7) << right << "Transaction Type" << "|" << setw(amountWidth) << right << "Amount" << "|" << setw(dateWidth) << right << "Date" << "|\n";
                    cout << "+" << string(typeWidth + 7, '-') << "+" << string(amountWidth, '-') << "+" << string(dateWidth, '-') << "+\n";

                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                    for (int i = 0; i < currentTransactionIndex; i++) {
                        if (transactionAccountNumbers[i] == accountNumbers[accountIndex]) {
                            cout << "|" << setw(typeWidth + 7) << left << transactionType[i] << "|";
                                    if (transactionMoneyAmount[i] < 0) {
                                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                                    } else {
                                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                                    }
                                    cout  << setw(amountWidth) << right << transactionMoneyAmount[i];
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                                    cout << "|";

                                    cout  << setw(dateWidth) << left << transactionDates[i] << "|\n";
                        }
                    }

                    // Print table footer
                    cout << "+" << string(typeWidth + 7, '-') << "+" << string(amountWidth, '-') << "+" << string(dateWidth, '-') << "+\n";

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

            case 6: {

                system("cls");
                cout << "Modify account details:\n";

                bool accountFound = false;
                int accountIndex;

                while (!accountFound) {
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
                    const int columnWidth = 15;
                    int typeWidth = 0;
                    int amountWidth = 0;
                    int dateWidth = 0;

                   settingsIterator: cout << "Welcome back, " << names[accountIndex] << "!\n";
                    cout << "Account Number:" << accountNumbers[accountIndex] << endl;
                    cout << "1. Account Name:" << names[accountIndex] << endl;
                    cout << "2. Account Password: " << passwords[accountIndex] << endl << endl;

                    cout << "Click [1] to rename your account name or [2] to change your password. Click any other key to exit account settings\n";
                    cin >> choice;

                    if (choice == '1') {
                        system("cls");
                        string name;
                        cout << "Enter your new account name:";
                        getline(cin.ignore(), name);

                        names[accountIndex] = name;
                        cout << "Your account name has been renamed successfully!\n";
                        goto settingsIterator;
                    } else if (choice == '2') {
                        system("cls");
                        settingsPassRetry:
                        cout << "Enter the password for your account: ";
                        getline(cin, tempPass);

                        if (tempPass.length() < 7) {
                            cout << "The password entered is too short, try again.\n";
                            goto settingsPassRetry;
                        } else {
                            passwords[accountIndex] = tempPass;
                            cout << "Your password has been changed successfully!\n";
                            goto settingsIterator;
                        }
                    } else {
                        goto menuIterator;
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

            case 7: {
                system("cls");
                cout << "Current currency rates:\n";








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

