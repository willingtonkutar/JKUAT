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

    // Calculate highest and lowest scores
    int highest_score = scores[0];
    int lowest_score = scores[0];
    int highest_score_unit = 0;
    int lowest_score_unit = 0;

    for (int i = 1; i < 7; i++) {
        if (scores[i] > highest_score) {
            highest_score = scores[i];
            highest_score_unit = i;
        }
        if (scores[i] < lowest_score) {
            lowest_score = scores[i];
            lowest_score_unit = i;
        }
    }

    // Printing student details
    printf("JKUAT\n\n\n");
    printf("JOMMO KENYATTA UNIVERSITY OF ARICULTURE AND TECHNOLOGY\n");
    printf("Student Details:\n");
    printf("Name: %s\n", new_student.name);
    printf("Admission No.: %d\n", new_student.admission_no);
    printf("Course: %s\n", new_student.course);
    printf("School: %s\n", new_student.school_name);
    printf("Department: %s\n", new_student.department);
    printf("Semester: %s\n", new_student.semester);
    
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

    // Printing highest and lowest scores
    printf("\nHighest Score: %d in unit %s\n", highest_score, unit_names[highest_score_unit]);
    printf("Lowest Score: %d in unit %s\n", lowest_score, unit_names[lowest_score_unit]);

    // Printing total scores, average, and final grade
    printf("\nTotal Scores: %d\n", total_scores);
    printf("Average Score: %.2f\n", average);
    printf("Final Grade: %c\n", calculateGrade(average));
    printf("Thank you for using the system\n");
    return 0;
}