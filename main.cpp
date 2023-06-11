#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <windows.h>

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
    string menuOptions[menuArraySize] = {"[1] Create an account", "[2] Deposit money into your account", "[3] Withdraw", "[4] Transfer", "[5] View past transactions", "[6] Edit Account details", "[7] Currency rates and currency converter", "[8] View system transaction log (Admin only)", "[9] Setup recurring payments"};

    // Account related arrays
    string names[maxAccounts], passwords[maxAccounts];
    double balances[maxAccounts];
    int accountNumbers[maxAccounts];

    // Transaction related arrays
    int transactionAccountNumbers[maxTransactions] = {0}; double transactionMoneyAmount[maxTransactions]; string transactionType[maxTransactions];
    string transactionDates[maxTransactions];

    // Recurring transaction related arrays
    int recurringPaymentFrom[maxRecurringTransactions], recurringPaymentTo[maxRecurringTransactions], recurringPaymentFrequency[maxRecurringTransactions], recurringPaymentTime[maxRecurringTransactions];
    double recurringMoneyAmount[maxRecurringTransactions];


    // Currency related arrays
    double rates[numberOfCurrencies] = {54.4, 64.7, 58.3, 1.0};
    string currencyNames[numberOfCurrencies] = {"USD to Birr", "Pound to Birr", "Euro to Birr",};

    // Current position integers
    int currentAccountIndex = 0, currentTransactionIndex = 0, currentRecurringIndex = 0;

    // Other variables
    string tempPass;
    int userChoice;
    bool navigateMenu = true;
    string adminPassword = "Strngpass";


    menuIterator: while (navigateMenu) {

        time_t currentTime = time(0);

        // Convert the current time to a struct tm
        tm* localTime = localtime(&currentTime);

        // Get the day of the week as an integer (0 - Sunday, 1 - Monday, ...)
        int dayOfWeek = localTime->tm_wday;
        int hourOfDay = localTime->tm_hour;
        int dayOfMonth = localTime->tm_mday;

        ////////////////////////////////////////////////////////////////////////////////

        // Array of day names
        const string dayNames[] = {
                "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
        };

        // Get the day name based on the day of the week
        string currentDayName = dayNames[dayOfWeek];


        // Loop through all the accounts and add an interest based on the balance
        if (currentDayName == "Saturday") {
            for (int i = 0; i < currentAccountIndex; i++) {
                balances[i] += (balances[i] * (interestRate / 100));
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////


        // Iterate through all registered recurring payments and transfer money based on the time specified
        for (int i = 0; i < currentRecurringIndex; i++) {
            if (recurringPaymentFrequency[i] == 1) {
                if (recurringPaymentTime[i] == hourOfDay) {
                    balances[recurringPaymentFrom[i]] -= recurringMoneyAmount[i];
                    balances[recurringPaymentTo[i]] += recurringMoneyAmount[i];

                    ostringstream ossDate;
                    ostringstream ossTime;

                    string dateTimeNow;
                    currentTime = time(0);
                    localTime = localtime(&currentTime);
                    ossDate << put_time(localTime, "%d-%m-%Y ");
                    ossTime << put_time(localTime, "%I:%M %p");
                    dateTimeNow = ossDate.str() + ossTime.str();

                    transactionMoneyAmount[currentTransactionIndex] = -recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentFrom[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";
                    transactionDates[currentTransactionIndex] = dateTimeNow;

                    currentTransactionIndex++;

                    transactionMoneyAmount[currentTransactionIndex] = recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentTo[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";
                    transactionDates[currentTransactionIndex] = dateTimeNow;

                    currentTransactionIndex++;
                }
            } else if (recurringPaymentFrequency[i] == 2) {
                if (recurringPaymentTime[i] == dayOfWeek) {
                    balances[recurringPaymentFrom[i]] -= recurringMoneyAmount[i];
                    balances[recurringPaymentTo[i]] += recurringMoneyAmount[i];

                    ostringstream ossDate;
                    ostringstream ossTime;

                    string dateTimeNow;
                    currentTime = time(0);
                    localTime = localtime(&currentTime);
                    ossDate << put_time(localTime, "%d-%m-%Y ");
                    ossTime << put_time(localTime, "%I:%M %p");
                    dateTimeNow = ossDate.str() + ossTime.str();

                    transactionMoneyAmount[currentTransactionIndex] = -recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentFrom[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";
                    transactionDates[currentTransactionIndex] = dateTimeNow;

                    currentTransactionIndex++;

                    transactionMoneyAmount[currentTransactionIndex] = recurringMoneyAmount[i];
                    transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentTo[i]];
                    transactionType[currentTransactionIndex] = "Recurring Transfer";
                    transactionDates[currentTransactionIndex] = dateTimeNow;

                    currentTransactionIndex++;
                } else if (recurringPaymentFrequency[i] == 3) {
                    if (recurringPaymentTime[i] == dayOfMonth) {
                        balances[recurringPaymentFrom[i]] -= recurringMoneyAmount[i];
                        balances[recurringPaymentTo[i]] += recurringMoneyAmount[i];

                        ostringstream ossDate;
                        ostringstream ossTime;

                        string dateTimeNow;
                        currentTime = time(0);
                        localTime = localtime(&currentTime);
                        ossDate << put_time(localTime, "%d-%m-%Y ");
                        ossTime << put_time(localTime, "%I:%M %p");
                        dateTimeNow = ossDate.str() + ossTime.str();

                        transactionMoneyAmount[currentTransactionIndex] = -recurringMoneyAmount[i];
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentFrom[i]];
                        transactionType[currentTransactionIndex] = "Recurring Transfer";
                        transactionDates[currentTransactionIndex] = dateTimeNow;

                        currentTransactionIndex++;

                        transactionMoneyAmount[currentTransactionIndex] = recurringMoneyAmount[i];
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[recurringPaymentTo[i]];
                        transactionType[currentTransactionIndex] = "Recurring Transfer";
                        transactionDates[currentTransactionIndex] = dateTimeNow;

                        currentTransactionIndex++;
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

                }

                balances[currentAccountIndex] = 0;

                // Initialize randomizer engine
                random_device rd;
                mt19937 engine(rd());

                // Specify the randomizer to return values between 10000 and 99999
                uniform_int_distribution<int> distribution(10000, 99999);

                // Pass the engine variable into the distribution to generate a random number and assign it to the randomGenerated integer variable
                int randomGenerated = distribution(engine), currentRand;
                stringstream  ss;


                int leadingZeros = 5 - to_string(randomGenerated).length();
                    ss << string(leadingZeros, '0') << randomGenerated;
                    currentRand = stoi(ss.str());

                bool uniqueFound = false;

                // Iterate through all currently registered accounts and check if the newly generated account number doesn't exist, if so add it for the new user
                for (int i = 0; i < currentAccountIndex + 1; i++) {
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
                char choice;


                while (accountFound == 0) {
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

                string accountPassword; bool passwordValidated = false; int passwordTries = 4;

                // Verify password
                while (!passwordValidated && passwordTries > 0) {
                    accountPassword = "";
                    cout << "Please enter the password of your account: ";

                    passwordTries == 4 ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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
                    amountIterator: double moneyAmount, convertedAmount; int currency;

                    // Get the currency the user has and convert it to a birr
                    cout << "Enter the currency you have:\n";

                    cout << "[1] US Dollar\n";
                    cout << "[2] Pound\n";
                    cout << "[3] Euro\n";
                    cout << "[4] Birr\n\n";
                    cin >> currency;

                    cout << "Enter the amount of money you want to deposit: ";
                    cin >> moneyAmount;

                    if (moneyAmount >= 0.1) {
                        convertedAmount = moneyAmount * rates[currency - 1];
                        balances[accountIndex] += convertedAmount;

                        // String manipulating data types
                        ostringstream ossDate;
                        ostringstream ossTime;

                        string dateTimeNow;

                        // Get the system's current date/time
                        currentTime = time(0);

                        localTime = /* Convert the system time into a tm structure */ localtime(&currentTime);


                        ossDate << /* Format local time into a string */ put_time(localTime, "%d-%m-%Y ");
                        ossTime << put_time(localTime, "%I:%M %p");
                        dateTimeNow = ossDate.str() + ossTime.str();

                        // Assign values to arrays respectively
                        transactionMoneyAmount[currentTransactionIndex] = convertedAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                        transactionType[currentTransactionIndex] = "Deposit";
                        transactionDates[currentTransactionIndex] = dateTimeNow;

                        currentTransactionIndex++;

                        system("cls");
                        cout << "You have successfully deposited " << convertedAmount << "birr into your account.\nYour current balance: " << balances[accountIndex] << "birr\nClick 'Y' if you want to go to main menu else click 'N' if you want to quit.\n";
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
                        localTime = localtime(&currentTime);
                        ossDate << put_time(localTime, "%d-%m-%Y ");
                        ossTime << put_time(localTime, "%I:%M %p");
                        dateTimeNow = ossDate.str() + ossTime.str();

                        transactionMoneyAmount[currentTransactionIndex] = -moneyAmount;
                        transactionAccountNumbers[currentTransactionIndex] = accountNumbers[accountIndex];
                        transactionType[currentTransactionIndex] = "Withdrawal";
                        transactionDates[currentTransactionIndex] = dateTimeNow;


                        currentTransactionIndex++;

                        system("cls");
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
                        localTime = localtime(&currentTime);
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

                        system("cls");
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
                        // Display transaction records where account number equals the signed-in user account number
                        if (transactionAccountNumbers[i] == accountNumbers[accountIndex]) {
                            cout << "|" << setw(typeWidth + 7) << left << transactionType[i] << "|";
                                    // Change the console text to red if money is lost from the account or green if a money is desposited or trasferred in to the account
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

                    cout << "Account balance: " << balances[accountIndex] << endl;
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

                    cout << "Choose the currency you want to convert from:\n";

                    cout << "[1] US Dollar\n";
                    cout << "[2] Pound\n";
                    cout << "[3] Euro\n";
                    cout << "[4] Birr\n\n";
                    cin >> currencyFrom;

                    cout << "Choose the currency you want to convert to:\n";

                    cout << "[1] US Dollar\n";
                    cout << "[2] Pound\n";
                    cout << "[3] Euro\n";
                    cout << "[4] Birr\n\n";

                    cin >> currencyTo;

                    cout << "Enter the amount of money you want to convert: ";
                    cin >> amount;


                    toBirr = amount * rates[currencyFrom - 1];
                    finalResult = toBirr / rates[currencyTo - 1];

                    cout << "fr " << finalResult;

                }
            }
            break;

            case 8: {
                system("cls");

                bool passwordValidated = false; int passwordTries = 4;
                string adminPasswordInput;
                cout << "Enter administrator password: ";


                while (!passwordValidated && passwordTries > 0) {
                    cout << "Please enter the password of your account: \n";
                    getline(cin.ignore(), adminPasswordInput);

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

                    // Calculate maximum column widths
                    for (int i = 0; i < currentTransactionIndex; i++) {
                        typeWidth = max(typeWidth, static_cast<int>(transactionType[i].length()));
                        amountWidth = max(amountWidth, static_cast<int>(to_string(transactionMoneyAmount[i]).length()));
                        dateWidth = max(dateWidth, static_cast<int>(transactionDates[i].length()));
                        accountWidth = max(accountWidth, static_cast<int>(to_string(transactionAccountNumbers[i]).length()));
                    }

                    // Add some padding to the maximum widths
                    typeWidth += 2;
                    amountWidth += 2;
                    dateWidth += 2;
                    accountWidth += 2;

                    // Print table header
                    cout << "+" << string(typeWidth + 7, '-') << "+" << string(accountWidth + 7, '-') << "+" << string(amountWidth, '-') << "+" << string(dateWidth, '-') << "+\n";
                    cout << "|" << setw(typeWidth + 7) << right << "Transaction Type" << "|" << setw(accountWidth) << right << "Account Number" << "|" <<  setw(amountWidth) << right << "Amount" << "|" << setw(dateWidth) << right << "Date" << "|\n";
                    cout << "+" << string(typeWidth + 7, '-') << "+" << string(accountWidth + 7, '-') << "+" << string(amountWidth, '-') << "+" << string(dateWidth, '-') << "+\n";


                    for (int i = 0; i < currentTransactionIndex; i++) {
                            cout << "|" << setw(typeWidth + 7) << left << transactionType[i] << "|" << setw(accountWidth + 7) << right << transactionAccountNumbers[i] << "|" << setw(amountWidth) << right << transactionMoneyAmount[i] << "|" << setw(dateWidth) << left << transactionDates[i] << "|\n";
                    }

                    // Print table footer
                    cout << "+" << string(typeWidth + 7, '-') << "+" << string(accountWidth + 7, '-') << "+" << string(amountWidth, '-') << "+" << string(dateWidth, '-') << "+\n";

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
                        cout << "If you want to re-enter your account number press [Y] else if you want to go to main menu click any key:";
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

                    passwordTries == 4 ? getline(cin.ignore(), accountPassword) : getline(cin, accountPassword);

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
                            cout << "The account number you entered is not found, try again.\n";
                        }
                    }

                    cout << "Enter the amount of money you want to transfer every time: ";
                    cin >> moneyAmount;


                    recurIterator: cout << "[1] Every day\n[2] Every week\n[3] Every month\n";
                    cout << "Enter the frequency between each payment:\n";

                    cin >> transactionFrequency;

                    switch (transactionFrequency) {
                        case 1: {
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
                            cout << "[1] Sunday\n[2] Monday\n[3] Tuesday\n[4] Wednesday\n[5] Thursday\n[6] Friday\n[7] Saturday\n";
                            cout << "Enter the week day for the payment to recur (from 1-7 as above stated): ";
                            cin >> transactionTime;

                            recurringPaymentFrom[currentRecurringIndex] = accountIndex;
                            recurringPaymentTo[currentRecurringIndex] = receiverAccountIndex;
                            recurringPaymentFrequency[currentRecurringIndex] = transactionFrequency;
                            recurringMoneyAmount[currentRecurringIndex] = moneyAmount;
                            recurringPaymentTime[currentRecurringIndex] = transactionTime - 1;

                            currentRecurringIndex++;

                            cout << "A payment of" << moneyAmount << "birr " << "has been successfully to recur every week-day at day" << transactionTime << " from the account number " << accountNumbers[accountIndex] << " to " << names[receiverAccountIndex] << "\nChoose [Y] if you want to go to main menu or any other key if you want to quit: ";
                            cin >> choice;

                            if (choice == 'Y' || choice == 'y') {
                                goto menuIterator;
                            }
                        }
                        break;

                        case 3: {
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

        break;
    }

    return 0;
}

