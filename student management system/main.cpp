#include "student.h"
#include <iostream>
#include <vector>
#include <fstream>

void displayMenu() {
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Display All Students" << std::endl;
    std::cout << "3. Save Students to File" << std::endl;
    std::cout << "4. Load Students from File" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

int main() {
    std::vector<Student> students;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::string studentID;
            std::string course;
            std::string school;
            std::string department;
            int semester;
            int numUnits;

            std::cout << "Enter student name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter student ID: ";
            std::getline(std::cin, studentID);
            std::cout << "Enter course: ";
            std::getline(std::cin, course);
            std::cout << "Enter school: ";
            std::getline(std::cin, school);
            std::cout << "Enter department: ";
            std::getline(std::cin, department);
            std::cout << "Enter semester: ";
            std::cin >> semester;

            Student student(name, studentID, course, school, department, semester);

            std::cout << "Enter number of units: ";
            std::cin >> numUnits;

            for (int i = 0; i < numUnits; ++i) {
                std::string unitName;
                double score;

                std::cout << "Enter unit name: ";
                std::cin.ignore();
                std::getline(std::cin, unitName);
                std::cout << "Enter score for " << unitName << ": ";
                std::cin >> score;

                student.addUnit(unitName, score);
            }

            students.push_back(student);
        } else if (choice == 2) {
            for (const auto& student : students) {
                student.displayReport();
                std::cout << std::endl; // Add a blank line between reports
            }
        } else if (choice == 3) {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::cin >> filename;
            std::ofstream outFile(filename);
            if (outFile.is_open()) {
                for (const auto& student : students) {
                    student.saveToFile(outFile);
                }
                outFile.close();
                std::cout << "Students saved to file successfully.\n";
            } else {
                std::cout << "Unable to open file for writing.\n";
            }
        } else if (choice == 4) {
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::cin >> filename;
            std::ifstream inFile(filename);
            if (inFile.is_open()) {
                students.clear();
                while (!inFile.eof()) {
                    Student student("", "", "", "", "", 0);
                    student.loadFromFile(inFile);
                    if (inFile) { // Check if the student was loaded successfully
                        students.push_back(student);
                    }
                }
                inFile.close();
                std::cout << "Students loaded from file successfully.\n";
            } else {
                std::cout << "Unable to open file for reading.\n";
            }
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }

        // Add a blank line before displaying the menu again
        std::cout << std::endl;
    }

    return 0;
}