#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "dispensary.csv"

typedef struct{

    int year;
    int month;
    int day;

}Time;

Time currentTime(){

    time_t t = time(NULL);
    struct tm date = *localtime(&t);

    Time time;

    time.year = date.tm_year + 1900;
    time.month = date.tm_mon + 1;
    time.day = date.tm_mday;
    
    return time;
}

typedef struct 
{
    int     year;
    int     month;
    int     day;

} Date;

typedef struct 
{
    char    houseNo[12];
    int     road; 
    int     postalCode;
    char    area[30];
    char    city[15];
    char    district[15];

} Address;

typedef struct 
{
    int     id;
    char    name [50];
    int     age;
    char    gender[10];
    Address address;
    char    disease[30];
    char    contact[20];
    int     password;

} Patient;

typedef struct 
{
    int     id;
    char    name[50];
    char    department[25];
    char    title[25];              // example : associate professor, consultant
    Address address;
    char    contactNo[20];
    char    contactMail[50];
    int     password;

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

typedef struct 
{
    int     id;
    char    name[50];
    char    department[25];
    char    title[25];
    int     password;

} Management;

typedef struct 
{
    int     id;
    char    name[50];
    char    department[25];
    char    title[25];
    int     password;

} Admin;

typedef struct 
{
    int     patientID;
    char    patientName[50];
    
    int     appointmentID;
    
    char    doctorDept[25];
    char    doctorName[50];    
    char    diagnosis[500];
    char    prescription[500];
    Date    date[15];
    
} MedicalRecord;

typedef struct 
{
    int     medicineID;
    char    name[50];
    char    dosageForm[20];
    char    genericName[50];
    char    group[100];
    char    company[40];
    int     quantity;
    //float   price;          Future Update: Billing System

} Medicine;

typedef struct
{
    int     appointmentID;
    int     patientID;

    char    date[15];
    char    patientName[50];

    char    doctorDept[25];
    char    doctorName[50];

} Appointment;

int     login(int userType);
void    logout();
void    addPatient();
void    viewPatient();
void    viewDoctor();
void    viewMedicalRecord();
void    viewDispensary();
void    bookAppointment();
void    viewAppointment();
void    addRecord();
void    updateDispensary();
void    viewMedicalRecord();
int     generatepatientID();
int     generateappointmentID();
void    addRecord();
void    viewMedicalRecord(); 
int     generateMedicineID(char medicineName[30]);
void    addNewMedicine();
void    updateDispensary();
void    medicineCodes();
//void    dispensary();
int     generatepatientID();
int     generateappointmentID();
void    bookAppointment();
void    viewAppointments();


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

int generateMedicineID(char medicineName[30]){

    int     medicineDept;
    int     medicineSubDept;
    int     generatedID = 0;
    char    line[200];

    FILE *dispensaryFile = fopen(FILE_NAME, "r");

    if(dispensaryFile){

        while (fgets(line, sizeof(line), dispensaryFile))
        {
            Medicine med;
            sscanf(line, "%d , %49[^,]", &med.medicineID, med.name);

            if(strcmp(med.name, medicineName) == 0){

                char choice;
                printf("Medicine already exists in the database.\n");
                printf("Do you want to update the quantity of that medicine? (y/n): \t");
                getchar(); // to consume newline
                choice = getchar();
            
                if(choice == 'y' || choice == 'Y'){
                    fclose(dispensaryFile);
                    updateDispensary(med.medicineID);
                    return -1; // Fix: return a valid int
                }
                else if(choice == 'n' || choice == 'N'){
                    fclose(dispensaryFile);
                    dispensary();
                }
            }    
        }
        fclose(dispensaryFile);
    }

    char choice;
    printf("Do you want to review the medicine codes?(y/n):\t\t\t");
    scanf(" %c", &choice);
    

    if(choice == 'y' || choice == 'Y')                          medicineCodes();       
        
            
    printf("Enter Department code:                                   \t");
    scanf("%d", &medicineDept);
    printf("Enter Sub-Divisions code:                                \t");
    scanf("%d", &medicineSubDept);

    generatedID = medicineDept * 10 + medicineSubDept;
    generatedID *= 1000;
    int highestSuffix = -1;

    dispensaryFile = fopen(FILE_NAME, "r");

    if(dispensaryFile){
        while(fgets(line, sizeof(line), dispensaryFile)){
            Medicine med;
            sscanf(line, "%d , %49[^,]", &med.medicineID, med.name);

            if(med.medicineID / 1000 == generatedID / 1000){
                int suffix = med.medicineID % 1000;
                if(suffix > highestSuffix)
                    highestSuffix = suffix;
            }
        }
        fclose(dispensaryFile);
    }

    generatedID += highestSuffix + 1;

    return generatedID;

}

void medicineCodes(){

    char department[30];
    int departmentCode;
    char subDivisions[40];
    int subDivisionsCode;

    FILE *file = fopen("medicine-characteristics.csv", "r");

    if(!file){
        printf("No records found\n");
        return;
    } 

    printf("\n----------------------------------------------------------------------------------------------");
    printf("\nDepartment                | Dept-Code | Sub-Divisions                           | Sub-Div-Code\n");
    printf("----------------------------------------------------------------------------------------------\n");

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        
        if (strlen(line) <= 1) {        // Skip empty lines
            continue;
        }

        sscanf(line, "%29[^,], %d, %39[^,], %d", department, &departmentCode, subDivisions, &subDivisionsCode);
        printf("%s | %-9d | %s | %d \n", department, departmentCode, subDivisions, subDivisionsCode);

        
    }

    printf("----------------------------------------------------------------------------------------------\n");

    fclose(file);

    printf("\n\n");


}

void addNewMedicine(){

    Medicine med;

    printf("Enter the Medicine name:                                   \t");
    scanf(" %[^\n]", med.name);

    med.medicineID = generateMedicineID(med.name);

    printf("Dosage Form (Tablet/Injection/Capsule/Oral Powder/Inhaler):\t");
    scanf(" %[^\n]", med.dosageForm);
    printf("Enter the Generic name:                                    \t");
    scanf(" %[^\n]", med.genericName); 
    printf("Enter the Group name:                                      \t");
    scanf(" %[^\n]", med.group); 
    printf("Enter the Company provider name:                           \t");
    scanf(" %[^\n]", med.company); 
    printf("Enter the Amount:                                          \t");
    scanf(" %d", &med.quantity); 
    
    FILE *file = fopen(FILE_NAME, "a");

    if(!file){
        printf("No records found\n");
        return;
    }

    fprintf(file, "%d , %s , %s , %s , %s , %s , %d\n", med.medicineID, med.name, med.dosageForm, med.genericName, med.group, med.company, med.quantity);

    fclose(file);

    printf("✅ Medicine added successfully with ID: %d\n", med.medicineID);
    
}

void updateDispensary(int x) {

    Medicine medTemp;
    char line[200];
    int found = 0;

    medTemp.medicineID = x;

    FILE *dispensaryFile = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (!dispensaryFile || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), dispensaryFile)) {
        Medicine med;
        sscanf(line, "%d, %49[^,], %19[^,], %49[^,], %99[^,], %39[^,], %d",
               &med.medicineID, med.name, med.dosageForm, med.genericName, med.group, med.company, &med.quantity);

        if (medTemp.medicineID == med.medicineID) {
            found = 1;

            char operation;
            int amount;

            printf("Current Quantity of %s (ID: %d):           \t%d\n", med.name, med.medicineID, med.quantity);
            printf("Do you want to add (a) or subtract (s) quantity? \t");
            scanf(" %c", &operation);
            printf("Enter amount:                                    \t");
            scanf("%d", &amount);

            if (operation == 'a' || operation == 'A') {
                med.quantity += amount;
            } else if (operation == 's' || operation == 'S') {
                if (amount > med.quantity) {
                    printf("\nCannot subtract more than existing quantity. Setting to 0.\n");
                    med.quantity = 0;
                } else {
                    med.quantity -= amount;
                }
            } else {
                printf("Invalid operation. No change made.\n");
            }
        }

        // Write to temp file (updated or unchanged)
        fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%d\n",
                med.medicineID, med.name, med.dosageForm, med.genericName, med.group, med.company, med.quantity);
    }

    fclose(dispensaryFile);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);

    if (found)
        printf("\nMedicine quantity updated successfully.\n");
    else
        printf("\nMedicine not found.\n");

    char choice;

    while(choice != 'Y' || choice != 'y' ||choice != 'N' ||choice != 'n')
    {
        printf("\nDo you want to update the quantity of that medicine? (y/n): ");
    
        getchar(); // to consume newline
        choice = getchar();
    
        if(choice == 'y' || choice == 'Y')
        {
            int medicineID;

            printf("\n\nEnter Medicine ID:                                     \t");
            scanf("%d", &medicineID);
            updateDispensary(medicineID);
        }                          
        
        else if(choice == 'n' || choice == 'N')                     dispensary();
        else                                                        printf("Wrong Input.\nPlease try again\n");
    }  

}

void viewDispensary(){

    FILE *file = fopen(FILE_NAME, "r");

    if(!file){
        printf("No records found\n");
        return;
    }    

    printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\nID    | Name       | Dosage Form | Generic Name                                | Group                                      | Company                     | Quantity\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    char line[300];
    while (fgets(line, sizeof(line), file)) {
        
        if (strlen(line) <= 1) {        // Skip empty lines
            continue;
        }

        Medicine med;

        if (sscanf(line, "%d, %49[^,], %19[^,], %49[^,], %99[^,], %39[^,], %d", &med.medicineID, med.name, med.dosageForm, med.genericName, med.group, med.company, &med.quantity) == 7)
            printf("%d | %s | %s | %s | %s | %s | %d \n", med.medicineID, med.name, med.dosageForm, med.genericName, med.group, med.company, med.quantity);
        
    }

    printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------");

    fclose(file);

    printf("\n\n");
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
    int choice, medicineID;

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
                    case 1:             viewPatient();          break;
                    case 2:             viewDoctor();           break;
                    case 3:             viewMedicalRecord();    break;
                    case 4:
                        viewDispensary();
                        break;
                    case 5:
                        bookAppointment();
                        break;
                    case 6:
                        viewAppointment();
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
                        viewMedicalRecord();
                        break;
                    case 4:
                        viewDispensary();
                        break;
                    case 5:
                        bookAppointment();
                        break;
                    case 6:
                        viewAppointment();
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
                        viewMedicalRecord();
                        break;
                    case 4:
                        viewDispensary();
                        break;
                    case 5:
                        viewAppointment();
                        break;
                    case 6:
                        addRecord();
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
                        viewMedicalRecord();
                        break;
                    case 4:
                        viewDispensary();
                        break;
                    case 5:
                        viewAppointment();
                        break;
                    case 6:
                        addPatient();
                        break;
                    case 7:
                        addRecord();
                    case 8:
                        logout();
                        loggedIn = 0;
                        break;
                    default:
                        printf("Invalid Input.\n");
                }
            }
            else if (userType == 6) {
                
                int choice, medicineID;

                do{
                    printf("\n\nHospital Dispensary System\n");
            
                    printf("1. Medicine Codes\n");
                    printf("2. View Dispensary\n");
                    printf("3. Add new Medicine\n");
                    printf("4. Update Dispensary\n");
                    printf("5. Exit\n");
                    
                    printf("\nYour choice:                                             \t");
                    scanf("%d", &choice);
            
                    switch (choice){
            
                        case 1:         medicineCodes();                break;
                        case 2:         viewDispensary();               break;
                        case 3:         addNewMedicine();               break;
                        case 5:         main();                         break;
                        case 4:         
            
                            printf("\n\nEnter Medicine ID:                                     \t");
                            scanf("%d", &medicineID);
                            updateDispensary(medicineID);             
                            break;
            
                        default:        printf("Invalid Choice.\n");    break;
                    
                    }
                }while (choice != 5);
            }
        }
    }

    return 0;
}
