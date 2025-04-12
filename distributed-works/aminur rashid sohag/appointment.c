#include<stdio.h>
#include<string.h>
#include <time.h>

typedef struct
{
    int     appointmentID;
    int     patientID;

    char    date[15];
    char    patientName[50];

    char    doctorDept[25];
    char    doctorName[50];

} Appointment;

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

    FILE *file = fopen("appointments.csv", "r");
    int count = 0;

    Appointment appoint;


    char line[2000];
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d, %d, %49[^,], %24[^,], %49[^,], %14[^,^\n]",
                   &appoint.patientID, &appoint.appointmentID, appoint.patientName,
                   appoint.doctorDept, appoint.doctorName, appoint.date);

            int mon = appoint.patientID / 10000; // Extract day from appointment ID
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

    FILE *file = fopen("appointments.csv", "r");
    int count = 0;

    Appointment appoint;


    char line[2000];
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d, %d, %49[^,], %24[^,], %49[^,], %14[^,^\n]",
                   &appoint.patientID, &appoint.appointmentID, appoint.patientName,
                   appoint.doctorDept, appoint.doctorName, appoint.date);


            int dat = appoint.appointmentID / 10000; // Extract day from appointment ID
            if (dat == day)
                count++;
        }
        fclose(file);
    }

    int ID = day * 10000 + (count + 1);  // e.g., 12*10000 + 1 → 120001
    return ID;
}

void bookAppointment() {

    Appointment appoint;

    FILE *file = fopen("appointments.csv", "a");    //file opening

    if(!file){
        printf("Error opening file!\n");    //if searching for file fails
        return;
    }


    appoint.patientID = generatepatientID();
    printf("Generated patient ID: %d\n", appoint.patientID);

    appoint.appointmentID = generateappointmentID();    //setting auto generated appointmentID in record.appointmentID
    printf("Generated appointment ID: %d\n", appoint.appointmentID);   //printing the auto generated appointmentID

    printf("Enter patient name:\t");                            scanf(" %[^\n]",appoint.patientName);
    printf("Enter doctor name:\t");                             scanf(" %[^\n]",appoint.doctorName);
    printf("Enter doctor's department:");                       scanf(" %[^\n]",appoint.doctorDept);
    printf("Enter date of appointment: \t\t");                  scanf(" %[^\n]",appoint.date);


    fprintf(file, "%d, %d, %s, %s, %s, %s\n", appoint.patientID, appoint.appointmentID, appoint.patientName,
             appoint.doctorName, appoint.doctorDept ,appoint.date);   //writing inputs in file

    fclose(file);     //closing the file

    printf("\nAppointment has been scheduled for %s\n\n",appoint.date);


}


void viewAppointments(){     //function to view saved information

 Appointment appoint;       //setting variable for MedicalRecord function


FILE *file = fopen("appointments.csv", "r");  //file opening in read mood

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

        sscanf(line, "%d, %d, %49[^,], %49[^,], %24[^,],%14[^\n]\n", &appoint.patientID, &appoint.appointmentID
               ,appoint.patientName ,appoint.doctorName, appoint.doctorDept, appoint.date);

        if (appoint.patientID == searchingpatientID && appoint.appointmentID == searchingappointID)  {      //checking if given and saved information matchs

            printf("\nOne Scheduled Appointment Found\n");          //printing informations after getting them
            printf("Patient ID:                 %d\n", appoint.patientID);
            printf("Appointment ID:             %d\n", appoint.appointmentID);
            printf("Patient Name:               %s\n", appoint.patientName);
            printf("Doctor's Department:        %s\n", appoint.doctorDept);
            printf("Doctor's Name:              %s\n", appoint.doctorName);
            printf("Date(yyyy-mm-dd):          %s\n", appoint.date);

            found = 1;
            break;
        }
    }

    if (!found) {          //showing that there is no saved information
        printf("\nNo record found for Patient ID %d and Appointment ID %d\n", searchingpatientID, searchingappointID);
    }

    fclose(file);            //closing file
}


int appointment() {

    int choice;

    while (1) {

        printf("\n1. Schedule an Appointment\n");
        printf("2. View scheduled Appointments\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookAppointment();
                break;
            case 2:
                viewAppointments();
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
    appointment();
}
