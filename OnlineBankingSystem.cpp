#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

//Account Class
class Account {
public:
    string accountNumber;
    string name;
    double balance;

    Account(string accNo, string accName, double bal) {
        accountNumber = accNo;
        name = accName;
        balance = bal;
    }

    // Deposit Money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successfu..your new balance is: " << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw Money
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! your new balance is : "<< balance << endl;
            return true;
        } else {
            cout << "Insufficient funds or invalid amount!" << endl;
            return false;
        }
    }

    // Display Account Info
    void display() {
        cout << "\n--- Account Details ---\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder name: " << name << endl;
        cout << "Balance: "<< balance << endl;
    }
};

void saveAccounts(const vector<Account> &accounts) {
    ofstream file("accounts.txt");
    for (const auto &acc : accounts) {
        file << acc.accountNumber << " " << acc.name << " " << acc.balance << endl;
    }
    file.close();
}

// Function to Load Accounts from File
vector<Account> loadAccounts() {
    vector<Account> accounts;
    ifstream file("accounts.txt");
    string accNo, name;
    double balance;
    while (file >> accNo >> ws && getline(file, name, ' ') && file >> balance) {
        accounts.push_back(Account(accNo, name, balance));
    }
    file.close();
    return accounts;
}

// Function to Find Account by Number
Account* findAccount(vector<Account> &accounts, string accNo) {
    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) {
            return &acc;
        }
    }
    return nullptr;
}
//main 
int main() {
    vector<Account> accounts = loadAccounts();
    int choice;

    do {
        cout << "\n-----Online Banking System----\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Money\n";
        cout << "5. View Account\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string accNo, name;
            double balance;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Deposit Amount: ";
            cin >> balance;

            accounts.push_back(Account(accNo, name, balance));
            saveAccounts(accounts);
            cout << "Account created successfully!" << endl;

        } else if (choice == 2) {
            string accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            Account *acc = findAccount(accounts, accNo);
            if (acc) {
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                acc->deposit(amount);
                saveAccounts(accounts);
            } else {
                cout << "Account not found!" << endl;
            }

        } else if (choice == 3) {
            string accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;
            Account *acc = findAccount(accounts, accNo);
            if (acc) {
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                if (acc->withdraw(amount)) {
                    saveAccounts(accounts);
                }
            } else {
                cout << "Account not found!" << endl;
            }

        } else if (choice == 4) {
            string senderAccNo, receiverAccNo;
            double amount;
            cout << "Enter Sender Account Number: ";
            cin >> senderAccNo;
            cout << "Enter Receiver Account Number: ";
            cin >> receiverAccNo;
            cout << "Enter Transfer Amount: ";
            cin >> amount;

            Account *sender = findAccount(accounts, senderAccNo);
            Account *receiver = findAccount(accounts, receiverAccNo);

            if (sender && receiver) {
                if (sender->withdraw(amount)) {
                    receiver->deposit(amount);
                    saveAccounts(accounts);
                    cout << "Transfer successful!" << endl;
                }
            } else {
                cout << "Invalid account details!" << endl;
            }

        } else if (choice == 5) {
            string accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            Account *acc = findAccount(accounts, accNo);
            if (acc) {
                acc->display();
            } else {
                cout << "Account not found!" << endl;
            }
        }

    } while (choice != 6);

    cout << "Thanks for contacting with Online Banking System...." << endl;
    return 0;
}