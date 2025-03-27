#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int     patientID;
    char    patientName[50];

    int     appointmentID;

    char    doctorDept[25];
    char    doctorName[50];
    char    diagnosis[500];
    char    prescription[500];
    char    date[15];

} MedicalRecord;

typedef struct{

    int year;
    int month;
    int day;

}Time;

Time currentTime(){ // Reference --> GeeksforGeeks "How can I return multiple values from a function?" {https://www.geeksforgeeks.org/how-can-i-return-multiple-values-from-a-function/}

    // Reference --> "How to get current time and date in C" by CodeVault {https://www.youtube.com/watch?v=i1MeXMciy6Q}

    time_t t = time(NULL);
    struct tm date = *localtime(&t);

    Time time;

    time.year = date.tm_year + 1900;
    time.month = date.tm_mon + 1;
    time.day = date.tm_mday;

    return time;
}

int generateappointmentID(){

    Time time = currentTime();

    int id;

    id = (time.year - 2000) * 10000 + time.month * 100 + time.day;

    FILE *file = fopen("record.csv", "a");

    return;
}

void addRecord(){

    MedicalRecord record;

    FILE *file = fopen("record.csv", "a");

    if(!file){
        printf("Error opening file!\n");
        return;
    }

    printf("Enter     patientID: \t");                          scanf("%d",&record.patientID);
    printf("Enter     appointmentID: \t");                      scanf("%d",&record.appointmentID);

    printf("Enter   patient    name: \t\t");                    scanf(" %[^\n]",record.patientName);
    printf("Enter   doctor's   department: \t");                scanf(" %[^\n]",record.doctorDept);
    printf("Enter   doctor     name:\t");                       scanf(" %[^\n]",record.doctorName);
    printf("Enter   diagnosis: \t");                            scanf(" %[^\n]",record.diagnosis);
    printf("Enter   date: \t");                                 scanf(" %[^\n]",record.date);
    printf("Enter   prescription: \t");                         scanf(" %[^\n]",record.prescription);

    fprintf(file, "%d, %d, %s, %s, %s, %s, %s, %s\n", record.patientID, record.appointmentID, record.patientName, record.doctorDept, record.doctorName
            , record.diagnosis ,record.date ,record.prescription);

    fclose(file);

    printf("\nRecord added successfully\n\n");
}

void viewMedicalRecord(){

MedicalRecord record;

FILE *file = fopen("record.csv", "r");

    if(!file){
        printf("Error opening file!\n");
        return;
    }

    int searchingpatientID;
    int searchingappointID;
    int found = 0;

    printf("Enter patientID :\t");                          scanf("%d",&searchingpatientID);
    printf("Enter appointmentID :\t");                      scanf("%d",&searchingappointID);

    char line[200];

    while (fgets(line, sizeof(line), file)) {

        fscanf(file, "%d, %d, %s, %s, %s, %s ,%s ,%s\n", &record.patientID, &record.appointmentID, record.doctorDept,record.doctorName
               , record.diagnosis, record.date ,record.prescription);

        if (record.patientID == searchingpatientID && record.appointmentID == searchingappointID) {

            printf("\nMedical Record Found\n");
            printf("Patient ID:                 %d\n", record.patientID);
            printf("Appoinment ID:              %d\n", record.appointmentID);
            printf("Doctor's Department:        %s\n", record.doctorDept);
            printf("Doctor's Name:              %s\n", record.doctorName);
            printf("Diagnosis:                  %s\n", record.diagnosis);
            printf("Date(yyyy-mm-dd):           %s\n", record.date);
            printf("Prescription:               %s\n", record.prescription);


            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo record found for Patient ID %d and Appointment ID %d\n", searchingpatientID, searchingappointID);
    }

    fclose(file);
}


int prescription() {

    int choice;

    while (1) {

        printf("1. Add Medical Record\n");
        printf("2. View Medical Record\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewMedicalRecord();
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

int main(){

    prescription();
}
