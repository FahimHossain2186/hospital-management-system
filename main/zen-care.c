#include <stdio.h>
#include <time.h>

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
    int     ID;
    Date    Date;               // Format: "YYYY-MM-DD"

    //Future Improvement --> Time

    int     patientID;
    char    patientName[50];

    char    doctorDept[25];
    char    doctorName[50];
    
} Appointment;

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
    char    group[100];
    char    company[20];
    int     quantity;
    //float   price;          Future Update: Billing System

} Medicine;



int main(){

    
} 