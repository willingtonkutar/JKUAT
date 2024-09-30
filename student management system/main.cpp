#include "student.h"
#include <iostream>
#include <vector>

void displayMenu() {
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Display All Students" << std::endl;
    std::cout << "3. Exit" << std::endl;
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
            std::cin >> name;
            std::cout << "Enter student ID: ";
            std::cin >> studentID;
            std::cout << "Enter course: ";
            std::cin >> course;
            std::cout << "Enter school: ";
            std::cin >> school;
            std::cout << "Enter department: ";
            std::cin >> department;
            std::cout << "Enter semester: ";
            std::cin >> semester;

            Student student(name, studentID, course, school, department, semester);

            std::cout << "Enter number of units: ";
            std::cin >> numUnits;

            for (int i = 0; i < numUnits; ++i) {
                std::string unitName;
                double score;

                std::cout << "Enter unit name: ";
                std::cin >> unitName;
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
            break;
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }

        // Add a blank line before displaying the menu again
        std::cout << std::endl;
    }

    return 0;    g++ main.cpp student.cpp -o student_grade_calculation
}