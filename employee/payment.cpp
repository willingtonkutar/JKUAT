#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip> // For table formatting
using namespace std;

// Constants
const double HOURLY_RATE = 15.0;
const double MANAGER_MONTHLY_RATE = 70000.0;
const int REGULAR_HOURS = 180; // 6 hours per day * 30 days

// Function prototypes
bool login();
void createAccount();
void enterEmployeeDetails();
void displayEmployeeDetails();
void calculateAndDisplaySalaries();
bool loadAccounts();
bool saveAccounts();
bool loadEmployees();
bool saveEmployees();

// Employee structure
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

// Global Variables
map<string, string> accounts; // A map to store username and password pairs
string loggedInUser; // Store the current logged in user
vector<Employee> employees; // Collection of employees

// Monthly rates for different positions
map<string, double> monthlyRates = {
    {"Manager", MANAGER_MONTHLY_RATE},
    {"Engineer", 50000},
    {"Technician", 30000},
    {"Clerk", 20000}
};

int main() {
    // Load accounts and employees from the files at the start of the program
    loadAccounts();
    loadEmployees();

    char mainChoice;
    do {
        cout << "\n=== Employee Management System ===\n";
        cout << "1. Login\n2. Create Account\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case '1':
                if (login()) {
                    char choice;
                    do {
                        cout << "\n--- Menu ---\n";
                        cout << "1. Enter employee details\n";
                        cout << "2. View all employee details\n";
                        cout << "3. Calculate and display salaries\n";
                        cout << "4. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case '1':
                                enterEmployeeDetails();
                                break;
                            case '2':
                                displayEmployeeDetails();
                                break;
                            case '3':
                                calculateAndDisplaySalaries();
                                break;
                            case '4':
                                cout << "Logging out...\n";
                                loggedInUser.clear(); // Clear the logged in user
                                break;
                            default:
                                cout << "Invalid choice. Please try again.\n";
                                break;
                        }
                    } while (choice != '4');
                } else {
                    cout << "Login failed!\n";
                }
                break;
            case '2':
                createAccount();
                break;
            case '3':
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (mainChoice != '3');

    // Save accounts and employees before exiting
    saveAccounts();
    saveEmployees();

    return 0;
}

// Function to create an account
void createAccount() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    if (accounts.find(username) != accounts.end()) {
        cout << "Username already exists. Please try again.\n";
        return;
    }

    cout << "Enter a new password: ";
    cin >> password;

    // Store the new account in the map
    accounts[username] = password;
    cout << "Account created successfully!\n";
}

// Login function
bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if the username exists and the password matches
    if (accounts.find(username) != accounts.end() && accounts[username] == password) {
        cout << "Login successful! Welcome, " << username << "!\n";
        loggedInUser = username;
        return true;
    }
    return false;
}

// Function to enter employee details
void enterEmployeeDetails() {
    Employee newEmployee;
    cout << "Enter employee ID (integer): ";
    cin >> newEmployee.employeeID;

    // Check for unique employee ID
    for (const auto& emp : employees) {
        if (emp.employeeID == newEmployee.employeeID) {
            cout << "Employee ID already exists. Please try again with a unique ID.\n";
            return;
        }
    }

    cout << "Enter employee name: ";
    cin.ignore(); // To ignore the newline character left by previous input
    getline(cin, newEmployee.name);

    cout << "Enter employee position (Manager, Engineer, Technician, Clerk): ";
    cin >> newEmployee.position;

    // Validate position
    if (monthlyRates.find(newEmployee.position) == monthlyRates.end()) {
        cout << "Invalid position. Please enter one of the predefined positions.\n";
        return;
    }

    cout << "Is the employee paid hourly or monthly? (Enter 'hourly' or 'monthly'): ";
    cin >> newEmployee.paymentType;

    // Validate payment type
    if (newEmployee.paymentType != "hourly" && newEmployee.paymentType != "monthly") {
        cout << "Invalid payment type. Please enter 'hourly' or 'monthly'.\n";
        return;
    }

    if (newEmployee.paymentType == "hourly") {
        cout << "Enter hours worked: ";
        cin >> newEmployee.hoursWorked;

        // Calculate overtime if hours worked exceed 180 hours per month
        if (newEmployee.hoursWorked > REGULAR_HOURS) {
            newEmployee.overtimeHours = newEmployee.hoursWorked - REGULAR_HOURS;
        } else {
            newEmployee.overtimeHours = 0; // No overtime if hours are within regular limit
        }
    } else {
        newEmployee.hoursWorked = 0; // Not used for monthly payment
        newEmployee.overtimeHours = 0; // No overtime for monthly payment
    }

    // Add the new employee to the collection
    employees.push_back(newEmployee);
    cout << "Employee added successfully!\n";
}

// Function to display all employee details in a table format
void displayEmployeeDetails() {
    if (employees.empty()) {
        cout << "No employee records to display.\n";
        return;
    }

    // Table Header
    cout << "\n---------------------------------------------------------------------------------------------\n";
    cout << "| ID    | Name               | Position    | Payment Type | Hours Worked | Overtime Hours |\n";
    cout << "---------------------------------------------------------------------------------------------\n";

    // Table Rows
    for (const auto& emp : employees) {
        cout << "| " << setw(5) << emp.employeeID << " | "
             << setw(18) << left << emp.name.substr(0, 17) << " | "
             << setw(11) << left << emp.position << " | "
             << setw(12) << left << emp.paymentType << " | ";

        if (emp.paymentType == "hourly") {
            cout << setw(12) << emp.hoursWorked << " | "
                 << setw(14) << emp.overtimeHours << " |\n";
        } else {
            cout << setw(12) << "N/A" << " | "
                 << setw(14) << "N/A" << " |\n";
        }
    }
    cout << "---------------------------------------------------------------------------------------------\n";
}

// Function to calculate and display salaries for all employees
void calculateAndDisplaySalaries() {
    if (employees.empty()) {
        cout << "No employee records to calculate salaries.\n";
        return;
    }

    // Table Header for Salaries
    cout << "\n----------------------------------------------------------------------------------------------------\n";
    cout << "| ID    | Name               | Position    | Payment Type | Hours Worked | Overtime Hours | Salary     |\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

    // Calculate and display salary for each employee
    for (const auto& emp : employees) {
        double salary = 0.0;

        if (emp.paymentType == "hourly") {
            salary = HOURLY_RATE * emp.hoursWorked;
            if (emp.overtimeHours > 0) {
                // Assuming overtime is paid at 1.5 times the hourly rate
                salary += emp.overtimeHours * HOURLY_RATE * 1.5;
            }
        } else if (emp.paymentType == "monthly") {
            // Check if the position exists in the monthlyRates map
            if (monthlyRates.find(emp.position) != monthlyRates.end()) {
                salary = monthlyRates[emp.position];
            } else {
                cout << "Position not found for employee ID " << emp.employeeID << ". Salary cannot be calculated.\n";
                continue;
            }
        }

        // Display the salary details
        cout << "| " << setw(5) << emp.employeeID << " | "
             << setw(18) << left << emp.name.substr(0, 17) << " | "
             << setw(11) << left << emp.position << " | "
             << setw(12) << left << emp.paymentType << " | ";

        if (emp.paymentType == "hourly") {
            cout << setw(12) << emp.hoursWorked << " | "
                 << setw(14) << emp.overtimeHours << " | "
                 << "$" << fixed << setprecision(2) << setw(9) << salary << " |\n";
        } else {
            cout << setw(12) << "N/A" << " | "
                 << setw(14) << "N/A" << " | "
                 << "$" << fixed << setprecision(2) << setw(9) << salary << " |\n";
        }
    }
    cout << "----------------------------------------------------------------------------------------------------\n";
}

// Function to calculate salary (Not used in the updated code, but kept for reference)
double calculateSalary(string paymentType, int hoursWorked, string position) {
    double salary = 0.0;

    if (paymentType == "hourly") {
        salary = HOURLY_RATE * hoursWorked;
    } else if (paymentType == "monthly") {
        // Check if the position exists in the monthlyRates map
        if (monthlyRates.find(position) != monthlyRates.end()) {
            salary = monthlyRates[position];
        } else {
            cout << "Position not found. Salary cannot be calculated.\n";
        }
    }

    return salary;
}

// Function to print salary (Not used in the updated code, but kept for reference)
void printSalary(double salary) {
    if (salary > 0) {
        cout << "Calculated salary: $" << fixed << setprecision(2) << salary << endl;
    } else {
        cout << "Salary calculation failed. Please check the input details.\n";
    }
}

// Function to load accounts from a file
bool loadAccounts() {
    ifstream file("accounts.txt");
    if (!file) {
        cout << "No account file found, starting fresh.\n";
        return false;
    }

    string username, password;
    while (file >> username >> password) {
        accounts[username] = password;
    }
    file.close();
    return true;
}

// Function to save accounts to a file
void saveAccounts() {
    ofstream file("accounts.txt");
    for (const auto& account : accounts) {
        file << account.first << " " << account.second << endl;
    }
    file.close();
}

// Function to load employees from a file
bool loadEmployees() {
    ifstream file("employees.txt");
    if (!file) {
        cout << "No employee file found, starting fresh.\n";
        return false;
    }

    Employee emp;
    while (file >> emp.employeeID) {
        // Read the rest of the employee details
        file.ignore(); // Ignore the newline or space after employeeID

        getline(file, emp.name, ',');
        getline(file, emp.position, ',');
        getline(file, emp.paymentType, ',');

        // Read hoursWorked and overtimeHours
        file >> emp.hoursWorked >> emp.overtimeHours;
        file.ignore(); // Ignore the newline after each employee record

        employees.push_back(emp);
    }
    file.close();
    return true;
}

// Function to save employees to a file
bool saveEmployees() {
    ofstream file("employees.txt");
    if (!file) {
        cout << "Error opening employees.txt for writing.\n";
        return false;
    }

    for (const auto& emp : employees) {
        file << emp.employeeID << "," 
             << emp.name << "," 
             << emp.position << "," 
             << emp.paymentType << "," 
             << emp.hoursWorked << "," 
             << emp.overtimeHours << "\n";
    }
    file.close();
    return true;
}