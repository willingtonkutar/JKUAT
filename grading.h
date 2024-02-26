#ifndef GRADING_H
#define GRADING_H

// Function to calculate grade based on score
char calculateGrade(int score);

// Function to input scores and calculate grades
void inputScoresAndCalculateGrades(int scores[], char unit_names[7][50], int *total_scores, float *average);

#endif // GRADING_H