#include <stdio.h>
#include <string.h>
#include "student.h"

void captureStudentDetails(struct Student *new_student) {
    printf("Enter student name: ");
    scanf("%s", new_student->name);
    printf("Enter admission number: ");
    scanf("%d", &new_student->admission_no);
    printf("Enter course: ");
    scanf("%s", new_student->course);
    printf("Enter school name: ");
    scanf("%s", new_student->school_name);
}
