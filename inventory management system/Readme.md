# Inventory Management System

This Inventory Management System is a C++ program designed to help a retail store manage its inventory. The system allows the store manager to add new products, update product quantities and prices, delete products, search for products, sort products, generate a report of all products, and save/load the inventory to/from a file.

## Features

1. **Add Product**: Allows the manager to add a new product to the inventory by specifying the product name, price, and quantity.
2. **Update Product Quantity**: Enables the manager to update the quantity of an existing product.
3. **Update Product Price**: Allows the manager to update the price of an existing product.
4. **Delete Product**: Provides the functionality to remove a product from the inventory.
5. **Search Product**: Enables the manager to search for a product by name and display its details if found.
6. **Sort Products**: Allows the manager to sort the products by name, price, or quantity.
7. **Generate Report**: Generates a report of all available products with their details.
8. **Save Inventory to File**: Saves the current state of the inventory to a file.
9. **Load Inventory from File**: Loads the inventory from a file.

## File Structure

- `product.h`: Header file defining the `Product` class.
- `product.cpp`: Implementation file for the `Product` class.
- `inventory.h`: Header file defining the `Inventory` class.
- `inventory.cpp`: Implementation file for the `Inventory` class.
- `main.cpp`: Main program file providing a user interface for the manager to interact with the inventory system.

## Classes

### Product Class

The `Product` class represents a product in the inventory. It has the following data members and member functions:

- **Data Members**:
  - `std::string name`: The name of the product.
  - `double price`: The price of the product.
  - `int quantity`: The quantity of the product in stock.

- **Member Functions**:
  - `Product(const std::string& name, double price, int quantity)`: Constructor to initialize a product.
  - `std::string getName() const`: Returns the name of the product.
  - `double getPrice() const`: Returns the price of the product.
  - `int getQuantity() const`: Returns the quantity of the product.
  - `void setPrice(double price)`: Sets the price of the product.
  - `void setQuantity(int quantity)`: Sets the quantity of the product.
  - `void display() const`: Displays the product details.

### Inventory Class

The `Inventory` class manages a collection of `Product` objects. It has the following data members and member functions:

- **Data Members**:
  - `std::vector<Product> products`: A vector of `Product` objects representing the inventory.

- **Member Functions**:
  - `void addProduct(const Product& product)`: Adds a new product to the inventory.
  - `void updateProductQuantity(const std::string& name, int quantity)`: Updates the quantity of an existing product.
  - `void updateProductPrice(const std::string& name, double price)`: Updates the price of an existing product.
  - `void deleteProduct(const std::string& name)`: Deletes a product from the inventory.
  - `Product* searchProduct(const std::string& name)`: Searches for a product by name and returns a pointer to the product if found.
  - `void sortByName()`: Sorts the products by name.
  - `void sortByPrice()`: Sorts the products by price.
  - `void sortByQuantity()`: Sorts the products by quantity.
  - `void generateReport() const`: Generates a report of all products in the inventory.
  - `void saveToFile(const std::string& filename) const`: Saves the inventory to a file.
  - `void loadFromFile(const std::string& filename)`: Loads the inventory from a file.

## Usage

1. **Compile the program**:
   ```sh
   g++ main.cpp product.cpp inventory.cpp -o inventory_management