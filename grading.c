#include <stdio.h>
#include "grading.h"

// Function to calculate grade based on score
char calculateGrade(int score) {
    char grade;
    if (score >= 70) {
        grade = 'A';
    } else if (score >= 60) {
        grade = 'B';
    } else if (score >= 50) {
        grade = 'C';
    } else if (score >= 40) {
        grade = 'D';
    } else {
        grade = 'F'; // Fail
    }
    return grade;
}

void inputScoresAndCalculateGrades(int scores[], char unit_names[7][50], int *total_scores, float *average) {
    // Input scores for each unit
    *total_scores = 0;
    for (int i = 0; i < 7; i++) {
        printf("Enter name for unit %d: ", i+1);
        scanf("%s", unit_names[i]);
        printf("Enter score for %s: ", unit_names[i]);
        scanf("%d", &scores[i]);

        if (scores[i] == 0) {
            printf("Visit the school exam's office for supplementary.\n");
        }

        if (scores[i] > 100) {
            printf("Score above the limit. Treating as 0 for average calculation.\n");
            scores[i] = 0;
        }

        // Calculate grade for the unit
        char grade = calculateGrade(scores[i]);
        printf("Grade for %s is %c\n", unit_names[i], grade);

        *total_scores += scores[i];
    }

    // Calculate average
    *average = (float)(*total_scores) / 7.0;
}