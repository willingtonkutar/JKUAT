#include "inventory.h"
#include <iostream>

void Inventory::addProduct(const Product& product) {
    products.push_back(product);
}

void Inventory::updateProductQuantity(const std::string& name, int quantity) {
    for (auto& product : products) {
        if (product.getName() == name) {
            product.setQuantity(quantity);
            return;
        }
    }
    std::cout << "Product not found!" << std::endl;
}

void Inventory::generateReport() const {
    for (const auto& product : products) {
        product.display();
    }
}