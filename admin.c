#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"

// Admin password
char admin_password[] = "admin";

void adminLogin() {
    char input_password[50];
    printf("Enter admin password: ");
    scanf("%s", input_password);

    if (strcmp(input_password, admin_password) == 0) {
        printf("Login successful!\n");
        // Proceed with admin functionality
    } else {
        printf("Incorrect password. Access denied.\n");
        exit(0); // Stop the process
    }
}
