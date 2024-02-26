#include <stdio.h>
#include "admin.h"
#include "student.h"
#include "grading.h"
#include <string.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    adminLogin();

    struct Student new_student;
    captureStudentDetails(&new_student);

    int scores[7];
    char unit_names[7][50];
    int total_scores;
    float average;

    inputScoresAndCalculateGrades(scores, unit_names, &total_scores, &average);

    // Printing student details
                fprintf(file, "JKUAT\n\n\n\nStudent Details:\n");
    fprintf(file, "Name: %s\n", new_student.name);
    fprintf(file, "Admission No.: %d\n", new_student.admission_no);
    fprintf(file, "Course: %s\n", new_student.course);
    fprintf(file, "School: %s\n", new_student.school_name);

    // Printing scores and grades for each unit
    fprintf(file, "\nScores:\n");
    for (int i = 0; i < 7; i++) {
        fprintf(file, "Unit %s: %d\t Grade: %c\n", unit_names[i], scores[i], calculateGrade(scores[i]));
        if (scores[i] < 0) {
            fprintf(file, " - Visit the exam's office for supplementary.\n");
        } else if (scores[i] < 40) {
            fprintf(file, " - Visit the exam's office for supplementary.\n");
        } else if (scores[i] > 100) {
            fprintf(file, " - Error with input.\n");
        }
    }

    // Printing total scores, average, and final grade
    fprintf(file, "\nTotal Scores: %d\n", total_scores);
    fprintf(file, "Average Score: %.2f\n", average);
    fprintf(file, "Final Grade: %c\n", calculateGrade(average));
    fprintf(file, "Thank you for using the system\n");

    fclose(file);

    return 0;
}