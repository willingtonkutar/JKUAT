# Employee Management System

## Overview

This is a simple Employee Management System written in C++. It allows users to manage employee information, including logging in, creating accounts, entering employee details, viewing employee details, and calculating monthly salaries for different positions.

## Features

- **Login**: Allows users to log in with a username and password.
- **Create Account**: Allows new users to create an account.
- **Employee Management**: Stores and manages employee information, including hours worked and overtime hours.
- **Salary Calculation**: Calculates monthly salaries for different positions.

## Code Explanation

### Constants

- `HOURLY_RATE`: The hourly rate for employees paid hourly.
- `MANAGER_MONTHLY_RATE`: The monthly salary for managers.
- `REGULAR_HOURS`: The regular hours worked per month (6 hours per day * 30 days).

### Global Variables

- `map<string, string> accounts`: A map to store username and password pairs.
- `string loggedInUser`: Stores the current logged-in user.
- `vector<Employee> employees`: A collection of employees.
- `map<string, double> monthlyRates`: Stores the monthly salary rates for different positions.

### Employee Structure

The `Employee` structure stores information about an employee, including their name, position, employee ID, payment type, hours worked, and overtime hours.

```cpp
struct Employee {
    string name;
    string position;
    int employeeID;
    string paymentType; // "hourly" or "monthly"
    int hoursWorked;
    int overtimeHours;  // Store overtime hours

    // Constructor for ease of creation
    Employee() : employeeID(0), hoursWorked(0), overtimeHours(0) {}
};