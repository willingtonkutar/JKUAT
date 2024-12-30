#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

// Base Class: User
class User {
protected:
    string name;
    string userID;

public:
    User(string name, string userID) : name(name), userID(userID) {}
    virtual void displayDetails() = 0; // Pure virtual function for abstraction
    string getUserID() const { return userID; }
};

// Derived Class: Admin
class Admin : public User {
private:
    string password;  // Store password for admin

public:
    Admin(string name, string userID, string password) : User(name, userID), password(password) {}

    void displayDetails() override {
        cout << "Admin Name: " << name << ", UserID: " << userID << endl;
    }

    // Add product to the product list
    void addProduct(vector<class Product> &products, const string &name, double price, int stock);

    // Remove product from the product list
    void removeProduct(vector<class Product> &products, const string &name);

    // Check admin login password
    bool checkPassword(const string &inputPassword) const {
        return inputPassword == password;
    }
};

// Derived Class: Customer
class Customer : public User {
public:
    Customer(string name, string userID) : User(name, userID) {}

    void displayDetails() override {
        cout << "Customer Name: " << name << ", UserID: " << userID << endl;
    }
};

// Product Class
class Product {
private:
    string productName;
    double price;
    int stock;

public:
    Product(string name, double price, int stock) : productName(name), price(price), stock(stock) {}

    string getName() const { return productName; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void updateStock(int newStock) { stock = newStock; }
    void displayProduct() const {
        cout << "Product: " << productName << ", Price: " << price << ", Stock: " << stock << endl;
    }
};

// Order Class
class Order {
private:
    string customerID;
    vector<pair<Product, int>> orderedProducts; // Store product and quantity

public:
    Order(string customerID) : customerID(customerID) {}

    void addProduct(const Product &product, int quantity) {
        orderedProducts.push_back(make_pair(product, quantity));
    }

    bool isEmpty() const {
        return orderedProducts.empty();
    }

    void displayOrder() const {
        cout << "Order for Customer ID: " << customerID << endl;
        for (const auto &entry : orderedProducts) {
            cout << "Product: " << entry.first.getName() << ", Price: " << entry.first.getPrice() << ", Quantity: " << entry.second << endl;
        }
    }

    void saveToFile(const string &filename) {
        ofstream outFile(filename, ios::app);
        if (!outFile) {
            throw runtime_error("Error opening file for writing.");
        }

        outFile << "Customer ID: " << customerID << endl;
        for (const auto &entry : orderedProducts) {
            outFile << entry.first.getName() << ", " << entry.first.getPrice() << ", " << entry.second << endl;
        }
        outFile.close();
    }
};

// Implement Admin Methods
void Admin::addProduct(vector<Product> &products, const string &name, double price, int stock) {
    products.emplace_back(name, price, stock);
    cout << "Product added successfully!" << endl;
}

void Admin::removeProduct(vector<Product> &products, const string &name) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getName() == name) {
            products.erase(it);
            cout << "Product removed successfully!" << endl;
            return;
        }
    }
    cout << "Product not found!" << endl;
}

// Main Function to Demonstrate CLI
int main() {
    // Product List, Customer List, and Orders List
    vector<Product> products;
    vector<Customer> customers;
    vector<Order> orders;
    vector<Admin> admins;

    // Register the first admin
    cout << "Welcome to the E-Commerce System!\n";
    cout << "Please register the first admin to proceed." << endl;
    string adminName, adminUserID, adminPassword;

    cout << "Enter Admin Name: ";
    getline(cin, adminName);
    cout << "Enter Admin UserID: ";
    getline(cin, adminUserID);
    cout << "Enter Admin Password: ";
    getline(cin, adminPassword);

    admins.push_back(Admin(adminName, adminUserID, adminPassword));
    cout << "Admin registered successfully!\n";

    // Main Menu Options
    while (true) {
        cout << "\n=================== E-Commerce System ===================" << endl;
        cout << "\n       1. Admin Login" << endl;
        cout << "       2. Customer Menu" << endl;
        cout << "=========================================================" << endl;
        cout << "Enter your choice (1 for Admin, 2 for Customer): ";

        int mainChoice;
        cin >> mainChoice;
        cin.ignore(); // Clear the input buffer

        if (mainChoice == 1) {
            // Admin Login
            string adminName, adminPassword;
            cout << "\nEnter Admin UserID: ";
            getline(cin, adminName);
            cout << "Enter Admin Password: ";
            getline(cin, adminPassword);

            bool adminFound = false;
            for (auto &admin : admins) {
                if (adminName == admin.getUserID() && admin.checkPassword(adminPassword)) {
                    adminFound = true;
                    cout << "\nLogin successful!" << endl;
                    // Admin menu
                    while (true) {
                        cout << "\nAdmin Menu:" << endl;
                        cout << "1. Add Product" << endl;
                        cout << "2. Remove Product" << endl;
                        cout << "3. View Products" << endl;
                        cout << "4. Register New Admin" << endl;
                        cout << "5. Return to Main Menu" << endl;
                        cout << "Enter your choice: ";
                        int adminChoice;
                        cin >> adminChoice;
                        cin.ignore();

                        if (adminChoice == 1) {
                            string name;
                            double price;
                            int stock;
                            cout << "Enter product name: ";
                            getline(cin, name);
                            cout << "Enter price: ";
                            cin >> price;
                            cout << "Enter stock: ";
                            cin >> stock;
                            cin.ignore();
                            admin.addProduct(products, name, price, stock);
                        } else if (adminChoice == 2) {
                            string name;
                            cout << "Enter product name to remove: ";
                            getline(cin, name);
                            admin.removeProduct(products, name);
                        } else if (adminChoice == 3) {
                            cout << "\nAvailable Products:" << endl;
                            for (const auto &product : products) {
                                product.displayProduct();
                            }
                        } else if (adminChoice == 4) {
                            string newName, newUserID, newPassword;
                            cout << "Enter new admin name: ";
                            getline(cin, newName);
                            cout << "Enter new admin UserID: ";
                            getline(cin, newUserID);
                            cout << "Enter new admin password: ";
                            getline(cin, newPassword);
                            admins.push_back(Admin(newName, newUserID, newPassword));
                            cout << "New Admin added successfully!" << endl;
                        } else if (adminChoice == 5) {
                            break; // Return to main menu
                        } else {
                            cout << "Invalid choice!" << endl;
                        }
                    }
                    break;
                }
            }
            if (!adminFound) {
                cout << "Invalid admin details. Access Denied!" << endl;
            }
        } else if (mainChoice == 2) {
            // Customer Menu
            cout << "\nEnter Customer Name: ";
            string customerName, customerID;
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter Customer ID: ";
            getline(cin, customerID);

            Customer customer(customerName, customerID);
            customers.push_back(customer);

            // Create a new order for this customer
            Order customerOrder(customerID);

            while (true) {
                cout << "\nCustomer Menu:" << endl;
                cout << "1. View Products" << endl;
                cout << "2. Add Product to Order" << endl;
                cout << "3. View Current Order" << endl;
                cout << "4. Finalize and Save Order" << endl;
                cout << "5. Return to Main Menu" << endl;
                cout << "Enter your choice: ";

                int customerChoice;
                cin >> customerChoice;
                cin.ignore();

                if (customerChoice == 1) {
                    cout << "\nAvailable Products:" << endl;
                    if (products.empty()) {
                        cout << "No products available." << endl;
                    } else {
                        for (const auto &product : products) {
                            product.displayProduct();
                        }
                    }
                } else if (customerChoice == 2) {
                    if (products.empty()) {
                        cout << "No products available to order." << endl;
                        continue;
                    }

                    cout << "Enter the product name to add to the order: ";
                    string productName;
                    getline(cin, productName);

                    // Find the product in the list
                    auto it = find_if(products.begin(), products.end(), [&productName](const Product &p) {
                        return p.getName() == productName;
                    });

                    if (it != products.end()) {
                        cout << "Enter quantity: ";
                        int quantity;
                        cin >> quantity;
                        cin.ignore();

                        if (quantity > 0 && quantity <= it->getStock()) {
                            // Add the product to the order and deduct stock
                            customerOrder.addProduct(*it, quantity);
                            it->updateStock(it->getStock() - quantity);
                            cout << "Product added to order successfully!" << endl;
                        } else {
                            cout << "Insufficient stock or invalid quantity." << endl;
                        }
                    } else {
                        cout << "Product not found!" << endl;
                    }
                } else if (customerChoice == 3) {
                    cout << "\nCurrent Order Details:" << endl;
                    customerOrder.displayOrder();
                } else if (customerChoice == 4) {
                    if (customerOrder.isEmpty()) {
                        cout << "Your order is empty. Add products before finalizing." << endl;
                    } else {
                        cout << "Finalizing order..." << endl;
                        customerOrder.saveToFile("orders.txt");
                        cout << "Order saved successfully!" << endl;
                        break; // Exit the customer menu
                    }
                } else if (customerChoice == 5) {
                    cout << "Returning to main menu..." << endl;
                    break; // Return to main menu
                } else {
                    cout << "Invalid choice!" << endl;
                }
            }
        } else {
            cout << "Invalid choice! Please select again." << endl;
        }
    }

    return 0;
}
