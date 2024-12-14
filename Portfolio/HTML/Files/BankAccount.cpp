#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   

using namespace std;

namespace PiggiesBank {
    const int MAX_ACCOUNTS = 100;
    int accountCount = 0;
    int accountNumbers[MAX_ACCOUNTS];
    string accountNames[MAX_ACCOUNTS];
    double accountBalances[MAX_ACCOUNTS];
    int accountPins[MAX_ACCOUNTS];

    void createAccount() {
        if (accountCount >= MAX_ACCOUNTS) {
            cout << "Cannot create more accounts. Maximum accounts reached.\n";
            return;
        }

        cout << "\n=========================================================================\n"
             << "                         Create New Piggy Account                          \n"
             << "=========================================================================\n";

        srand(time(0));
        int newAccountNumber;
        bool isUnique;

        do {
            newAccountNumber = rand() % 9000000 + 1000000;
            isUnique = true;

            for (int i = 0; i < accountCount; i++) {
                if (accountNumbers[i] == newAccountNumber) {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);

        accountNumbers[accountCount] = newAccountNumber;
        cout << "Generated Account Number: " << newAccountNumber << endl;

        cin.ignore();
        cout << "Enter Account Name: ";
        getline(cin, accountNames[accountCount]);

        while (true) {
            cout << "Enter starting balance (should not be below 2000): ";
            cin >> accountBalances[accountCount];
            if (cin.fail() || accountBalances[accountCount] < 2000) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid balance. Please enter again.\n";
            } else {
                break;
            }
        }

        while (true) {
            cout << "Set a 5-digit PIN for your account: ";
            cin >> accountPins[accountCount];
            if (cin.fail() || accountPins[accountCount] < 10000 || accountPins[accountCount] > 99999) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid PIN. Please enter a 5-digit number.\n";
            } else {
                break;
            }
        }

        accountCount++;
        cout << "Piggy Account Created Successfully.\n\n";
    }

    void displayAccounts() {
        if (accountCount == 0) {
            cout << "\nNo piggy accounts found.\n";
            return;
        }

        cout << "\n=== Account Details ===\n";
        for (int i = 0; i < accountCount; i++) {
            cout << "Name: " << accountNames[i] << endl
                 << "Balance: ₱" << accountBalances[i] << endl
                 << "=======================\n";
        }
    }

    void updateAccount() {
        if (accountCount == 0) {
            cout << "\nNo accounts available to update.\n";
            return;
        }

        int accountNumber, pin;
        cout << "\nEnter account number to update: ";
        cin >> accountNumber;

        for (int i = 0; i < accountCount; i++) {
            if (accountNumbers[i] == accountNumber) {
                cout << "Enter your 5-digit PIN: ";
                cin >> pin;
                if (pin != accountPins[i]) {
                    cout << "Invalid PIN. Access denied.\n";
                    return;
                }

                int choice;
                cout << "\n=== Update Account ===\n"
                     << "1. Deposit Amount\n"
                     << "2. Withdraw Amount\n"
                     << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1: {
                        double depositAmount;
                        cout << "Enter amount to deposit: ";
                        cin >> depositAmount;

                        if (depositAmount <= 0) {
                            cout << "Invalid amount. Deposit must be greater than 0.\n";
                        } else {
                            accountBalances[i] += depositAmount;
                            cout << "Amount deposited successfully. New balance: $" << accountBalances[i] << "\n";
                        }
                        break;
                    }
                    case 2: {
                        double withdrawAmount;
                        cout << "Enter amount to withdraw: ";
                        cin >> withdrawAmount;

                        if (withdrawAmount <= 0) {
                            cout << "Invalid amount. Withdrawal must be greater than 0.\n";
                        } else if (withdrawAmount > accountBalances[i]) {
                            cout << "Insufficient balance. Current balance: $" << accountBalances[i] << "\n";
                        } else {
                            accountBalances[i] -= withdrawAmount;
                            cout << "Amount withdrawn successfully. New balance: $" << accountBalances[i] << "\n";
                        }
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void deleteAccount() {
        if (accountCount == 0) {
            cout << "\nNo accounts available to delete.\n";
            return;
        }

        int accountNumber, pin;
        cout << "\nEnter account number to delete: ";
        cin >> accountNumber;

        for (int i = 0; i < accountCount; i++) {
            if (accountNumbers[i] == accountNumber) {
                cout << "Enter your 5-digit PIN: ";
                cin >> pin;
                if (pin != accountPins[i]) {
                    cout << "Invalid PIN. Access denied.\n";
                    return;
                }

                for (int j = i; j < accountCount - 1; j++) {
                    accountNumbers[j] = accountNumbers[j + 1];
                    accountNames[j] = accountNames[j + 1];
                    accountBalances[j] = accountBalances[j + 1];
                    accountPins[j] = accountPins[j + 1];
                }
                accountCount--;
                cout << "Account deleted successfully.\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void displayMenu() {
        cout << "=========================================\n"
             << "Account Count: " << accountCount << "\n"
             << "=========================================\n"
             << "\n============ Piggy Bank ===============\n"
             << "1. Create Piggy Account\n"
             << "2. Display Piggy Accounts\n"
             << "3. Update Piggy Account (Deposit/Withdraw)\n"
             << "4. Delete Piggy Account\n"
             << "5. Exit\n"
             << "Enter your choice: ";
    }
}

int main() {
    int choice;

    do {
        PiggiesBank::displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                PiggiesBank::createAccount();
                break;
            case 2:
                PiggiesBank::displayAccounts();
                break;
            case 3:
                PiggiesBank::updateAccount();
                break;
            case 4:
                PiggiesBank::deleteAccount();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
