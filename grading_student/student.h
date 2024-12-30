#ifndef STUDENT_H
#define STUDENT_H

// Define a structure for storing student details
struct Student {
    char name[50];
    int admission_no;
    char course[50];
    char school_name[50];
    char department[50];
    char semester[50];
};

// Declare student-related functions
void captureStudentDetails(struct Student *new_student);

#endif
