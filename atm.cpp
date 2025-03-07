#include <iostream>
using namespace std;

class ATM {
private:
    double balance;

public:
    ATM(double accountbalance) {
        balance = accountbalance;
    }

    void checkBalance() {
        cout << "Current balance: Rs " << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: Rs " << amount << endl;
        } else {
            cout << "Invalid amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: Rs " << amount << endl;
        } else if (amount > balance) {
            cout << "Not Enough Balance....!" << endl;
        } else {
            cout << "Invalid amount....!" << endl;
        }
    }
};

void displayAtm() {
     cout << "-----------------------------------------------------------WELCOME-----------------------------------------------------------------------------" << endl;
    cout << "ATM:" << endl;
    cout << "1. Check Balance" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    ATM atm(150000.0); 
    int choice;
    double amount;

    do {
        displayAtm();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            atm.checkBalance();
            break;
        case 2:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            atm.deposit(amount);
            break;
        case 3:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            atm.withdraw(amount);
            break;
        case 4:
            cout << "Thank you for using the ATM. Have a great day ahead!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl;
    } 
    while (choice != 4);
    return 0;
}
