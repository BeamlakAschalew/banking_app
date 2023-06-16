#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {

    // Array Sizes
    const int maxAccounts = 500;
    const int maxTransactions = 1000;
    const int maxRecurringTransactions = 1000;
    const int menuArraySize = 9;
    const int numberOfCurrencies = 4;

    // Program constants
    const double interestRate = 7.0;

    // Menu items array
    string menuOptions[menuArraySize] = {"[1] Create an account", "[2] Deposit money into your account", "[3] Withdraw", "[4] Transfer", "[5] View transaction history", "[6] Edit Account details", "[7] Currency rates and currency converter", "[8] View system transaction log (Admin only)", "[9] Setup recurring payments"};

    // Account related arrays
    string names[maxAccounts], passwords[maxAccounts];
    double balances[maxAccounts];
    int accountNumbers[maxAccounts] = {0};

    // Transaction related arrays
    int transactionAccountNumbers[maxTransactions] = {0}; double transactionMoneyAmount[maxTransactions]; string transactionType[maxTransactions];

    // Recurring transaction related arrays
    int recurringPaymentFrom[maxRecurringTransactions], recurringPaymentTo[maxRecurringTransactions], recurringPaymentFrequency[maxRecurringTransactions], recurringPaymentTime[maxRecurringTransactions];
    double recurringMoneyAmount[maxRecurringTransactions];


    // Currency related arrays
    const double rates[numberOfCurrencies] = {54.4, 64.7, 58.3, 1.0};
    string currencyNames[numberOfCurrencies] = {"USD to Birr", "Pound to Birr", "Euro to Birr",};

    // Current position integers
    int currentAccountIndex = 0, currentTransactionIndex = 0, currentRecurringIndex = 0;

    // Other variables
    string tempPass;
    int userChoice;
    bool navigateMenu = true;
    string adminPassword = "Strngpass";


    menuIterator: while (navigateMenu) {

    // Get the day of the week as an integer (0 - Sunday, 1 - Monday, ...)
    int dayOfWeek = 5;
    int hourOfDay = 8;
    int dayOfMonth = 16;

    ////////////////////////////////////////////////////////////////////////////////

    // Array of day names
    const string dayNames[] = {
            "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    // Get the day name based on the day of the week
    string currentDayName = dayNames[dayOfWeek];

    // Loop through all the accounts and add an interest based on the balance
    if (currentDayName == "Friday") {
        for (int i = 0; i < currentAccountIndex; i++) {
            balances[i] += (balances[i] * (interestRate / 100));
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////


    // Iterate through all registered recurring payments and transfer money based on the time specified
    for (int i = 0; i < currentRecurringIndex; i++) {
        if (recurringPaymentFrequency[i] == 1) {
            if (recurringPaymentTime[i] == hourOfDay) {
                if (balances[recurringPaymentFrom[i]] >= 0.1) {
                    balances[recurringPaymentFrom[i]] -= recurringMoneyAmount[i];
                    balances[recurringPaymentTo[i]] += recurringMoneyAmount[i];

                    transactionMoneyAmount[currentTransactionIndex] = -recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentFrom[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";

                    currentTransactionIndex++;

                    transactionMoneyAmount[currentTransactionIndex] = recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentTo[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";

                    currentTransactionIndex++;
                }
            }
        } else if (recurringPaymentFrequency[i] == 2) {
            if (recurringPaymentTime[i] == dayOfWeek) {
                if (balances[recurringPaymentFrom[i]] >= 0.1) {
                    balances[recurringPaymentFrom[i]] -= recurringMoneyAmount[i];
                    balances[recurringPaymentTo[i]] += recurringMoneyAmount[i];

                    transactionMoneyAmount[currentTransactionIndex] = -recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentFrom[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";

                    currentTransactionIndex++;

                    transactionMoneyAmount[currentTransactionIndex] = recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentTo[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";

                    currentTransactionIndex++;
                }
            } else if (recurringPaymentFrequency[i] == 3) {
                if (recurringPaymentTime[i] == dayOfMonth) {
                    if (balances[recurringPaymentFrom[i]] >= 0.1) {
                        balances[recurringPaymentFrom[i]] -= recurringMoneyAmount[i];
                        balances[recurringPaymentTo[i]] += recurringMoneyAmount[i];

                        transactionMoneyAmount[currentTransactionIndex] = -recurringMoneyAmount[i];
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentFrom[i]];
                        transactionType[currentTransactionIndex] = "Recurring Transfer";

                        currentTransactionIndex++;

                        transactionMoneyAmount[currentTransactionIndex] = recurringMoneyAmount[i];
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentTo[i]];
                        transactionType[currentTransactionIndex] = "Recurring Transfer";

                        currentTransactionIndex++;
                    }
                }
            }
        }
    }


    system("cls");
    cout << ".______        ___      .__   __.  __  ___  __  .__   __.   _______         ___      .______   .______   \n"
            "|   _  \\      /   \\     |  \\ |  | |  |/  / |  | |  \\ |  |  /  _____|       /   \\     |   _  \\  |   _  \\  \n"
            "|  |_)  |    /  ^  \\    |   \\|  | |  '  /  |  | |   \\|  | |  |  __        /  ^  \\    |  |_)  | |  |_)  | \n"
            "|   _  <    /  /_\\  \\   |  . `  | |    <   |  | |  . `  | |  | |_ |      /  /_\\  \\   |   ___/  |   ___/  \n"
            "|  |_)  |  /  _____  \\  |  |\\   | |  .  \\  |  | |  |\\   | |  |__| |     /  _____  \\  |  |      |  |      \n"
            "|______/  /__/     \\__\\ |__| \\__| |__|\\__\\ |__| |__| \\__|  \\______|    /__/     \\__\\ | _|      | _|      \n";


    cout << endl << endl;

    // Menu table layout
    cout << string(5, ' ') + "+" << string(48, '-') << "+\n";
    for (int i = 0; i < 9; i++) {
        cout << string(5, ' ') + "|   " << setw(45) << left << menuOptions[i] << "|\n";
        (i < 8) ? cout << string(5, ' ') + string(50, '-') << endl : cout << "" ;
    }
    cout << string(5, ' ') + "+" << string(48, '-') << "+\n\n\n";
    cout << "Choose the action you want, click from 1 upto 7 respectively for each action: ";

    cin >> userChoice;

    switch (userChoice) {
        case 1: {
            system("cls");
            cout << "Great. You wanted to create an account! Follow the following procedures." << endl;

            cout << "Enter your name: ";
            getline(cin.ignore(), names[currentAccountIndex]);

            passRetry:
            cout << "Enter the password for your account: ";
            getline(cin, tempPass);

            if (tempPass.length() < 7) {
                cout << "The password entered is too short, try again.\n";
                goto passRetry;
            } else {
                passwords[currentAccountIndex] = tempPass;
            }

            balances[currentAccountIndex] = 0;

            srand(time(0));

            int randomGenerated = rand();
            bool uniqueFound = false;

            // Iterate through all currently registered accounts and check if the newly generated account number doesn't exist, if so add it for the new user
            for (int i = 0; i < currentAccountIndex + 1; i++) {
                if (accountNumbers[i] != randomGenerated) {
                    accountNumbers[currentAccountIndex] = randomGenerated;
                    uniqueFound = true;
                }

                while (!uniqueFound) {
                    srand(time(0));
                    randomGenerated = rand();
                    if (accountNumbers[i] != randomGenerated) {
                        accountNumbers[currentAccountIndex] = randomGenerated;
                        uniqueFound = true;
                    }
                }
            }

            system("cls");
            cout << "You have successfully created an account!\n";
            cout << "Your account number is: " << accountNumbers[currentAccountIndex] << endl;
            cout << "Your account balance is: " << balances[currentAccountIndex] << endl;

            currentAccountIndex++;

            cout << "If you would like to go to main menu click [Y] else if you want to quit click any key: ";

            char menuChoice;
            cin >> menuChoice;

            if (menuChoice == 'Y' || menuChoice == 'y') {
                goto menuIterator;
            }  else {
                navigateMenu = false;
            }
        }

            break;

        case 2: {
            system("cls");
            cout << "Deposit into your account\n";

            bool accountFound = false;
            int accountIndex;
            char choice;

            while (!accountFound) {
                cout << "Enter your account number: ";
                int accountNumber;
                cin >> accountNumber;

                // Iterate through all accounts and assign the 'i' where the account number is found to accountIndex
                for (int i = 0; i < currentAccountIndex; i++) {
                    if (accountNumbers[i] == accountNumber) {
                        accountFound = true;
                        accountIndex = i;
                        break;
                    }
                }

                if (accountFound == 0) {
                    cout << "The account number you entered is not found.\n";
                    cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key:";
                    cin >> choice;

                    if (!(choice == 'Y' || choice == 'y')) {
                        goto menuIterator;
                    }
                }
            }

            system("cls");
            cout << "Deposit money for, " << names[accountIndex] << ".\n";
            amountIterator: double moneyAmount, convertedAmount; int currency;

            cout << "[1] US Dollar\n";
            cout << "[2] Pound\n";
            cout << "[3] Euro\n";
            cout << "[4] Birr\n\n";

            // Get the currency the user has and convert it to a birr
            cout << "Enter the currency you have: ";
            cin >> currency;

            cout << "Enter the amount of money you want to deposit: ";
            cin >> moneyAmount;

            if (moneyAmount >= 0.1) {
                convertedAmount = moneyAmount * rates[currency - 1];
                balances[accountIndex] += convertedAmount;

                // Assign values to arrays respectively
                transactionMoneyAmount[currentTransactionIndex] = convertedAmount;
                transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                transactionType[currentTransactionIndex] = "Deposit";

                currentTransactionIndex++;

                system("cls");
                cout << "You have successfully deposited " << convertedAmount << "birr into your account.\nYour current balance: " << balances[accountIndex] << "birr\nClick [Y] if you want to go to main menu else any key if you want to quit.\n";
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
        }

            break;

        case 3: {
            system("cls");
            cout << "Withdraw from your account\n";

            bool accountFound = false;
            int accountIndex;
            char choice;

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
                    cout << "The account number you entered is not found.\n";
                    cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key:";
                    cin >> choice;

                    if (!(choice == 'Y' || choice == 'y')) {
                        goto menuIterator;
                    }
                }
            }

            string accountPassword; bool passwordValidated = false; int passwordTries = 4;

            while (!passwordValidated && passwordTries > 0) {
                cout << "Please enter the password of your account: ";
                (passwordTries == 4) ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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

            if (passwordValidated) {
                withdrawAmountIterator: double moneyAmount;
                cout << "Enter the amount of money you want to withdraw: ";
                cin >> moneyAmount;

                if ((balances[accountIndex] - moneyAmount) <= 25) {
                    cout << "Your balance is insufficient!" << " Your balance is " << balances[accountIndex] << "birr\n";
                    cout << "If you want to enter amount again click [Y], if you want to go to main menu press any key: ";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto withdrawAmountIterator;
                    } else {
                        goto menuIterator;
                    }

                } else {
                    balances[accountIndex] -= moneyAmount;

                    transactionMoneyAmount[currentTransactionIndex] = -moneyAmount;
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                    transactionType[currentTransactionIndex] = "Withdrawal";

                    currentTransactionIndex++;

                    system("cls");
                    cout << "You have successfully withdrawn " << moneyAmount << "birr from your account.\nYour current balance: " << balances[accountIndex] << "birr\nClick [Y] if you want to go to main menu else click any if you want to quit.\n";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto menuIterator;
                    } else {
                        break;
                    }
                }


            } else {
                cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click [Y] if you want to go to main menu else click any key if you want to quit.\n";
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
            cout << "Transfer\n";

            bool accountFound = false;
            int accountIndex;
            char choice;

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
                    cout << "The account number you entered is not found.\n";
                    cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key:";
                    cin >> choice;

                    if (!(choice == 'Y' || choice == 'y')) {
                        goto menuIterator;
                    }
                }
            }

            string accountPassword; bool passwordValidated = false; int passwordTries = 4;

            while (!passwordValidated && passwordTries > 0) {
                cout << "Please enter the password of your account: ";
                (passwordTries == 4) ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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

            if (passwordValidated) {
                double moneyAmount;
                system("cls");
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
                        cout << "The account number you entered is not found.\n";
                        cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key:";
                        cin >> choice;

                        if (!(choice == 'Y' || choice == 'y')) {
                            goto menuIterator;
                        }
                    }
                }
                transferAmountIterator: cout << "Enter the amount of money you want to transfer: ";
                cin >> moneyAmount;

                if ((balances[accountIndex] - moneyAmount) <= 0.1) {
                    cout << "Your balance is insufficient!" << " Your balance is " << balances[accountIndex] << "birr\n";
                    cout << "If you want to enter amount again click [Y], if you want to go to main menu press any key: ";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto transferAmountIterator;
                    } else {
                        goto menuIterator;
                    }

                } else {
                    balances[accountIndex] -= moneyAmount;
                    balances[receiverAccountIndex] += moneyAmount;

                    transactionMoneyAmount[currentTransactionIndex] = -moneyAmount;
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                    transactionType[currentTransactionIndex] = "Transfer";

                    currentTransactionIndex++;

                    transactionMoneyAmount[currentTransactionIndex] = moneyAmount;
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[receiverAccountIndex];
                    transactionType[currentTransactionIndex] = "Transfer";

                    currentTransactionIndex++;

                    system("cls");
                    cout << "You have successfully transferred " << moneyAmount << "birr from your account. To " << names[receiverAccountIndex] << "\nYour current balance: " << balances[accountIndex] << "birr\nClick [Y] if you want to go to main menu else click any key if you want to quit.\n";
                    cin >> choice;

                    if (choice == 'Y' || choice == 'y') {
                        goto menuIterator;
                    } else {
                        break;
                    }
                }


            } else {

                cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click [Y] if you want to go to main menu, click any other key to quit.\n";
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
            char choice;

            while (!accountFound) {
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
                    cout << "The account number you entered is not found.\n";
                    cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key:";
                    cin >> choice;

                    if (!(choice == 'Y' || choice == 'y')) {
                        goto menuIterator;
                    }
                }
            }

            string accountPassword; bool passwordValidated = false; int passwordTries = 4;

            while (!passwordValidated && passwordTries > 0) {
                cout << "Please enter the password of your account: ";
                (passwordTries == 4) ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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

            if (passwordValidated) {
                system("cls");
                cout << "Welcome back, " << names[accountIndex] << "!\n";

                // Print table header
                cout << "+" << string(20, '-') << "+" << string(15, '-') << "+\n";
                cout << "|" << setw(20) << left << "Transaction Type" << "|" << setw(15) << left << "Amount" << "|\n";
                cout << "+" << string(20, '-') << "+" << string(15, '-') << "+\n";


                for (int i = 0; i < currentTransactionIndex; i++) {
                    // Display transaction records where account number equals the signed-in user account number
                    if (transactionAccountNumbers[i] == accountNumbers[accountIndex]) {
                        cout << "|" << setw(20) << left << transactionType[i] << "|";
                        cout  << setw(15) << left << transactionMoneyAmount[i];
                        cout << "|\n";
                    }
                }

                // Print table footer
                cout << "+" << string(20, '-') << "+" << string(15, '-') << "+\n";

                cout << "Account balance: " << balances[accountIndex] << " birr" << endl;
                cout << "Click [Y] if you want to go to main menu, click any other key to quit: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    goto menuIterator;
                } else {
                    break;
                }

            } else {

                cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click [Y] if you want to go to main menu, click any other key to quit: ";
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
            cout << "Modify account details\n";

            bool accountFound = false;
            int accountIndex;
            char choice;

            while (!accountFound) {
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
                    cout << "The account number you entered is not found.\n";
                    cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key: ";
                    cin >> choice;

                    if (!(choice == 'Y' || choice == 'y')) {
                        goto menuIterator;
                    }
                }
            }

            string accountPassword; bool passwordValidated = false; int passwordTries = 4;

            while (!passwordValidated && passwordTries > 0) {
                cout << "Please enter the password of your account: ";
                (passwordTries == 4) ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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

            if (passwordValidated) {
                const int columnWidth = 15;
                int typeWidth = 0;
                int amountWidth = 0;
                int dateWidth = 0;

                settingsIterator: cout << "Welcome back, " << names[accountIndex] << "!\n";
                cout << "Account Number: " << accountNumbers[accountIndex] << endl;
                cout << "1. Account Name: " << names[accountIndex] << endl;
                cout << "2. Account Password: " << passwords[accountIndex] << endl << endl;

                cout << "Click [1] to rename your account name or [2] to change your password. Click any other key to exit account settings: ";
                cin >> choice;

                if (choice == '1') {
                    system("cls");
                    string name;
                    cout << "Enter your new account name: ";
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

                cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click [Y] if you want to go to main menu, click any other key to quit.\n";
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
            cout << "Current currency rates\n";

            cout << "+" << string(20, '-') << "+" << string(20, '-') << "+\n";
            cout << "|   " << setw(17) << left << "Currency" << "|   " << setw(17) << left << "Birr" << "|\n";
            cout << "+" << string(20, '-') << "+" << string(20, '-') << "+\n";

            for (int i = 0; i < numberOfCurrencies - 1; i++) {
                cout << "|   " << setw(17) << left << currencyNames[i] << "|   " << setw(17) << left << rates[i] << "|\n";
            }

            cout << "+" << string(20, '-') << "+" << string(20, '-') << "+\n\n\n";

            char choice;
            cout << "If you want to convert currency click [C], if you want to go to main menu click [M] else if you want to quit press any key: ";
            cin >> choice;

            if (choice == 'C' || choice == 'c') {
                system("cls");
                int currencyFrom, currencyTo;
                double amount, toBirr, finalResult;

                cout << "[1] US Dollar\n";
                cout << "[2] Pound\n";
                cout << "[3] Euro\n";
                cout << "[4] Birr\n\n";

                cout << "Choose the currency you want to convert from: ";
                cin >> currencyFrom;


                cout << "[1] US Dollar\n";
                cout << "[2] Pound\n";
                cout << "[3] Euro\n";
                cout << "[4] Birr\n\n";

                cout << "Choose the currency you want to convert to: ";
                cin >> currencyTo;

                cout << "Enter the amount of money you want to convert: ";
                cin >> amount;

                toBirr = amount * rates[currencyFrom - 1];
                finalResult = toBirr / rates[currencyTo - 1];

                cout << "The calculated amount is: " << finalResult << endl;
                cout << "If you want to go to main menu click [Y] else if you want to quit click any key: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    goto menuIterator;
                } else {
                    break;
                }

            } else if (choice == 'M' || choice == 'm') {
                goto menuIterator;
            } else {
                break;
            }
        }
            break;

        case 8: {
            system("cls");
            cout << "System transaction log\n";
            bool passwordValidated = false; int passwordTries = 4;
            string adminPasswordInput;

            while (!passwordValidated && passwordTries > 0) {
                cout << "Please enter the password of your account: ";
                (passwordTries == 4) ? getline(cin.ignore(), adminPasswordInput) : getline(cin, adminPasswordInput);

                if (adminPassword == adminPasswordInput) {
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
                int typeWidth = 0, amountWidth = 0, dateWidth = 0, accountWidth = 0;

                cout << "Welcome back, Admin!\n";

                // Print table header
                cout << "+" << string(20, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+\n";
                cout << "|" << setw(20) << left << "Transaction Type" << "|" << setw(15) << left << "Account Number" << "|" <<  setw(15) << left << "Amount" << "|\n";
                cout << "+" << string(20, '-') << "+" << string( 15, '-') << "+" << string(15, '-') << "+\n";

                for (int i = 0; i < currentTransactionIndex; i++) {
                    cout << "|" << setw(20) << left << transactionType[i] << "|" << setw(15) << left << transactionAccountNumbers[i] << "|" << setw(15) << left << transactionMoneyAmount[i] << "|\n";
                }

                // Print table footer
                cout << "+" << string(20, '-') << "+" << string(15, '-') << "+" << string(15, '-') << "+\n";

                cout << "Click [Y] if you want to go to main menu, else click any key to quit: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    goto menuIterator;
                } else {
                    break;
                }


            } else {
                cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click [Y] if you want to go to main menu, else click any key if you want to quit: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    goto menuIterator;
                } else {
                    break;
                }
            }
        }

            break;

        case 9: {
            system("cls");
            cout << "Setup recurring transactions\n";

            bool accountFound = false;
            int accountIndex;
            char choice;

            while (accountFound == 0) {
                cout << "Enter the account number you want to transfer from: ";
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
                    cout << "The account number you entered is not found.\n";
                    cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key: ";
                    cin >> choice;

                    if (!(choice == 'Y' || choice == 'y')) {
                        goto menuIterator;
                    }
                }
            }

            string accountPassword; bool passwordValidated = false; int passwordTries = 4;

            while (!passwordValidated && passwordTries > 0) {
                accountPassword = "";
                cout << "Please enter the password of your account: ";
                (passwordTries == 4) ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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

            if (passwordValidated) {
                system("cls");
                cout << "Welcome back, " << names[accountIndex] << "!\n";
                double moneyAmount;

                bool receiverAccountFound = false;
                int receiverAccountIndex, transactionFrequency, transactionTime;

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
                        cout << "The account number you entered is not found.\n";
                        cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key: ";
                        cin >> choice;

                        if (!(choice == 'Y' || choice == 'y')) {
                            goto menuIterator;
                        }
                    }
                }

                cout << "Enter the amount of money you want to transfer every time: ";
                cin >> moneyAmount;

                recurIterator: cout << "[1] Every day\n[2] Every week\n[3] Every month\n";
                cout << "Enter the frequency between each payment: ";
                cin >> transactionFrequency;

                switch (transactionFrequency) {
                    case 1: {
                        system("cls");
                        cout << "Enter the hour for the payment (use 24-hr format like '21' etc): ";
                        cin >> transactionTime;

                        recurringPaymentFrom[currentRecurringIndex] = accountIndex;
                        recurringPaymentTo[currentRecurringIndex] = receiverAccountIndex;
                        recurringPaymentFrequency[currentRecurringIndex] = transactionFrequency;
                        recurringMoneyAmount[currentRecurringIndex] = moneyAmount;
                        recurringPaymentTime[currentRecurringIndex] = transactionTime;

                        currentRecurringIndex++;

                        cout << "A payment of" << moneyAmount << "birr " << "has been successfully to recur every day at " << transactionTime << " from the account number " << accountNumbers[accountIndex] << " to " << names[receiverAccountIndex] << "\nChoose [Y] if you want to go to main menu or any other key if you want to quit: ";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        }
                    }
                        break;

                    case 2: {
                        system("cls");
                        cout << "[1] Sunday\n[2] Monday\n[3] Tuesday\n[4] Wednesday\n[5] Thursday\n[6] Friday\n[7] Saturday\n";
                        cout << "Enter the week day for the payment to recur (from 1-7 as above stated): ";
                        cin >> transactionTime;

                        recurringPaymentFrom[currentRecurringIndex] = accountIndex;
                        recurringPaymentTo[currentRecurringIndex] = receiverAccountIndex;
                        recurringPaymentFrequency[currentRecurringIndex] = transactionFrequency;
                        recurringMoneyAmount[currentRecurringIndex] = moneyAmount;
                        recurringPaymentTime[currentRecurringIndex] = transactionTime - 1;

                        currentRecurringIndex++;

                        cout << "A payment of" << moneyAmount << " birr " << "has been successfully to recur every week-day at day" << transactionTime << " from the account number " << accountNumbers[accountIndex] << " to " << names[receiverAccountIndex] << "\nChoose [Y] if you want to go to main menu or any other key if you want to quit: ";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        }
                    }
                        break;

                    case 3: {
                        system("cls");
                        cout << "[1] January\n[2] February\n[3] March\n[4] April\n[5] May\n[6] June\n[7] July\n[8] August\n[9] September\n[10] October\n[11] November\n[12] December";
                        cout << "Enter the month for the payment to recur (from 1-12 as above stated): ";
                        cin >> transactionTime;

                        recurringPaymentFrom[currentRecurringIndex] = accountIndex;
                        recurringPaymentTo[currentRecurringIndex] = receiverAccountIndex;
                        recurringPaymentFrequency[currentRecurringIndex] = transactionFrequency;
                        recurringMoneyAmount[currentRecurringIndex] = moneyAmount;
                        recurringPaymentTime[currentRecurringIndex] = transactionTime - 1;

                        currentRecurringIndex++;

                        cout << "A payment of" << moneyAmount << "birr " << "has been successfully to recur every month at month" << transactionTime << " from the account number " << accountNumbers[accountIndex] << " to " << names[receiverAccountIndex] << "\nChoose [Y] if you want to go to main menu or any other key if you want to quit: ";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        }
                    }
                        break;

                    default: {
                        cout << "Wrong option entered. Click [Y] to retry or any other key to go to main menu: ";
                        cin >> choice;

                        if (choice == 'Y' || choice == 'y') {
                            goto menuIterator;
                        } else {
                            goto recurIterator;
                        }
                    }
                }

            } else {
                cout << "\nYou have entered incorrect password too many times so we can't grant deposition action now. Click [Y] if you want to go to main menu else click any key if you want to quit: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    goto menuIterator;
                } else {
                    break;
                }
            }
        }

            break;


        default: {
            char choice;
            system("cls");
            cout << "You have entered invalid option, If you want to try again click [Y], if you want to exit click any key: ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                goto menuIterator;
            } else {
                break;
            }
        }
    }

    break;
}

    return 0;
}

