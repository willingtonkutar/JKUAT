cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ShopEase)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(src/include)

# Add the executable
add_executable(shopease
    src/main.cpp
    src/admin.cpp
    src/customer.cpp
    src/product.cpp
    src/order.cpp
    src/user.cpp
)