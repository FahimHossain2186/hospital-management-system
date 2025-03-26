#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct{

    int recordID;
    int patientID;
    char reports[300];
    char treatment[300];
    char date[20];
    char prescription[300];

}MedicalRecord;

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

int generateRecordID(){

    Time time = getCurrentTime();

    int id;

    id = (time.year - 2000) * 10000 + time.month * 100 + time.day

    FILE *file = fopen();

    return 
}

void addRecord(){

    MedicalRecord record;

    FILE *file = fopen("record.csv", "a");

    if(!file){
        printf("Error opening file!\n");
        return;
    }

    printf("Enter patientID: \t");                      scanf("%d",&record.patientID);
    printf("Enter record ID: \t");                      scanf("%d",&record.recordID);

    printf("Enter report: \t\t");                       scanf(" %[^\n]",record.reports);
    printf("Enter Treatment: \t");                      scanf(" %[^\n]",record.prescription);
    printf("Enter Date (yyyy-MM-DD:\t");                scanf(" %[^\n]",record.date);
    printf("Enter prescription: \t");                   scanf(" %[^\n]",record.prescription);

    fprintf(file, "%d, %d, %s, %s, %s, %s\n", record.recordID, record.patientID, record.reports, record.treatment, record.date, record.prescription);

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

    int searchingPatientID;
    int searchingRecordID;
    int found = 0;

    printf("Enter Patient ID :\t");                     scanf("%d",&searchingPatientID);
    printf("Enter Record ID :\t");                      scanf("%d",&searchingRecordID);

    char line[200];

    while (fgets(line, sizeof(line), file)) {

        fscanf(file, "%d, %d, %s, %s, %s, %s\n", &record.patientID, &record.recordID, record.reports,record.treatment, record.date, record.prescription);

        if (record.patientID == searchingPatientID && record.recordID == searchingRecordID) {
            
            printf("\nMedical Record Found\n");
            printf("Patient ID:     %d\n", record.patientID);
            printf("Record ID:      %d\n", record.recordID);
            printf("Reports:        %s\n", record.reports);
            printf("Treatment:      %s\n", record.treatment);
            printf("Date:           %s\n", record.date);
            printf("Prescription:   %s\n", record.prescription);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo record found for Patient ID %d and Record ID %d\n", searchingPatientID, searchingRecordID);
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