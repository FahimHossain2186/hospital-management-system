#include<stdio.h>
#include<string.h>


typedef struct{
    int recordID;
    int patientID;
    char reports[300];
    char treatment[300];
    char prescription[300];
    char date[20];
}MedicalRecord;

void addRecord(){
    MedicalRecord record;
    FILE *file = fopen("record.csv", "a");
    if(!file){
        printf("Error opening file!\n");
        return;
    }
    printf("Enter patientID: ");
   scanf("%d",&record.patientID);
   printf("Enter record ID: ");
   scanf("%d",&record.recordID);
   getchar();
   printf("Enter report: ");
   scanf("%[^\n]",record.reports);
   getchar();
   printf("Enter Treatment: ");
   scanf("%[^\n]",&record.prescription);
   getchar();
   printf("Enter Date (yyyy-MM-DD; ");
   scanf("%[^\n]",&record.date);
   getchar();
   printf("Enter prescription: ");
   scanf("%[^\n]",&record.patientID);
   fprintf(file, "%d,%d,%s,%s,%s,%s\n", record.recordID, record.patientID, record.reports, record.treatment, record.prescription, record.date);
   fclose(file);
}
void main()
{
    addRecord();
}
