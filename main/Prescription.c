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

    printf("Enter patientID: \t\t");                            scanf("%d",&record.patientID);
    printf("Enter record ID: \t\t");                            scanf("%d",&record.recordID);

    printf("Enter report: \t\t\t");                               scanf(" %[^\n]",record.reports);
    printf("Enter Treatment: \t\t");                            scanf(" %[^\n]",record.prescription);
    printf("Enter Date (yyyy-MM-DD; \t");                     scanf(" %[^\n]",record.date);
    printf("Enter prescription: \t\t");                         scanf(" %[^\n]",record.prescription);

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
    int searchingRecordID;
    int found = 0;

    printf("Enter Patient ID :\t");                   scanf("%d",&searchingPatientID);
    printf("Enter Record ID :\t");                    scanf("%d",&searchingRecordID);

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
        printf("No record found for Patient ID %d and Record ID %d\n", searchingPatientID, searchingRecordID);
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