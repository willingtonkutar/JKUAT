#include "inventory.h"
#include <iostream>

void displayMenu() {
    std::cout << "1. Add Product" << std::endl;
    std::cout << "2. Update Product Quantity" << std::endl;
    std::cout << "3. Update Product Price" << std::endl;
    std::cout << "4. Delete Product" << std::endl;
    std::cout << "5. Search Product" << std::endl;
    std::cout << "6. Sort Products by Name" << std::endl;
    std::cout << "7. Sort Products by Price" << std::endl;
    std::cout << "8. Sort Products by Quantity" << std::endl;
    std::cout << "9. Generate Report" << std::endl;
    std::cout << "10. Save Inventory to File" << std::endl;
    std::cout << "11. Load Inventory from File" << std::endl;
    std::cout << "12. Exit" << std::endl;
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
            std::string name;
            double price;

            std::cout << "Enter product name: ";
            std::cin >> name;
            std::cout << "Enter new price: ";
            std::cin >> price;

            inventory.updateProductPrice(name, price);
        } else if (choice == 4) {
            std::string name;

            std::cout << "Enter product name: ";
            std::cin >> name;

            inventory.deleteProduct(name);
        } else if (choice == 5) {
            std::string name;

            std::cout << "Enter product name: ";
            std::cin >> name;

            Product* product = inventory.searchProduct(name);
            if (product) {
                product->display();
            } else {
                std::cout << "Product not found!" << std::endl;
            }
        } else if (choice == 6) {
            inventory.sortByName();
        } else if (choice == 7) {
            inventory.sortByPrice();
        } else if (choice == 8) {
            inventory.sortByQuantity();
        } else if (choice == 9) {
            inventory.generateReport();
        } else if (choice == 10) {
            std::string filename;

            std::cout << "Enter filename: ";
            std::cin >> filename;

            inventory.saveToFile(filename);
        } else if (choice == 11) {
            std::string filename;

            std::cout << "Enter filename: ";
            std::cin >> filename;

            inventory.loadFromFile(filename);
        } else if (choice == 12) {
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }

        // Add a blank line before displaying the menu again
        std::cout << std::endl;
    }

    return 0;
}