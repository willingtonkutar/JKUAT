#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"

class Customer : public User {
public:
    Customer(std::string name, std::string userID);
    void displayDetails() override;
};

#endif // CUSTOMER_H