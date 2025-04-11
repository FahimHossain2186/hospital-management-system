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
void main();
void updateDispensary();
void medicineCodes();

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
                printf("Do you want to update the quantity of that medicine? (y/n): ");
                getchar(); // to consume newline
                choice = getchar();
            
                if(choice == 'y' || choice == 'Y'){
                    fclose(dispensaryFile);
                    updateDispensary();
                    return -1; // Fix: return a valid int
                }
            }    
        }
        fclose(dispensaryFile);
    }

    char choice;
    printf("Do you want to review the medicine codes?(y/n)\n");
    scanf(" %c", &choice);
    

    if(choice == 'y' || choice == 'Y')                          medicineCodes();       
        
            
    printf("\n\nEnter Department code:   \t");
    scanf("%d", &medicineDept);
    printf("Enter Sub-Divisions code:\t");
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
    scanf(" %[^\n]", med.genericName); 
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

void updateDispensary() {

    Medicine medTemp;
    char line[200];
    int found = 0;

    printf("Enter Medicine ID: ");
    scanf("%d", &medTemp.medicineID);

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

            printf("Current Quantity of %s (ID: %d): %d\n", med.name, med.medicineID, med.quantity);
            printf("Do you want to add (a) or subtract (s) quantity? \t");
            scanf(" %c", &operation);
            printf("Enter amount:                                    \t");
            scanf("%d", &amount);

            if (operation == 'a' || operation == 'A') {
                med.quantity += amount;
            } else if (operation == 's' || operation == 'S') {
                if (amount > med.quantity) {
                    printf("Cannot subtract more than existing quantity. Setting to 0.\n");
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
        printf("Medicine quantity updated successfully.\n");
    else
        printf("Medicine not found.\n");

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

        printf("\nYour choice:\t");
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