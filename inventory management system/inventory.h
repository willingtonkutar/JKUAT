#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"
#include <vector>

class Inventory {
private:
    std::vector<Product> products;

public:
    void addProduct(const Product& product);
    void updateProductQuantity(const std::string& name, int quantity);
    void generateReport() const;
};

#endif // INVENTORY_H