#include "customer.h"
#include <iostream>

Customer::Customer(std::string name, std::string userID) : User(name, userID) {}

void Customer::displayDetails() {
    std::cout << "Customer Name: " << name << ", UserID: " << userID << std::endl;
}