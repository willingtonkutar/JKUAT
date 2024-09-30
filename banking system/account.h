// account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <fstream>
#include <iostream>

class Account {
public:
    Account(const std::string& accountNumber, const std::string& accountHolderName, double balance)
        : accountNumber(accountNumber), accountHolderName(accountHolderName), balance(balance) {}

    virtual ~Account() = default;

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        } else {
            std::cout << "Insufficient balance." << std::endl;
        }
    }

    virtual void display() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolderName << std::endl;
        std::cout << "Balance: " << balance << std::endl;
    }

    virtual void saveToFile(std::ofstream& outFile) const {
        outFile << accountNumber << std::endl;
        outFile << accountHolderName << std::endl;
        outFile << balance << std::endl;
    }

    virtual std::string getAccountNumber() const {
        return accountNumber;
    }

protected:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;
};

class CurrentAccount : public Account {
public:
    CurrentAccount(const std::string& accountNumber, const std::string& accountHolderName, double balance, double overdraftLimit)
        : Account(accountNumber, accountHolderName, balance), overdraftLimit(overdraftLimit) {}

    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
        } else {
            std::cout << "Overdraft limit exceeded." << std::endl;
        }
    }

    void manageOverdraft(double newLimit) {
        overdraftLimit = newLimit;
    }

    void display() const override {
        Account::display();
        std::cout << "Overdraft Limit: " << overdraftLimit << std::endl;
    }

    void saveToFile(std::ofstream& outFile) const override {
        Account::saveToFile(outFile);
        outFile << overdraftLimit << std::endl;
    }

private:
    double overdraftLimit;
};

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& accountNumber, const std::string& accountHolderName, double balance, double interestRate)
        : Account(accountNumber, accountHolderName, balance), interestRate(interestRate) {}

    void calculateInterest() {
        double interest = balance * interestRate / 100.0;
        balance += interest;
        std::cout << "Interest of " << interest << " applied. New balance: " << balance << std::endl;
    }

    void display() const override {
        Account::display();
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
    }

    void saveToFile(std::ofstream& outFile) const override {
        Account::saveToFile(outFile);
        outFile << interestRate << std::endl;
    }

private:
    double interestRate;
};

#endif // ACCOUNT_H
