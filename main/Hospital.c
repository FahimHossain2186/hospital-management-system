#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int login(int userType);
void logout();
void addPatient();
void viewPatient();
void viewDoctor();
//void viewMedicalRecord();
//void viewDispensary();
//void bookAppointment();
//void viewAppointment();
//void addRecord();
//void updateDispensary();

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

void logout() {
    printf("\nLogged Out Successfully!\n");
}

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

void viewPatient() {
    FILE *file = fopen("patients.csv", "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void viewDoctor() {
    FILE *file = fopen("doctors.csv", "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main() {
    int userType;
    int loggedIn = 0;
    int choice;

    while (1) {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Patient Login\n");
        printf("2. Doctor Login\n");
        printf("3. Staff Login\n");
        printf("4. Hospital Admin Login\n");
        printf("5. Hospital Management\n");
        printf("6. Pharmacy\n");

        printf("Enter your choice: ");
        scanf("%d", &userType);

        if (userType < 1 || userType > 6) {
            printf("Invalid Input.\n");
            continue;
        }

        loggedIn = login(userType);

        while (loggedIn) {
            if (userType == 1) {
                printf("1. View Patients \n");
                printf("2. View Doctors\n");
                printf("3. viewMedicalRecord\n");
                printf("4. viewDispensary\n");
                printf("5. bookAppointment\n");
                printf("6. viewAppointment\n");
                printf("7. Logout\n");
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
                        //viewMedicalRecord();
                        break;
                    case 4:
                        //viewDispensary();
                        break;
                    case 5:
                        //bookAppointment();
                        break;
                    case 6:
                        //viewAppointment();
                        break;
                    case 7:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid Input.\n");
                }
            } else if (userType == 2) {
                printf("1. View Patients\n");
                printf("2. View Doctors\n");
                printf("3. viewMedicalRecord\n");
                printf("4. viewDispensary\n");
                printf("5. bookAppointment\n");
                printf("6. viewAppointment\n");
                printf("7. Logout\n");
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
                        //viewMedicalRecord();
                        break;
                    case 4:
                        //viewDispensary();
                        break;
                    case 5:
                        //bookAppointment();
                        break;
                    case 6:
                        //viewAppointment();
                        break;
                    case 7:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid Input.\n");
                }
            } else if (userType == 3) {
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
                        printf("Invalid Input.\n");
                }
            } else if (userType == 4) {
                printf("1. View Patients\n");
                printf("2. View Doctors\n");
                printf("3. viewMedicalRecord\n");
                printf("4. viewDispensary\n");
                printf("5. viewAppointment\n");
                printf("6. addRecord\n");
                printf("7. Logout\n");
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
                        //viewMedicalRecord();
                        break;
                    case 4:
                        //viewDispensary();
                        break;
                    case 5:
                        //viewAppointment();
                        break;
                    case 6:
                        //addRecord();
                        break;
                    case 7:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid Input.\n");
                }
            }else if (userType == 5) {
                printf("1. View Patients\n");
                printf("2. View Doctors\n");
                printf("3. viewMedicalRecord\n");
                printf("4. viewDispensary\n");
                printf("5. viewAppointment\n");
                printf("6. addPatient\n");
                printf("7. addRecord\n");
                printf("8. Logout\n");
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
                        //viewMedicalRecord();
                        break;
                    case 4:
                        //viewDispensary();
                        break;
                    case 5:
                        //viewAppointment();
                        break;
                    case 6:
                        //addPatient();
                        break;
                    case 7:
                        //addRecord();
                    case 8:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid Input.\n");
                }
            }else if (userType == 6) {
                printf("1. viewDispensary\n");
                printf("2. updateDispensary\n");
                printf("3. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        //viewDispensary();
                        break;
                    case 2:
                        //updateDispensary();
                        break;
                    case 3:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid Input.\n");
                }
            }
        }
    }

    return 0;
}
