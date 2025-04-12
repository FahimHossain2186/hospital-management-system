#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct  //declaring structure for patient informatin
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

typedef struct{     //declaring structure for date

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



int generatepatientID(){    //function for auto generating patient id

    Time time = currentTime();
    int month = time.month;

    FILE *file = fopen("record.csv", "r");
    int count = 0;

    MedicalRecord record;


    char line[2000];
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d, %d, %49[^,], %24[^,], %49[^,], %499[^,], %14[^,], %499[^\n]",
                   &record.patientID, &record.appointmentID, record.patientName,
                   record.doctorDept, record.doctorName, record.diagnosis,
                   record.date, record.prescription);

            int mon = record.patientID / 10000; // Extract day from appointment ID
            if (mon == month)
                count++;
        }
        fclose(file);
    }

    int ID = month * 10000 + (count + 1);  // e.g., 12*10000 + 1 → 120001
    return ID;
}






int generateappointmentID(){    //function for auto generating appointment id

    Time time = currentTime();
    int day = time.day;

    FILE *file = fopen("record.csv", "r");
    int count = 0;

    MedicalRecord record;


    char line[2000];
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d, %d, %49[^,], %24[^,], %49[^,], %499[^,], %14[^,], %499[^\n]",
                   &record.patientID, &record.appointmentID, record.patientName,
                   record.doctorDept, record.doctorName, record.diagnosis,
                   record.date, record.prescription);

            int dat = record.appointmentID / 10000; // Extract day from appointment ID
            if (dat == day)
                count++;
        }
        fclose(file);
    }

    int ID = day * 10000 + (count + 1);  // e.g., 12*10000 + 1 → 120001
    return ID;
}



void addRecord(){ //function to take information of patient

    MedicalRecord record;     //setting variable for MedicalRecord function

    FILE *file = fopen("record.csv", "a");    //file opening

    if(!file){
        printf("Error opening file!\n");    //if searching for file fails
        return;
    }

    record.patientID = generatepatientID();
    printf("Generated patient ID: %d\n", record.patientID);



    record.appointmentID = generateappointmentID();    //setting auto generated appointmentID in record.appointmentID
    printf("Generated appointment ID: %d\n", record.appointmentID);   //printing the auto generated appointmentID

    printf("Enter patient name:\t");                            scanf(" %[^\n]",record.patientName);   //prompts for more inputs
    printf("Enter doctor's department:");                       scanf(" %[^\n]",record.doctorDept);
    printf("Enter doctor name:\t");                             scanf(" %[^\n]",record.doctorName);
    printf("Enter   diagnosis: \t");                            scanf(" %[^\n]",record.diagnosis);
    printf("Enter   date: \t\t");                               scanf(" %[^\n]",record.date);
    printf("Enter   prescription: \t");                         scanf(" %[^\n]",record.prescription);

    fprintf(file, "%d, %d, %s, %s, %s, %s, %s, %s\n", record.patientID, record.appointmentID, record.patientName, record.doctorDept, record.doctorName
            , record.diagnosis ,record.date ,record.prescription);   //writing inputs in file

    fclose(file);     //closing the file

    printf("\nRecord added successfully\n\n");
}

void viewMedicalRecord(){     //function to view saved information

 MedicalRecord record;       //setting variable for MedicalRecord function


FILE *file = fopen("record.csv", "r");  //file opening in read mood

    if(!file){
        printf("Error opening file!\n");        //if searching for file fails
        return;
    }

    int searchingpatientID;          //variable to take input
    int searchingappointID;
    int found = 0;

    printf("Enter patientID :\t");                          scanf("%d",&searchingpatientID);      //taking patientId and appointment id to search for information
    printf("Enter appointmentID :\t");                      scanf("%d",&searchingappointID);

    char line[2000];

    while (fgets(line, sizeof(line), file)) {         //searching for given information in lines

        sscanf(line, "%d, %d, %49[^,], %24[^,], %49[^,], %499[^,] ,%14[^,] ,%499[^\n]\n", &record.patientID, &record.appointmentID, record.patientName ,record.doctorDept, record.doctorName
               , record.diagnosis, record.date ,record.prescription);

        if (record.patientID == searchingpatientID && record.appointmentID == searchingappointID)  {      //checking if given and saved information matchs

            printf("\nMedical Record Found\n");          //printing informations after getting them
            printf("Patient ID:                 %d\n", record.patientID);
            printf("Appointment ID:             %d\n", record.appointmentID);
            printf("Patient Name:               %s\n", record.patientName);
            printf("Doctor's Department:        %s\n", record.doctorDept);
            printf("Doctor's Name:              %s\n", record.doctorName);
            printf("Diagnosis:                  %s\n", record.diagnosis);
            printf("Date(yyyy-mm-dd):          %s\n", record.date);
            printf("Prescription:              %s\n", record.prescription);


            found = 1;
            break;
        }
    }

    if (!found) {          //showing that there is no saved information
        printf("\nNo record found for Patient ID %d and Appointment ID %d\n", searchingpatientID, searchingappointID);
    }

    fclose(file);            //closing file
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

int main()
{

  prescription();
}
