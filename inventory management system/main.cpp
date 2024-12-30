#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int qty;

    bool operator==(const Product& other) const {
        return id == other.id;
    }
};

struct Transaction {
    int product_id;
    string type; // "add" or "remove"
    int qty;
    double price;
};

bool enter_password() {
    string password;
    cout << "Enter Password: ";
    cin >> password;
    return password == "1234";
}

int display_menu() {
    int choice;
    cout << "1. Add Product" << endl;
    cout << "2. Display Products" << endl;
    cout << "3. Generate Report" << endl;
    cout << "4. Products Taken Out" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void add_product(vector<Product>& products, vector<Transaction>& transactions) {
    Product p;
    cout << "Enter product ID: ";
    cin >> p.id;
    cout << "Enter product name: ";
    cin >> p.name;
    cout << "Enter product price per unit: ";
    cin >> p.price;
    cout << "Enter product quantity: ";
    cin >> p.qty;

    // Check if the product already exists
    for (auto& prod : products) {
        if (prod.id == p.id) {
            // Update the existing product
            prod.price = p.price;
            prod.qty += p.qty;
            cout << "Product updated successfully!" << endl;

            // Log the transaction
            transactions.push_back({p.id, "add", p.qty, p.price});
            return;
        }
    }

    // If the product does not exist, add it to the list
    products.push_back(p);
    cout << "Product added successfully!" << endl;

    // Log the transaction
    transactions.push_back({p.id, "add", p.qty, p.price});
}

void display_products(const vector<Product>& products) {
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (const auto& p : products) {
        cout << left << setw(10) << p.id << setw(20) << p.name << setw(10) << p.price << setw(10) << p.qty << endl;
    }
}

void generate_report(const vector<Product>& products, const vector<Transaction>& transactions) {
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }

    for (const auto& p : products) {
        cout << "Product ID: " << p.id << ", Name: " << p.name << ", Current Price per Unit: " << p.price << ", Current Quantity: " << p.qty << endl;
        cout << left << setw(10) << "Type" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        cout << "----------------------------------------" << endl;
        double total_value = 0;
        for (const auto& t : transactions) {
            if (t.product_id == p.id) {
                cout << left << setw(10) << t.type << setw(10) << t.qty << setw(10) << t.price << endl;
                if (t.type == "add") {
                    total_value += t.qty * t.price;
                } else if (t.type == "remove") {
                    total_value -= t.qty * t.price;
                }
            }
        }
        cout << "Total Value: " << total_value << endl;
        cout << "----------------------------------------" << endl;
    }
}

void remove_product(vector<Product>& products, vector<Transaction>& transactions) {
    int id;
    int remove_qty;
    cout << "Enter product ID to remove: ";
    cin >> id;
    cout << "Enter quantity to remove: ";
    cin >> remove_qty;

    for (auto& prod : products) {
        if (prod.id == id) {
            if (remove_qty > prod.qty) {
                cout << "Cannot remove more than available quantity." << endl;
                return;
            }
            prod.qty -= remove_qty;
            double removed_price = remove_qty * prod.price;
            cout << "Removed " << remove_qty << " units of " << prod.name << " costing " << removed_price << endl;

            // Log the transaction
            transactions.push_back({id, "remove", remove_qty, prod.price});

            if (prod.qty == 0) {
                products.erase(remove(products.begin(), products.end(), prod), products.end());
                cout << "Product removed from inventory as quantity is zero." << endl;
            }
            return;
        }
    }
    cout << "Product ID not found." << endl;
}

int main() {
    if (!enter_password()) {
        cout << "Incorrect password. Exiting..." << endl;
        return 1;
    }

    vector<Product> products;
    vector<Transaction> transactions;
    while (true) {
        int choice = display_menu();
        switch (choice) {
            case 1:
                add_product(products, transactions);
                break;
            case 2:
                display_products(products);
                break;
            case 3:
                generate_report(products, transactions);
                break;
            case 4:
                remove_product(products, transactions);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}