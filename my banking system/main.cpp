#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <vector>
#include <iomanip> // For setw and setprecision

using namespace std;

struct User {
    int accountNumber;
    string username;
    string password;
    string accountType;
    double balance;
    double overdraftLimit; // For current accounts
    vector<string> transactions; // To track transactions
};

// Function to generate a random account number
int generateAccountNumber() {
    srand(time(0)); // Seed random number generator with current time
    return rand() % 1000000000 + 1000000000; // Generate a random 9-digit account number
}

// Function to store user data in a file
void storeUserData(const User &user) {
    ofstream file("users.txt", ios::app); // Open the file in append mode
    if (file.is_open()) {
        file << user.accountNumber << " " << user.username << " " << user.password << " "
             << user.accountType << " " << user.balance << " " << user.overdraftLimit << endl; // Save overdraft limit
        file.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

// Function to load all users from the file
vector<User> loadAllUsers() {
    vector<User> users;
    ifstream file("users.txt");
    if (file.is_open()) {
        User user;
        while (file >> user.accountNumber >> user.username >> user.password >> user.accountType >> user.balance >> user.overdraftLimit) { // Load overdraft limit
            users.push_back(user);
        }
        file.close();
    } else {
        cout << "Error opening file for reading." << endl;
    }
    return users;
}

// Function to save all users back to the file (overwrite)
void saveAllUsers(const vector<User> &users) {
    ofstream file("users.txt", ios::trunc); // Open the file in truncate mode (overwrite)
    if (file.is_open()) {
        for (const auto &user : users) {
            file << user.accountNumber << " " << user.username << " " << user.password << " "
                 << user.accountType << " " << user.balance << " " << user.overdraftLimit << endl; // Save overdraft limit
        }
        file.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
}

// Function to update the user's balance in the file
void updateUserBalance(const User &currentUser) {
    vector<User> users = loadAllUsers();  // Load all users
    for (auto &user : users) {
        if (user.username == currentUser.username) {
            user.balance = currentUser.balance;  // Update the balance in memory
        }
    }
    saveAllUsers(users);  // Save all users (including the updated balance) back to the file
}

// Function to load user data from a file based on login credentials
bool loadUserData(const string &username, const string &password, User &user) {
    ifstream file("users.txt");
    if (file.is_open()) {
        while (file >> user.accountNumber >> user.username >> user.password >> user.accountType >> user.balance >> user.overdraftLimit) { // Load overdraft limit
            if (user.username == username && user.password == password) {
                return true; // Login success, data loaded
            }
        }
        file.close();
    } else {
        cout << "Error opening file for reading." << endl;
    }
    return false; // If no match found
}

// Function to simulate account creation
bool createAccount() {
    User user;
    user.accountNumber = generateAccountNumber(); // Generate a random account number

    // Get user inputs for account creation
    cout << "Enter new username: ";
    cin >> user.username;
    cout << "Enter new password: ";
    cin >> user.password;

    // Ask the user for the account type (savings or current)
    cout << "What type of account do you want to create? (savings/current): ";
    cin >> user.accountType;

    // Check if the user entered a valid account type
    if (user.accountType != "savings" && user.accountType != "current") {
        cout << "Invalid account type. Please try again.\n";
        return false; // Invalid input
    }

    user.balance = 1.0; // Set initial balance to 1 Ksh for new accounts
    user.overdraftLimit = (user.accountType == "current") ? 100.0 : 0.0; // Set overdraft limit for current accounts

    // Store the user data in a file
    storeUserData(user);
    cout << "Account created successfully!\n";
    cout << "Your account number is: " << user.accountNumber << endl;
    return true; // Account creation successful
}

// Function to display balance
void viewBalance(const User &user) {
    cout << "Current balance: Ksh " << user.balance << endl;
}

// Function to deposit funds
void depositFunds(User &user) {
    double amount;
    cout << "Enter amount to deposit: Ksh ";
    cin >> amount;

    if (amount > 0) {
        user.balance += amount;  // Correctly add the deposit to balance
        user.transactions.push_back("Deposited: Ksh " + to_string(amount));
        cout << "Deposit successful! New balance: Ksh " << user.balance << endl;
        updateUserBalance(user);  // Save updated balance to file
    } else {
        cout << "Invalid amount entered." << endl;
    }
}

// Function to withdraw funds
void withdrawFunds(User &user) {
    double amount; // Declare the amount variable
    cout << "Enter amount to withdraw: Ksh ";
    cin >> amount;

    if (amount > 0) {
        if (user.accountType == "current") {
            // Allow overdraft
            if (amount <= user.balance + user.overdraftLimit) {
                user.balance -= amount;  // Correctly subtract the withdrawal from balance
                user.transactions.push_back("Withdrew: Ksh " + to_string(amount));
                cout << "Withdrawal successful! New balance: Ksh " << user.balance << endl;
            } else {
                cout << "Overdraft limit exceeded! You can only withdraw up to Ksh " << user.balance + user.overdraftLimit << endl;
            }
        } else if (user.accountType == "savings") {
            // Savings account withdrawal
            if (amount <= user.balance) {
                user.balance -= amount;  // Correctly subtract the withdrawal from balance
                user.transactions.push_back("Withdrew: Ksh " + to_string(amount));
                cout << "Withdrawal successful! New balance: Ksh " << user.balance << endl;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        }
        updateUserBalance(user);  // Save updated balance to file
    } else {
        cout << "Invalid amount entered." << endl;
    }
}

// Function to apply interest to savings account
void applyInterest(User &user) {
    if (user.accountType == "savings") {
        double interestRate = 0.05; // 5% interest rate
        double interest = user.balance * interestRate;
        user.balance += interest; // Apply interest
        user.transactions.push_back("Interest applied: Ksh " + to_string(interest));
        cout << "Interest applied! New balance: Ksh " << user.balance << endl;
        updateUserBalance(user); // Save updated balance to file
    } else {
        cout << "Interest can only be applied to savings accounts." << endl;
    }
}

// Function to simulate login process
bool login(User &user) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Check login credentials from the file
    if (loadUserData(username, password, user)) {
        cout << "Login successful!\n";
        cout << "Account Type: " << user.accountType << endl;
        cout << "Account Number: " << user.accountNumber << endl;
        viewBalance(user); // Show balance after login
        return true;
    } else {
        cout << "Login failed. Invalid username or password.\n";
        return false;
    }
}

// Function to generate a report for the logged-in user
void generateReport(const User &user) {
    cout << left << setw(15) << "Account No" << setw(15) << "Username" << setw(15) << "Account Type" << setw(15) << "Balance (Ksh)" << setw(20) << "Overdraft Limit (Ksh)" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << user.accountNumber << setw(15) << user.username << setw(15) << user.accountType << setw(15) << user.balance << setw(20) << user.overdraftLimit << endl;
    cout << "\nTransactions:\n";
    for (const auto &transaction : user.transactions) {
        cout << transaction << endl;
    }
}

// Main menu for current account
void currentAccountMenu(User &user) {
    int choice;
    do {
        cout << "\n--- Current Account Menu ---\n";
        cout << "1. View Balance\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Generate Report\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewBalance(user);
                break;
            case 2:
                depositFunds(user);
                break;
            case 3:
                withdrawFunds(user);
                break;
            case 4:
                generateReport(user);
                break;
            case 5:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    } while (choice != 5);
}

// Main menu for savings account
void savingsAccountMenu(User &user) {
    int choice;
    do {
        cout << "\n--- Savings Account Menu ---\n";
        cout << "1. View Balance\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Apply Interest\n";
        cout << "5. Generate Report\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewBalance(user);
                break;
            case 2:
                depositFunds(user);
                break;
            case 3:
                withdrawFunds(user);
                break;
            case 4:
                applyInterest(user); // Apply interest for savings accounts
                break;
            case 5:
                generateReport(user);
                break;
            case 6:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    } while (choice != 6);
}

// Handle login and direct to appropriate menu
void handleLogin(User &user) {
    if (login(user)) {
        if (user.accountType == "current") {
            currentAccountMenu(user); // Show current account menu
        } else if (user.accountType == "savings") {
            savingsAccountMenu(user); // Show savings account menu
        }
    }
}

int main() {
    char hasAccount;
    User currentUser;

    cout << "Do you have an account? (y/n): ";
    cin >> hasAccount;

    if (hasAccount == 'y' || hasAccount == 'Y') {
        // Try login
        handleLogin(currentUser); // Login and direct to the appropriate menu
    } else {
        // Create account flow
        if (createAccount()) {
            cout << "Account creation successful.\n";
            handleLogin(currentUser); // Login after account creation
        } else {
            cout << "Account creation failed. Please try again.\n";
        }
    }

    return 0;
}