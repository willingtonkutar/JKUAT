#include <stdio.h>
#include "admin.h"
#include "student.h"
#include "grading.h"

int main() {
    adminLogin();

    struct Student new_student;
    captureStudentDetails(&new_student);

    int scores[7];
    char unit_names[7][50];
    int total_scores;
    float average;

    inputScoresAndCalculateGrades(scores, unit_names, &total_scores, &average);

    // Printing student details
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Student Details:\n");
    printf("Name: %s\n", new_student.name);
    printf("Admission No.: %d\n", new_student.admission_no);
    printf("Course: %s\n", new_student.course);
    printf("School: %s\n", new_student.school_name);

    // Printing scores and grades for each unit
    printf("\nScores:\n");
    for (int i = 0; i < 7; i++) {
        printf("Unit %s: %d\t Grade: %c\n", unit_names[i], scores[i], calculateGrade(scores[i]));
        if (scores[i] < 0) {
            printf(" - Visit the exam's office for supplementary.\n");
        } else if (scores[i] < 40) {
            printf(" - Visit the exam's office for supplementary.\n");
        } else if (scores[i] > 100) {
            printf(" - Error with input.\n");
        }
    }

    // Printing total scores, average, and final grade
    printf("\nTotal Scores: %d\n", total_scores);
    printf("Average Score: %.2f\n", average);
    printf("Final Grade: %c\n", calculateGrade(average));
    printf("Thank you for using the system\n");
    return 0;
}