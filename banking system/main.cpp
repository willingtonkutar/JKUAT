// main.cpp
#include "account.h"
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

void displayMainMenu() {
    std::cout << "1. Open Current Account" << std::endl;
    std::cout << "2. Open Savings Account" << std::endl;
    std::cout << "3. Login" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void displayCurrentAccountMenu() {
    std::cout << "1. Deposit" << std::endl;
    std::cout << "2. Withdraw" << std::endl;
    std::cout << "3. Manage Overdraft" << std::endl;
    std::cout << "4. Display Account" << std::endl;
    std::cout << "5. Save Account" << std::endl;
    std::cout << "6. Logout" << std::endl;
}

void displaySavingsAccountMenu() {
    std::cout << "1. Deposit" << std::endl;
    std::cout << "2. Withdraw" << std::endl;
    std::cout << "3. Calculate Interest" << std::endl;
    std::cout << "4. Display Account" << std::endl;
    std::cout << "5. Save Account" << std::endl;
    std::cout << "6. Logout" << std::endl;
}

std::unique_ptr<Account> login(const std::vector<std::unique_ptr<Account>>& accounts) {
    std::string accountNumber;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;

    for (const auto& account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            return std::make_unique<Account>(*account);
        }
    }

    std::cout << "Account not found!" << std::endl;
    return nullptr;
}

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    int choice;

    while (true) {
        displayMainMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string accountNumber, accountHolderName;
            double balance, overdraftLimit;

            std::cout << "Enter account number: ";
            std::cin >> accountNumber;
            std::cout << "Enter account holder name: ";
            std::cin.ignore();
            std::getline(std::cin, accountHolderName);
            std::cout << "Enter initial balance: ";
            std::cin >> balance;
            std::cout << "Enter overdraft limit: ";
            std::cin >> overdraftLimit;

            accounts.push_back(std::make_unique<CurrentAccount>(accountNumber, accountHolderName, balance, overdraftLimit));
        } else if (choice == 2) {
            std::string accountNumber, accountHolderName;
            double balance, interestRate;

            std::cout << "Enter account number: ";
            std::cin >> accountNumber;
            std::cout << "Enter account holder name: ";
            std::cin.ignore();
            std::getline(std::cin, accountHolderName);
            std::cout << "Enter initial balance: ";
            std::cin >> balance;
            std::cout << "Enter interest rate: ";
            std::cin >> interestRate;

            accounts.push_back(std::make_unique<SavingsAccount>(accountNumber, accountHolderName, balance, interestRate));
        } else if (choice == 3) {
            auto account = login(accounts);
            if (account) {
                if (dynamic_cast<CurrentAccount*>(account.get())) {
                    while (true) {
                        displayCurrentAccountMenu();
                        std::cout << "Enter your choice: ";
                        std::cin >> choice;

                        if (choice == 1) {
                            double amount;
                            std::cout << "Enter amount to deposit: ";
                            std::cin >> amount;
                            account->deposit(amount);
                        } else if (choice == 2) {
                            double amount;
                            std::cout << "Enter amount to withdraw: ";
                            std::cin >> amount;
                            account->withdraw(amount);
                        } else if (choice == 3) {
                            double limit;
                            std::cout << "Enter new overdraft limit: ";
                            std::cin >> limit;
                            dynamic_cast<CurrentAccount*>(account.get())->manageOverdraft(limit);
                        } else if (choice == 4) {
                            account->display();
                        } else if (choice == 5) {
                            std::string filename;
                            std::cout << "Enter filename to save: ";
                            std::cin >> filename;
                            std::ofstream outFile(filename);
                            if (outFile.is_open()) {
                                account->saveToFile(outFile);
                                outFile.close();
                                std::cout << "Account saved successfully.\n";
                            } else {
                                std::cout << "Unable to open file for writing.\n";
                            }
                        } else if (choice == 6) {
                            break;
                        }
                    }
                } else if (dynamic_cast<SavingsAccount*>(account.get())) {
                    while (true) {
                        displaySavingsAccountMenu();
                        std::cout << "Enter your choice: ";
                        std::cin >> choice;

                        if (choice == 1) {
                            double amount;
                            std::cout << "Enter amount to deposit: ";
                            std::cin >> amount;
                            account->deposit(amount);
                        } else if (choice == 2) {
                            double amount;
                            std::cout << "Enter amount to withdraw: ";
                            std::cin >> amount;
                            account->withdraw(amount);
                        } else if (choice == 3) {
                            dynamic_cast<SavingsAccount*>(account.get())->calculateInterest();
                        } else if (choice == 4) {
                            account->display();
                        } else if (choice == 5) {
                            std::string filename;
                            std::cout << "Enter filename to save: ";
                            std::cin >> filename;
                            std::ofstream outFile(filename);
                            if (outFile.is_open()) {
                                account->saveToFile(outFile);
                                outFile.close();
                                std::cout << "Account saved successfully.\n";
                            } else {
                                std::cout << "Unable to open file for writing.\n";
                            }
                        } else if (choice == 6) {
                            break;
                        } else {
                            std::cout << "Invalid choice!" << std::endl;
                        }
                    }
                }
            }
        } else if (choice == 4) {
            break; // Exit the program
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }

        // Add a blank line before displaying the menu again
        std::cout << std::endl;
    }

    return 0;
}
