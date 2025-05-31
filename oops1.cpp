#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// Abstract base Account class
class Account {
private:
    int accountNumber;
    string accountHolderName;
    string password;
    double balance;

protected:
    // Protected constructor so derived classes can use
    Account(int accNum, const string& name, const string& pwd, double initialBalance)
        : accountNumber(accNum), accountHolderName(name), password(pwd), balance(initialBalance) {}

public:
    virtual ~Account() {}

    // Encapsulation: accessors
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // Mutators with validation
    void setAccountHolderName(const string& name) { accountHolderName = name; }

    // Password validation
    bool checkPassword(const string& pwd) const {
        return pwd == password;
    }

    void setPassword(const string& newPwd) {
        password = newPwd;
    }

    // Deposit money
    virtual void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive!" << endl;
            return;
        }
        balance += amount;
        cout << "Deposited $" << amount << " into account " << accountNumber << endl;
    }

    // Withdraw money - virtual for override
    virtual bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive!" << endl;
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient funds in account " << accountNumber << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrew $" << amount << " from account " << accountNumber << endl;
        return true;
    }

    // Abstract display info
    virtual void displayAccountInfo() const = 0;
};

// CurrentAccount class
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNum, const string& name, const string& pwd, double initialBalance, double overdraft)
        : Account(accNum, name, pwd, initialBalance), overdraftLimit(overdraft) {}

    bool withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive!" << endl;
            return false;
        }
        if (amount > getBalance() + overdraftLimit) {
            cout << "Overdraft limit exceeded in current account " << getAccountNumber() << endl;
            return false;
        }
        // Use base class balance manipulation
        return Account::withdraw(amount);
    }

    void displayAccountInfo() const override {
        cout << "Current Account #" << getAccountNumber() << endl;
        cout << "Holder Name   : " << getAccountHolderName() << endl;
        cout << "Balance       : $" << fixed << setprecision(2) << getBalance() << endl;
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
        cout << "--------------------------" << endl;
    }
};

// Bank class to manage accounts
class Bank {
private:
    vector<Account*> accounts;
    int nextAccountNumber;

public:
    Bank() : nextAccountNumber(1001) {}
    ~Bank() {
        for (auto acc : accounts) {
            delete acc;
        }
    }

    void createCurrentAccount(const string& name, const string& pwd, double initialDeposit, double overdraft) {
        Account* acc = new CurrentAccount(nextAccountNumber++, name, pwd, initialDeposit, overdraft);
        accounts.push_back(acc);
        cout << "Current account created with account number: " << acc->getAccountNumber() << endl;
    }

    Account* findAccount(int accountNumber) {
        for (auto acc : accounts) {
            if (acc->getAccountNumber() == accountNumber) {
                return acc;
            }
        }
        return nullptr;
    }

    // Interactive login and operations
    void run() {
        while (true) {
            cout << "\n--- Bank Management System ---\n";
            cout << "1. Create Current Account\n";
            cout << "2. Login to Account\n";
            cout << "3. Exit\n";
            cout << "Choose option: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1) {
                createAccountMenu();
            } else if (choice == 2) {
                loginMenu();
            } else if (choice == 3) {
                cout << "Exiting... Goodbye!" << endl;
                break;
            } else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void createAccountMenu() {
        string name, password;
        double initialDeposit, overdraft;

        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Set your password: ";
        getline(cin, password);
        cout << "Initial deposit: $";
        cin >> initialDeposit;
        cout << "Set overdraft limit: $";
        cin >> overdraft;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        createCurrentAccount(name, password, initialDeposit, overdraft);
    }

    void loginMenu() {
        int accNum;
        string pwd;

        cout << "Enter account number: ";
        cin >> accNum;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter password: ";
        getline(cin, pwd);

        Account* acc = findAccount(accNum);
        if (!acc) {
            cout << "Account not found." << endl;
            return;
        }
        if (!acc->checkPassword(pwd)) {
            cout << "Incorrect password." << endl;
            return;
        }

        cout << "Login successful!\n";
        accountOperationsMenu(acc);
    }

    void accountOperationsMenu(Account* acc) {
        while (true) {
            cout << "\n--- Account Menu (Acc #: " << acc->getAccountNumber() << ") ---\n";
            cout << "1. View Account Info\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Update Account Holder Name\n";
            cout << "5. Change Password\n";
            cout << "6. Logout\n";
            cout << "Choose option: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1) {
                acc->displayAccountInfo();
            } else if (choice == 2) {
                cout << "Enter deposit amount: $";
                double amount;
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                acc->deposit(amount);
            } else if (choice == 3) {
                cout << "Enter withdrawal amount: $";
                double amount;
                cin >> amount;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                acc->withdraw(amount);
            } else if (choice == 4) {
                cout << "Enter new account holder name: ";
                string newName;
                getline(cin, newName);
                acc->setAccountHolderName(newName);
                cout << "Name updated successfully." << endl;
            } else if (choice == 5) {
                cout << "Enter current password: ";
                string currPwd;
                getline(cin, currPwd);
                if (!acc->checkPassword(currPwd)) {
                    cout << "Incorrect current password." << endl;
                    continue;
                }
                cout << "Enter new password: ";
                string newPwd;
                getline(cin, newPwd);
                acc->setPassword(newPwd);
                cout << "Password changed successfully." << endl;
            } else if (choice == 6) {
                cout << "Logging out..." << endl;
                break;
            } else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }
};

int main() {
    Bank bank;
    bank.run();
    return 0;
}
