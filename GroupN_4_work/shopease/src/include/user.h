#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string name;
    std::string userID;

public:
    User(std::string name, std::string userID);
    virtual void displayDetails() = 0;
    std::string getUserID() const;
};

#endif // USER_H