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
    fprintf(file, "JOMMO KENYATTA UNIVERSITY OF AGRICULTURE AND TECHNOLOGY\n\n\n\nStudent Details:\n");
    fprintf(file, "Name: %s\n", new_student.name);
    fprintf(file, "Admission No.: %d\n", new_student.admission_no);
    fprintf(file, "Course: %s\n", new_student.course);
    fprintf(file, "School: %s\n", new_student.school_name);
    fprintf(file, "Department: %s\n", new_student.department);
    fprintf(file, "Semester: %s\n", new_student.semester);
    
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

    // Printing highest and lowest scores
    fprintf(file, "\nHighest Score: %d in unit %s\n", highest_score, unit_names[highest_score_unit]);
    fprintf(file, "Lowest Score: %d in unit %s\n", lowest_score, unit_names[lowest_score_unit]);

    // Printing total scores, average, and final grade
    fprintf(file, "\nTotal Scores: %d\n", total_scores);
    fprintf(file, "Average Score: %.2f\n", average);
    fprintf(file, "Final Grade: %c\n", calculateGrade(average));
    fprintf(file, "Thank you for using the system\n");

    fclose(file);

    return 0;
}