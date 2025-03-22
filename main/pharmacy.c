#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "dispensary.csv"

typedef struct 
{
    int     medicineID;
    char    name[50];
    char    group[100];
    char    company[40];
    int     quantity;
    //float   price;          Future Update: Billing System

} Medicine;

void addNewMedicine(){
    //aa
}

void main();

void updateDispensary(){
    //aa
}

void viewDispensary(){

    FILE *file = fopen(FILE_NAME, "r");

    if(!file){
        printf("No records found\n");
        return;
    }    

    printf("\nID | Name | Quantity | Price\n");
    printf("--------------------------------\n");
    
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        Medicine med;
        sscanf(line, "%d,%49[^,],%99[^,],%39[^,],%d", &med.medicineID, med.name, med.group, med.company, &med.quantity);
        printf("%d | %s | %s | %s | %d \n", med.medicineID, med.name, med.group, med.company, med.quantity);
    }
    fclose(file);
}

void dispensary(){

    int choice;

    do{
        printf("Hospital Dispensary System\n");

        printf("1. View Dispensary\n");
        printf("2. Add new Medicine\n");
        printf("3. Update Dispensary\n");
        printf("4. Exit\n");

        scanf("%d", &choice);

        switch (choice){

            case 1:         viewDispensary();               break;
            case 2:         addNewMedicine();               break;
            case 3:         updateDispensary();             break;
            case 4:         main();                         break;
            default:        printf("Invalid Choice.\n");    break;
        
        }
    }while (choice != 4);
    
}

void main(){

    dispensary();
}