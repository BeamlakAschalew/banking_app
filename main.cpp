#include <iostream>
#include <string>


using namespace std;

int main() {

    const int maxAccounts = 50;

    string names[maxAccounts];
    double balances[maxAccounts];
    string passwords[maxAccounts];
    int accountNumbers[maxAccounts];
    string secretCodes[maxAccounts];

    int userChoice;



    while (true) {
        cout << "1. Create an account";
        cin >> userChoice;


        switch (userChoice) {
        case 1:
            cout << "Enter Name: " << endl;
            getline(cin.ignore(), names[0]);

            
            break;
        
        default:
            break;
        }

        cout << names[0];
        break;
    }

    return 0;
}