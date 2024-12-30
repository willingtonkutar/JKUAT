#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include <string>
#include "user.h"
#include "product.h"

class Admin : public User {
private:
    std::string password;

public:
    Admin(std::string name, std::string userID, std::string password);
    void displayDetails() override;
    void addProduct(std::vector<Product> &products, const std::string &name, double price, int stock);
    void removeProduct(std::vector<Product> &products, const std::string &name);
    bool checkPassword(const std::string &inputPassword) const;
};

#endif // ADMIN_H