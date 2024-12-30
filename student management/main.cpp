#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <unordered_map>

using namespace std;

class Student {
    string name;
    string studentID;
    vector<int> assignments;
    vector<int> exams;
    double finalGrade;

public:
    Student() : assignments(3), exams(2), finalGrade(0.0) {}

    void inputStudentData() {
        cout << "Enter student's name: ";
        cin >> name;
        cout << "Enter student ID: ";
        cin >> studentID;
        cout << "Enter marks for CAT 1: ";
        cin >> assignments[0];
        cout << "Enter marks for CAT 2: ";
        cin >> assignments[1];
        cout << "Enter marks for CAT 3: ";
        cin >> assignments[2];
        cout << "Enter marks for Exam 1: ";
        cin >> exams[0];
        cout << "Enter marks for Exam 2: ";
        cin >> exams[1];
        calculateFinalGrade();
    }

    void calculateFinalGrade() {
        double assignmentAvg = accumulate(assignments.begin(), assignments.end(), 0.0) / assignments.size();
        double examAvg = accumulate(exams.begin(), exams.end(), 0.0) / exams.size();
        finalGrade = (assignmentAvg * 0.4) + (examAvg * 0.6);
    }

    void displayStudentData() const {
        cout << left << setw(15) << name << setw(10) << studentID;
        for (const int &mark : assignments) {
            cout << setw(10) << mark;
        }
        for (const int &mark : exams) {
            cout << setw(10) << mark;
        }
        cout << setw(10) << finalGrade << endl;
    }

    void displayIndividualMarks() const {
        cout << left << setw(15) << "Name" << setw(10) << "ID" 
             << setw(10) << "CAT 1" << setw(10) << "CAT 2" << setw(10) << "CAT 3"
             << setw(10) << "Exam 1" << setw(10) << "Exam 2" << setw(10) << "Final Grade" << endl;
        cout << string(85, '-') << endl;
        displayStudentData();
    }

    string getName() const {
        return name;
    }

    string getStudentID() const {
        return studentID;
    }

    void saveToFile(ofstream& outFile) const {
        outFile << name << " " << studentID << " ";
        for (const int &mark : assignments) {
            outFile << mark << " ";
        }
        for (const int &mark : exams) {
            outFile << mark << " ";
        }
        outFile << finalGrade << endl;
    }

    void loadFromFile(ifstream& inFile) {
        inFile >> name >> studentID;
        for (int &mark : assignments) {
            inFile >> mark;
        }
        for (int &mark : exams) {
            inFile >> mark;
        }
        inFile >> finalGrade;
    }

    static void displayHeader() {
        cout << left << setw(15) << "Name" << setw(10) << "ID" 
             << setw(10) << "CAT 1" << setw(10) << "CAT 2" << setw(10) << "CAT 3"
             << setw(10) << "Exam 1" << setw(10) << "Exam 2" << setw(10) << "Final Grade" << endl;
        cout << string(85, '-') << endl;
    }
};

struct User {
    string username;
    string password;

    void saveToFile(ofstream& outFile) const {
        outFile << username << " " << password << endl;
    }

    void loadFromFile(ifstream& inFile) {
        inFile >> username >> password;
    }
};

void log_message(const string& message) {
    ofstream log_file("log.txt", ios_base::app);
    log_file << message << endl;
}

bool login(vector<User>& users) {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            log_message("User " + username + " logged in.");
            return true;
        }
    }
    log_message("Failed login attempt for user " + username);
    return false;
}

void register_user(vector<User>& users) {
    string username, password;
    cout << "Enter new Username: ";
    cin >> username;
    cout << "Enter new Password: ";
    cin >> password;

    users.push_back({username, password});
    log_message("New user registered: " + username);
    cout << "Registration successful. Please login.\n" << endl;
}

void saveUsersToFile(const vector<User>& users) {
    ofstream outFile("users.txt");
    for (const auto& user : users) {
        user.saveToFile(outFile);
    }
}

void loadUsersFromFile(vector<User>& users) {
    ifstream inFile("users.txt");
    while (inFile) {
        User user;
        user.loadFromFile(inFile);
        if (inFile) {
            users.push_back(user);
        }
    }
}

int display_menu() {
    int choice;
    cout << "1. Add Student" << endl;
    cout << "2. Display Student Marks" << endl;
    cout << "3. View Individual Student Marks" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void saveStudentsToFile(const unordered_map<string, Student>& students) {
    ofstream outFile("students.txt");
    for (const auto& pair : students) {
        pair.second.saveToFile(outFile);
    }
}

void loadStudentsFromFile(unordered_map<string, Student>& students) {
    ifstream inFile("students.txt");
    while (inFile) {
        Student student;
        student.loadFromFile(inFile);
        if (inFile) {
            students[student.getName()] = student;
        }
    }
}

int main() {
    vector<User> users;
    loadUsersFromFile(users);

    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        if (!login(users)) {
            cout << "Incorrect username or password. Exiting..." << endl;
            return 1;
        }
    } else if (choice == 2) {
        register_user(users);
        saveUsersToFile(users);
        if (!login(users)) {
            cout << "Incorrect username or password. Exiting..." << endl;
            return 1;
        }
    } else {
        cout << "Invalid choice. Exiting..." << endl;
        return 1;
    }

    unordered_map<string, Student> students;
    loadStudentsFromFile(students);

    while (true) {
        int choice = display_menu();
        switch (choice) {
            case 1: {
                Student student;
                student.inputStudentData();
                students[student.getName()] = student;
                saveStudentsToFile(students);
                break;
            }
            case 2:
                if (!students.empty()) {
                    Student::displayHeader();
                    for (const auto& pair : students) {
                        pair.second.displayStudentData();
                    }
                } else {
                    cout << "No students available." << endl;
                }
                break;
            case 3: {
                string studentName;
                cout << "Enter student name: ";
                cin >> studentName;
                if (students.find(studentName) != students.end()) {
                    students[studentName].displayIndividualMarks();
                } else {
                    cout << "Student name not found." << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                log_message("Exited the application.");
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}