#include "order.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Order::Order(std::string customerID) : customerID(customerID) {}

void Order::addProduct(const Product &product, int quantity) {
    orderedProducts.push_back(std::make_pair(product, quantity));
}

bool Order::isEmpty() const {
    return orderedProducts.empty();
}

void Order::displayOrder() const {
    std::cout << "Order for Customer ID: " << customerID << std::endl;
    for (const auto &entry : orderedProducts) {
        std::cout << "Product: " << entry.first.getName() << ", Price: " << entry.first.getPrice() << ", Quantity: " << entry.second << std::endl;
    }
}

void Order::saveToFile(const std::string &filename) {
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        throw std::runtime_error("Error opening file for writing.");
    }

    outFile << "Customer ID: " << customerID << std::endl;
    for (const auto &entry : orderedProducts) {
        outFile << entry.first.getName() << ", " << entry.first.getPrice() << ", " << entry.second << std::endl;
    }
    outFile.close();
}