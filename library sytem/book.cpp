#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <limits>  // for clearing input buffer
#include <iomanip> // for setw
#include <algorithm> // for find

using namespace std;

// Define a structure for books
struct Book {
    int id;
    string title;
    string isbn; // Add ISBN attribute
    bool isBorrowed;
    int quantity; // Add quantity attribute

    Book(int id, string title, int quantity) : id(id), title(title), isBorrowed(false), quantity(quantity) {
        isbn = generateISBN(); // Assign a random ISBN upon creation
    }

    // Function to generate a random ISBN
    string generateISBN() {
        string isbn = "978-0-";
        for (int i = 0; i < 9; ++i) {
            isbn += to_string(rand() % 10); // Generate random digits
        }
        return isbn;
    }
};

// Define a structure for users
struct User {
    string username;
    vector<int> borrowedBooks;
};

vector<string> transactions; // To track all transactions

// Function to display all available books
void displayAvailableBooks(const vector<Book>& books) {
    cout << "\nAvailable Books:\n";
    bool anyAvailable = false;
    for (const auto& book : books) {
        if (book.quantity > 0) {
            cout << "ID: " << book.id << " | Title: " << book.title << " | ISBN: " << book.isbn << " | Quantity: " << book.quantity << endl;
            anyAvailable = true;
        }
    }
    if (!anyAvailable) {
        cout << "No books are available at the moment.\n";
    }
}

// Function to borrow a book
void borrowBook(vector<Book>& books, User& user, const string& title, int quantity) {
    if (quantity > 3) {
        cout << "You can only borrow up to 3 books at a time.\n";
        return;
    }

    for (auto& book : books) {
        if (book.title == title) {
            if (book.quantity < quantity) {
                cout << "Not enough copies of '" << book.title << "' are available.\n";
            } else {
                book.quantity -= quantity;
                for (int i = 0; i < quantity; ++i) {
                    user.borrowedBooks.push_back(book.id);
                }
                transactions.push_back(user.username + " borrowed " + to_string(quantity) + " copies of book: " + book.title);
                cout << "You have successfully borrowed " << quantity << " copies of '" << book.title << "'.\n";
            }
            return;
        }
    }
    cout << "Error: Book with title '" << title << "' not found.\n";
}

// Function to return a book
void returnBook(vector<Book>& books, User& user, int id) {
    for (auto& book : books) {
        if (book.id == id) {
            if (book.isBorrowed) {
                book.isBorrowed = false;
                book.quantity++;
                auto it = find(user.borrowedBooks.begin(), user.borrowedBooks.end(), id);
                if (it != user.borrowedBooks.end()) {
                    user.borrowedBooks.erase(it);
                    transactions.push_back(user.username + " returned book: " + book.title);
                    cout << "You have successfully returned '" << book.title << "'.\n";
                }
            } else {
                cout << "Error: Book '" << book.title << "' was not borrowed.\n";
            }
            return;
        }
    }
    cout << "Error: Book with ID " << id << " not found.\n";
}

// Function to save books to a file
void saveBooksToFile(const vector<Book>& books, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& book : books) {
            outFile << book.id << "," << book.title << "," << book.isbn << "," << book.isBorrowed << "," << book.quantity << "\n";
        }
        outFile.close();
    } else {
        cout << "Error opening file for writing.\n";
    }
}

// Function to load books from a file
void loadBooksFromFile(vector<Book>& books, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            int id, quantity;
            string title, isbn;
            bool isBorrowed;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);

            id = stoi(line.substr(0, pos1));
            title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            isbn = line.substr(pos2 + 1, pos3 - pos2 - 1);
            isBorrowed = (line.substr(pos3 + 1, pos4 - pos3 - 1) == "1");
            quantity = stoi(line.substr(pos4 + 1));

            books.emplace_back(id, title, quantity);
            books.back().isbn = isbn; // Set the ISBN
            books.back().isBorrowed = isBorrowed; // Set the borrowed status
        }
        inFile.close();
    } else {
        cout << "Error opening file for reading.\n";
    }
}

// Function for user login
bool login(User& user) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Open the accounts file to check for valid credentials
    ifstream accountFile("accounts.txt");
    if (!accountFile.is_open()) {
        cout << "Error opening accounts file.\n";
        return false;
    }

    string storedUsername, storedPassword;
    while (accountFile >> storedUsername >> storedPassword) {
        // Check if stored username matches input username
        if (storedUsername == username && storedPassword == password) {
            user.username = username;
            accountFile.close();
            return true; // Valid login
        }
    }

    accountFile.close();
    cout << "Invalid login details.\n";
    return false;
}

// Function for account creation
void createAccount() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    // Append the new account details to the file
    ofstream accountFile("accounts.txt", ios::app);
    if (accountFile.is_open()) {
        accountFile << username << " " << password << "\n"; // Store on the same line separated by space
        accountFile.close();
        cout << "Account created successfully!\n";
    } else {
        cout << "Error creating account file.\n";
    }
}

// Function to add a new book
void addBook(vector<Book>& books) {
    string title;
    int quantity;
    cout << "Enter the title of the new book: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Properly clear the input buffer
    getline(cin, title);
    cout << "Enter the quantity of the new book: ";
    cin >> quantity;

    int newId = books.size() + 1; // Simple ID generation (sequential)
    books.emplace_back(newId, title, quantity); // Create a new book and add it to the vector

    transactions.push_back("Added book: " + title + " (Quantity: " + to_string(quantity) + ")");
    saveBooksToFile(books, "books.txt"); // Save updated book list to the file
    cout << "Book '" << title << "' has been added successfully!\n";
}

// Function to delete a book
void deleteBook(vector<Book>& books, int id) {
    auto it = remove_if(books.begin(), books.end(), [id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        transactions.push_back("Deleted book with ID: " + to_string(id));
        books.erase(it, books.end());
        saveBooksToFile(books, "books.txt"); // Save updated book list to the file
        cout << "Book with ID " << id << " has been deleted successfully!\n";
    } else {
        cout << "Error: Book with ID " << id << " not found.\n";
    }
}

// Function to generate a report of all transactions
void generateReport() {
    cout << "Report output is:\n";
    cout << left << setw(30) << "Transaction Details" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& transaction : transactions) {
        cout << left << setw(30) << transaction << endl;
    }
}

// Main menu
void showMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Display all available books\n";
    cout << "2. Borrow a book\n";
    cout << "3. Return a book\n";
    cout << "4. Add a new book\n"; // New option for adding a book
    cout << "5. Delete a book\n"; // New option for deleting a book
    cout << "6. Generate Report\n"; // New option for generating a report
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    vector<Book> books;
    const string filename = "books.txt"; // File to store books

    // Load existing books from the file
    loadBooksFromFile(books, filename);

    // Ask user to create an account
    cout << "Welcome to the Library Management System!\n";
    cout << "Do you want to create a new account? (yes/no): ";
    string response;
    cin >> response;

    if (response == "yes") {
        createAccount();
    }

    User currentUser;
    // User login
    if (!login(currentUser)) {
        return 0; // Exit if login fails
    }

    int choice;
    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayAvailableBooks(books);
                break;
            case 2: {
                string title;
                int quantity;
                cout << "Enter the title of the book you want to borrow: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Properly clear the input buffer
                getline(cin, title);
                cout << "Enter the quantity of books you want to borrow (max 3): ";
                cin >> quantity;
                borrowBook(books, currentUser, title, quantity);
                break;
            }
            case 3: {
                int id;
                cout << "Enter the ID of the book you want to return: ";
                cin >> id;
                returnBook(books, currentUser, id);
                break;
            }
            case 4:
                addBook(books); // Call the addBook function
                break;
            case 5: {
                int id;
                cout << "Enter the ID of the book you want to delete: ";
                cin >> id;
                deleteBook(books, id);
                break;
            }
            case 6:
                generateReport(); // Call the generateReport function
                break;
            case 7:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}