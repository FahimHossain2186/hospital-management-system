#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== STRUCT DEFINITIONS =====

typedef struct {
    char city[30];
    char area[30];
    int postalCode;
} Address;

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    Address address;
    char disease[30];
    char contact[20];
    int password;
} Patient;

typedef struct {
    int id;
    char name[50];
    char department[25];
    char title[25];
    Address address;
    char contactNo[20];
    char contactMail[50];
    int password;
} Doctor;

typedef struct {
    int id;
    char name[50];
    char role[30];
    char department[50];
    Address address;
    char contactNo[15];
    char email[50];
    int password;
} Staff;

// ===== FUNCTION DECLARATIONS =====

int login(int userType);
void logout();
void addPatient();
void viewPatient();
void viewDoctor();

// ===== LOGIN FUNCTION =====

int login(int userType) {
    int id, password;
    printf("\nEnter ID: ");
    scanf("%d", &id);
    printf("Enter Password: ");
    scanf("%d", &password);

    FILE *file;
    if (userType == 1)
        file = fopen("patients.csv", "r");
    else if (userType == 2)
        file = fopen("doctors.csv", "r");
    else
        file = fopen("staffs.csv", "r");

    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        int fileID, filePassword;
        sscanf(line, "%d,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d", &fileID, &filePassword);


        if (fileID == id && filePassword == password) {
            fclose(file);
            printf("\nLogin Successful!\n");
            return 1;
        }
    }

    fclose(file);
    printf("\nInvalid Input!\n");
    return 0;
}

// ===== LOGOUT FUNCTION =====

void logout() {
    printf("\nLogged Out Successfully!\n");
}

// ===== ADD PATIENT FUNCTION =====

void addPatient() {
    Patient patient;
    FILE *file = fopen("patients.csv", "a");

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d", &patient.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", patient.name);
    printf("Enter Age: ");
    scanf("%d", &patient.age);
    printf("Enter Gender: ");
    scanf("%s", patient.gender);
    printf("Enter City: ");
    scanf("%s", patient.address.city);
    printf("Enter Area: ");
    scanf("%s", patient.address.area);
    printf("Enter Postal Code: ");
    scanf("%d", &patient.address.postalCode);
    printf("Enter Disease: ");
    scanf("%s", patient.disease);
    printf("Enter Contact: ");
    scanf("%s", patient.contact);
    printf("Enter Password: ");
    scanf("%d", &patient.password);

    fprintf(file, "%d,%s,%d,%s,%s,%s,%d,%s,%s,%d\n",
            patient.id, patient.name, patient.age, patient.gender,
            patient.address.city, patient.address.area, patient.address.postalCode,
            patient.disease, patient.contact, patient.password);

    fclose(file);
    printf("\nPatient Added Successfully!\n");
}

// ===== VIEW PATIENT FUNCTION =====

void viewPatient() {
    FILE *file = fopen("patients.csv", "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nID | Name | Age | Gender | City | Area | PostalCode | Disease | Contact\n");
    printf("------------------------------------------------------------------------\n");

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// ===== VIEW DOCTOR FUNCTION =====

void viewDoctor() {
    FILE *file = fopen("doctors.csv", "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nID | Name | Department | Title | City | Area | PostalCode | Contact | Email\n");
    printf("--------------------------------------------------------------------------\n");

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// ===== MAIN FUNCTION =====

int main() {
    int userType;
    int loggedIn = 0;
    int choice;

    while (1) {
        printf("\n--- Welcome to Hospital Management System ---\n");
        printf("1. Patient Login\n");
        printf("2. Doctor Login\n");
        printf("3. Staff Login\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        if (userType == 4) {
            printf("Exiting system...\n");
            break;
        }

        if (userType < 1 || userType > 3) {
            printf("Invalid user type! Please try again.\n");
            continue;
        }

        loggedIn = login(userType);

        while (loggedIn) {
            if (userType == 1) { // Patient
                printf("\n--- Patient Menu ---\n");
                printf("1. View Patients \n");
                printf("2. View Doctors\n");
                printf("3. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        viewPatient();
                        break;
                    case 2:
                        viewDoctor();
                        break;
                    case 3:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            } else if (userType == 2) { // Doctor
                printf("\n--- Doctor Menu ---\n");
                printf("1. View Patients\n");
                printf("2. View Doctors\n");
                printf("3. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        viewPatient();
                        break;
                    case 2:
                        viewDoctor();
                        break;
                    case 3:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            } else if (userType == 3) { // Staff
                printf("\n--- Staff Menu ---\n");
                printf("1. Add New Patient\n");
                printf("2. View All Patients\n");
                printf("3. View All Doctors\n");
                printf("4. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        addPatient();
                        break;
                    case 2:
                        viewPatient();
                        break;
                    case 3:
                        viewDoctor();
                        break;
                    case 4:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            }
        }
    }

    return 0;
}
