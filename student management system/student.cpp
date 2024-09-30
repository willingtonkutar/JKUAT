#include "student.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Student::Student(const std::string& name, const std::string& studentID, const std::string& course, const std::string& school, const std::string& department, int semester)
    : name(name), studentID(studentID), course(course), school(school), department(department), semester(semester) {}

char Student::calculateGrade(double score) const {
    if (score >= 70) return 'A';
    if (score >= 60) return 'B';
    if (score >= 50) return 'C';
    if (score >= 40) return 'D';
    return 'F';
}

bool Student::needsSupplementary(double score) const {
    return score < 40;
}

void Student::addUnit(const std::string& unitName, double score) {
    Unit unit;
    unit.name = unitName;
    unit.score = score;
    unit.grade = calculateGrade(score);
    unit.supplementary = needsSupplementary(score);
    units.push_back(unit);
}

void Student::displayReport() const {
    std::cout << "JOMMO KENYATTA UNIVERSITY OF AGRICULTURE AND TECHNOLOGY\n\n";
    std::cout << "Student Details:\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Admission No.: " << studentID << "\n";
    std::cout << "Course: " << course << "\n";
    std::cout << "School: " << school << "\n";
    std::cout << "Department: " << department << "\n";
    std::cout << "Semester: " << semester << "\n\n";

    std::cout << "Scores:\n";
    double totalScore = 0;
    double highestScore = -1;
    double lowestScore = 101;
    std::string highestUnit, lowestUnit;

    for (const auto& unit : units) {
        std::cout << "Unit " << unit.name << ": " << unit.score << "\t Grade: " << unit.grade << "\n";
        if (unit.supplementary) {
            std::cout << " - Visit the exam's office for supplementary.\n";
        }
        totalScore += unit.score;
        if (unit.score > highestScore) {
            highestScore = unit.score;
            highestUnit = unit.name;
        }
        if (unit.score < lowestScore) {
            lowestScore = unit.score;
            lowestUnit = unit.name;
        }
    }

    double averageScore = totalScore / units.size();
    char finalGrade = calculateGrade(averageScore);

    std::cout << "\nHighest Score: " << highestScore << " in unit " << highestUnit << "\n";
    std::cout << "Lowest Score: " << lowestScore << " in unit " << lowestUnit << "\n\n";
    std::cout << "Total Scores: " << totalScore << "\n";
    std::cout << "Average Score: " << std::fixed << std::setprecision(2) << averageScore << "\n";
    std::cout << "Final Grade: " << finalGrade << "\n";
    std::cout << "Thank you for using the system\n";
}