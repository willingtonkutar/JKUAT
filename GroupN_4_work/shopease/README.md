# ShopEase

This is a simple E-Commerce System implemented in C++. The system allows admins to manage products and customers to place orders.

## Project Structure

## Files Description

- `main.cpp`: Contains the main function and the main loop of the application.
- `admin.h` and `admin.cpp`: Contains the `Admin` class which inherits from the `User` class and provides functionalities for managing products.
- `customer.h` and `customer.cpp`: Contains the `Customer` class which inherits from the `User` class.
- `product.h` and `product.cpp`: Contains the `Product` class which represents a product in the system.
- `order.h` and `order.cpp`: Contains the `Order` class which represents an order placed by a customer.
- `user.h` and `user.cpp`: Contains the `User` base class which is inherited by `Admin` and `Customer` classes.

## How to Build

1. Make sure you have `cmake` and a C++ compiler installed.
2. Create a build directory and navigate into it:
   ```sh
   mkdir build
   cd build
Run cmake to generate the build files:
make
Build the project
make
How to Run
After building the project, you can run the executable:
./shopease

**Features**
Admin Login: Admins can log in using their user ID and password.
Product Management: Admins can add, remove, and view products.
Customer Menu: Customers can view products, add products to their order, view their current order, and finalize their order.

**Future Improvements**
Add more functionalities for admins and customers.
Improve the user interface.
Add a database to store data persistently.