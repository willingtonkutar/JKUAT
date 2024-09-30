# Student Grade Calculation

This Student Grade Calculation program is designed to help a university calculate the final grades of students in a course. Each student has a name, student ID, course, school, department, semester, and marks for multiple units. The final grade is calculated based on the scores of these units.

## Features

1. **Add Student**: Allows the user to add a new student with their details and unit scores.
2. **Display All Students**: Displays a detailed report for each student, including their scores, grades, highest and lowest scores, total scores, average score, and final grade.
3. **Save Students to File**: Saves the current list of students to a file.
4. **Load Students from File**: Loads a list of students from a file.
5. **Exit**: Exits the program.

## File Structure

- `student.h`: Header file defining the `Student` class and `Unit` struct.
- `student.cpp`: Implementation file for the `Student` class.
- `main.cpp`: Main program file providing a user interface for the user to interact with the student grade calculation system.

## Classes

### Unit Struct

The `Unit` struct represents a unit in the course. It has the following data members:

- `std::string name`: The name of the unit.
- `double score`: The score obtained in the unit.
- `char grade`: The grade obtained in the unit.
- `bool supplementary`: Indicates if the student needs to visit the exam's office for supplementary.

### Student Class

The `Student` class represents a student in the course. It has the following data members and member functions:

- **Data Members**:
  - `std::string name`: The name of the student.
  - `std::string studentID`: The student ID.
  - `std::string course`: The course the student is enrolled in.
  - `std::string school`: The school the student belongs to.
  - `std::string department`: The department the student belongs to.
  - `int semester`: The current semester of the student.
  - `std::vector<Unit> units`: A vector of `Unit` objects representing the units the student is enrolled in.

- **Member Functions**:
  - `Student(const std::string& name, const std::string& studentID, const std::string& course, const std::string& school, const std::string& department, int semester)`: Constructor to initialize a student.
  - `void addUnit(const std::string& unitName, double score)`: Adds a unit and its score to the student's record.
  - `void displayReport() const`: Displays a detailed report of the student's scores, grades, and other details.
  - `void saveToFile(std::ofstream& outFile) const`: Saves the student's data to a file.
  - `void loadFromFile(std::ifstream& inFile)`: Loads the student's data from a file.

## Usage

1. **Compile the program**:
   ```sh
   g++ main.cpp student.cpp -o student_grade_calculation