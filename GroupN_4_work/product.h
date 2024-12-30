#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string productName;
    double price;
    int stock;

public:
    Product(std::string name, double price, int stock);
    std::string getName() const;
    double getPrice() const;
    int getStock() const;
    void updateStock(int newStock);
    void displayProduct() const;
};

#endif // PRODUCT_H