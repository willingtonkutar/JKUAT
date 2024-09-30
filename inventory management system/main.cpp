#include "inventory.h"
#include <iostream>

void displayMenu() {
    std::cout << "1. Add Product" << std::endl;
    std::cout << "2. Update Product Quantity" << std::endl;
    std::cout << "3. Generate Report" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

int main() {
    Inventory inventory;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            double price;
            int quantity;

            std::cout << "Enter product name: ";
            std::cin >> name;
            std::cout << "Enter product price: ";
            std::cin >> price;
            std::cout << "Enter product quantity: ";
            std::cin >> quantity;

            Product product(name, price, quantity);
            inventory.addProduct(product);
        } else if (choice == 2) {
            std::string name;
            int quantity;

            std::cout << "Enter product name: ";
            std::cin >> name;
            std::cout << "Enter new quantity: ";
            std::cin >> quantity;

            inventory.updateProductQuantity(name, quantity);
        } else if (choice == 3) {
            inventory.generateReport();
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }

    return 0;
}