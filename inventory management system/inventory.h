#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<Product> products;

public:
    void addProduct(const Product& product);
    void updateProductQuantity(const std::string& name, int quantity);
    void updateProductPrice(const std::string& name, double price);
    void deleteProduct(const std::string& name);
    Product* searchProduct(const std::string& name);
    void sortByName();
    void sortByPrice();
    void sortByQuantity();
    void generateReport() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // INVENTORY_H