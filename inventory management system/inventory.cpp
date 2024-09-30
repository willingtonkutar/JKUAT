#include "inventory.h"
#include <iostream>
#include <algorithm>
#include <fstream>

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

void Inventory::updateProductPrice(const std::string& name, double price) {
    for (auto& product : products) {
        if (product.getName() == name) {
            product.setPrice(price);
            return;
        }
    }
    std::cout << "Product not found!" << std::endl;
}

void Inventory::deleteProduct(const std::string& name) {
    auto it = std::remove_if(products.begin(), products.end(), [&name](const Product& product) {
        return product.getName() == name;
    });
    if (it != products.end()) {
        products.erase(it, products.end());
    } else {
        std::cout << "Product not found!" << std::endl;
    }
}

Product* Inventory::searchProduct(const std::string& name) {
    for (auto& product : products) {
        if (product.getName() == name) {
            return &product;
        }
    }
    return nullptr;
}

void Inventory::sortByName() {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getName() < b.getName();
    });
}

void Inventory::sortByPrice() {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getPrice() < b.getPrice();
    });
}

void Inventory::sortByQuantity() {
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getQuantity() < b.getQuantity();
    });
}

void Inventory::generateReport() const {
    for (const auto& product : products) {
        product.display();
    }
}

void Inventory::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.getName() << " " << product.getPrice() << " " << product.getQuantity() << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file for writing!" << std::endl;
    }
}

void Inventory::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        products.clear();
        std::string name;
        double price;
        int quantity;
        while (file >> name >> price >> quantity) {
            products.emplace_back(name, price, quantity);
        }
        file.close();
    } else {
        std::cout << "Unable to open file for reading!" << std::endl;
    }
}