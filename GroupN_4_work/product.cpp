#include "product.h"
#include <iostream>

Product::Product(std::string name, double price, int stock) : productName(name), price(price), stock(stock) {}

std::string Product::getName() const {
    return productName;
}

double Product::getPrice() const {
    return price;
}

int Product::getStock() const {
    return stock;
}

void Product::updateStock(int newStock) {
    stock = newStock;
}

void Product::displayProduct() const {
    std::cout << "Product: " << productName << ", Price: " << price << ", Stock: " << stock << std::endl;
}