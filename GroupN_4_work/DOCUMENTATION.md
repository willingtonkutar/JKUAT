# Shopease Documentation

## 1. Overview

**Shopease** is a console-based e-commerce management system designed to streamline shopping and product management for administrators and customers. The system is implemented in C++ and features object-oriented design principles like inheritance, abstraction, and encapsulation.

### Core Functionalities:
- **Admin management of products**: Add, remove, view products.
- **Customer creation of orders**: View products, add products to order, finalize orders.
- **File-based storage**: Order data persistence.

## 2. Project Structure

The project is divided into two main directories: `build` and `src`.

### Directories:
- **build/**: Contains compiled files and build configurations.
  - **CMakeFiles/**: Directory for CMake-related files.
  - **Makefile**: Used for building the project.
  - **shopease**: The compiled executable file.
- **src/**: Contains source code and header files.
  - **include/**: Holds header files for classes and functions.

### Source Files:
- **admin.cpp**: Contains the implementation of the Admin class.
- **customer.cpp**: Contains the implementation of the Customer class.
- **main.cpp**: Entry point of the application and main CLI logic.
- **order.cpp**: Contains the implementation of the Order class.
- **product.cpp**: Contains the implementation of the Product class.
- **user.cpp**: Contains the implementation of the User base class.
- **CMakeLists.txt**: Build configuration for the project.
- **README.md**: High-level description of the project.

## 3. Class Structure

### 3.1 User Class (Base Class)
**Purpose**: Represents a user in the system.

**Attributes**:
- `string name`: Name of the user.
- `string userID`: Unique ID of the user.

**Methods**:
- `virtual void displayDetails()`: Displays user details (pure virtual).
- `string getUserID() const`: Returns the user ID.

### 3.2 Admin Class (Derived from User)
**Purpose**: Represents an administrator who manages products.

**Attributes**:
- `string password`: Password for admin authentication.

**Methods**:
- `void addProduct(vector<Product> &products, const string &name, double price, int stock)`: Adds a product.
- `void removeProduct(vector<Product> &products, const string &name)`: Removes a product.
- `bool checkPassword(const string &inputPassword) const`: Verifies admin password.
- `void displayDetails() override`: Displays admin details.

### 3.3 Customer Class (Derived from User)
**Purpose**: Represents a customer who places orders.

**Methods**:
- `void displayDetails() override`: Displays customer details.

### 3.4 Product Class
**Purpose**: Represents a product available in the system.

**Attributes**:
- `string productName`: Name of the product.
- `double price`: Price of the product.
- `int stock`: Available stock for the product.

**Methods**:
- `string getName() const`: Returns product name.
- `double getPrice() const`: Returns product price.
- `int getStock() const`: Returns available stock.
- `void updateStock(int newStock)`: Updates product stock.
- `void displayProduct() const`: Displays product details.

### 3.5 Order Class
**Purpose**: Represents a customer order.

**Attributes**:
- `string customerID`: ID of the customer who placed the order.
- `vector<pair<Product, int>> orderedProducts`: List of products and their quantities in the order.

**Methods**:
- `void addProduct(const Product &product, int quantity)`: Adds a product to the order.
- `bool isEmpty() const`: Checks if the order is empty.
- `void displayOrder() const`: Displays order details.
- `void saveToFile(const string &filename)`: Saves order to a file.

## 4. Functionality

### Admin Operations:
- Login using a UserID and password.
- Add and remove products.
- View all available products.
- Register additional admins.

### Customer Operations:
- Browse available products.
- Add products to an order.
- View their current order.
- Finalize and save the order.

### Order Management:
- Orders are linked to customer IDs.
- Orders are saved to a file (`orders.txt`).

## 5. How to Build and Run

### Building the Project
1. Ensure you have CMake installed.
2. Navigate to the project directory and run the following commands:

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

3. The executable will be created in the `build/` directory.

### Running the Project
Run the following command to start the application:

```sh
./shopease