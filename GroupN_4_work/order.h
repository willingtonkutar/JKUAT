#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include "product.h"

class Order {
private:
    std::string customerID;
    std::vector<std::pair<Product, int>> orderedProducts;

public:
    Order(std::string customerID);
    void addProduct(const Product &product, int quantity);
    bool isEmpty() const;
    void displayOrder() const;
    void saveToFile(const std::string &filename);
};

#endif // ORDER_H