#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "dispensary.csv"

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

void addNewMedicine();

void generateMedicineID(){

    char    medicineName[30];
    char    medicineDept[40];
    char    medicineSubDept[40];

    printf("Enter the medicine name:\t");
    scanf(" %[^\n]", medicineName);
    printf("Enter the medicine department:\t");
    scanf(" %[^\n]", medicineDept);

    FILE *dispensaryFile = fopen("dispensary.csv", "r");
    char line[200];

    if(dispensaryFile){

        while (fgets(line, sizeof(line), dispensaryFile))
        {
            Medicine med;
            sscanf(line, "%d , %49[^,]", &med.medicineID, &med.name);

            if(strcmp(med.name, medicineName) == 0){

                char choice;
                printf("Medicine already exists in the database.\n");
                printf("Do you want to update the quantity of that medicine?\n");
                
                choice = getchar();

                if(choice == 'y' || choice == 'Y'){
                    addNewMedicine();
                    return;
                }
                else{
                    return;
                }
            }    
        }
    }
            
    fclose(dispensaryFile);

    printf("Enter Department name:   \t");
    scanf(" [^\n]", medicineDept);
    printf("Enter Sub-Divisions name:\t");
    scanf(" [^\n]", medicineSubDept);

    

}

void medicineCodes(){

    char department[30];
    char departmentCode;
    char subDivisions[40];
    char subDivisionsCode;

    FILE *file = fopen("medicine-characteristics.csv", "r");

    if(!file){
        printf("No records found\n");
        return;
    } 

    printf("Department                | Dept-Code | Sub-Divisions                           | Sub-Div-Code\n");
    printf("----------------------------------------------------------------------------------------------\n");

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        
        if (strlen(line) <= 1) {        // Skip empty lines
            continue;
        }

        sscanf(line, "%29[^,], %c, %39[^,], %c", department, &departmentCode, subDivisions, &subDivisionsCode);
        printf("%s | %c | %s | %c \n", department, departmentCode, subDivisions, subDivisionsCode);
        
    }

    fclose(file);

    printf("\n\n");


}

void addNewMedicine(){
    
    FILE *file = fopen(FILE_NAME, "r+");

    if(!file){
        printf("No records found\n");
        return;
    }

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

    fclose(file);

    printf("\n\n");
}

void dispensary(){

    int choice;

    do{
        printf("Hospital Dispensary System\n");

        printf("1. Medicine Codes\n");
        printf("2. View Dispensary\n");
        printf("3. Add new Medicine\n");
        printf("4. Update Dispensary\n");
        printf("5. Exit\n");

        scanf("%d", &choice);

        switch (choice){

            case 1:         medicineCodes();                break;
            case 2:         viewDispensary();               break;
            case 3:         addNewMedicine();               break;
            case 4:         updateDispensary();             break;
            case 5:         main();                         break;
            default:        printf("Invalid Choice.\n");    break;
        
        }
    }while (choice != 4);
    
}

void main(){

    dispensary();
}