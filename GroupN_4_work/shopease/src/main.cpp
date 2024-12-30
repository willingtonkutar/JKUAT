#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Add this line to include the algorithm header
#include "include/admin.h"
#include "include/customer.h"
#include "include/product.h"
#include "include/order.h"

using namespace std;

int main() {
    vector<Product> products;
    vector<Customer> customers;
    vector<Order> orders;
    vector<Admin> admins;

    cout << "Welcome to the Shopease System!\n";
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

    while (true) {
        cout << "\n=================== E-Commerce System ===================" << endl;
        cout << "\n       1. Admin Login" << endl;
        cout << "       2. Customer Menu" << endl;
        cout << "=========================================================" << endl;
        cout << "Enter your choice (1 for Admin, 2 for Customer): ";

        int mainChoice;
        cin >> mainChoice;
        cin.ignore();

        if (mainChoice == 1) {
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
                            break;
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
            cout << "\nEnter Customer Name: ";
            string customerName, customerID;
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter Customer ID: ";
            getline(cin, customerID);

            Customer customer(customerName, customerID);
            customers.push_back(customer);

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

                    auto it = find_if(products.begin(), products.end(), [&productName](const Product &p) {
                        return p.getName() == productName;
                    });

                    if (it != products.end()) {
                        cout << "Enter quantity: ";
                        int quantity;
                        cin >> quantity;
                        cin.ignore();

                        if (quantity > 0 && quantity <= it->getStock()) {
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
                        break;
                    }
                } else if (customerChoice == 5) {
                    cout << "Returning to main menu..." << endl;
                    break;
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