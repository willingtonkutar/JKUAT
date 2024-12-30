#include "admin.h"
#include <iostream>

Admin::Admin(std::string name, std::string userID, std::string password) : User(name, userID), password(password) {}

void Admin::displayDetails() {
    std::cout << "Admin Name: " << name << ", UserID: " << userID << std::endl;
}

void Admin::addProduct(std::vector<Product> &products, const std::string &name, double price, int stock) {
    products.emplace_back(name, price, stock);
    std::cout << "Product added successfully!" << std::endl;
}

void Admin::removeProduct(std::vector<Product> &products, const std::string &name) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getName() == name) {
            products.erase(it);
            std::cout << "Product removed successfully!" << std::endl;
            return;
        }
    }
    std::cout << "Product not found!" << std::endl;
}

bool Admin::checkPassword(const std::string &inputPassword) const {
    return inputPassword == password;
}