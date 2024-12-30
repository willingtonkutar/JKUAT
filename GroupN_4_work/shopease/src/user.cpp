#include "user.h"

User::User(std::string name, std::string userID) : name(name), userID(userID) {}

std::string User::getUserID() const {
    return userID;
}