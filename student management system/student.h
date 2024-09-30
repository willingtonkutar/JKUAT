#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <fstream>

struct Unit {
    std::string name;
    double score;
    char grade;
    bool supplementary;
};

class Student {
private:
    std::string name;
    std::string studentID;
    std::string course;
    std::string school;
    std::string department;
    int semester;
    std::vector<Unit> units;

    char calculateGrade(double score) const;
    bool needsSupplementary(double score) const;

public:
    Student(const std::string& name, const std::string& studentID, const std::string& course, const std::string& school, const std::string& department, int semester);

    void addUnit(const std::string& unitName, double score);
    void displayReport() const;

    void saveToFile(std::ofstream& outFile) const;
    void loadFromFile(std::ifstream& inFile);
};

#endif // STUDENT_H