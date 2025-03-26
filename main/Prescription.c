#include<stdio.h>
#include<string.h>

typedef struct{

    int recordID;
    int patientID;
    char reports[300];
    char treatment[300];
    char date[20];
    char prescription[300];

}MedicalRecord;

void addRecord(){

    MedicalRecord record;

    FILE *file = fopen("record.csv", "a");

    if(!file){
        printf("Error opening file!\n");
        return;
    }

    printf("Enter patientID: ");                            scanf("%d",&record.patientID);
    printf("Enter record ID: ");                            scanf("%d",&record.recordID);

    printf("Enter report: ");                               scanf(" %[^\n]",record.reports);
    printf("Enter Treatment: ");                            scanf(" %[^\n]",record.prescription);
    printf("Enter Date (yyyy-MM-DD; ");                     scanf(" %[^\n]",record.date);
    printf("Enter prescription: ");                         scanf(" %[^\n]",record.prescription);

    fprintf(file, "%d, %d, %s, %s, %s, %s\n", record.recordID, record.patientID, record.reports, record.treatment, record.date, record.prescription);

    fclose(file);
    printf("Record added successfully");
}
void viewMedicalRecord(){

MedicalRecord record;

FILE *file = fopen("record.csv", "r");

    if(!file){
        printf("Error opening file!\n");
        return;
    }

     int searchingPatientID;
     int searchingrecordID;
     int found = 0;

    printf("Enter patientID: ");                    scanf("%d",&searchingPatientID);
    printf("Enter record ID: ");                    scanf("%d",&searchingrecordID);

    while (fscanf(file, "%d, %d, %s, %s, %s, %s\n", &record.patientID, &record.recordID, record.reports,record.treatment, record.date, record.prescription) != EOF)

    if (record.patientID == searchingPatientID && record.recordID == searchingrecordID) {
        printf("\nMedical Record Found\n");

        printf("Patient ID: %d\n", record.patientID);

        printf("Record ID: %d\n", record.recordID);

        printf("Reports: %s\n", record.reports);

        printf("Treatment: %s\n", record.treatment);

        printf("Date: %s\n", record.date);

        printf("Prescription: %s\n", record.prescription);
        found = 1;
        break;
    }

    if (!found) {
        printf("No record found for Patient ID %d and Record ID %d\n", searchingPatientID, searchingrecordID);
    }

    fclose(file);
}


int main() {

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
