//
// Created by Cole Campbell and Jonah Botelho
// Purpose...
//

#include <stdio.h>
#include <string.h>

// Define the structure for a Patient record
typedef struct {
    int patientID;            // Unique Patient ID
    char name[100];           // Full Name of the patient
    int age;                  // Age of the patient
    char diagnosis[200];      // Medical condition or reason for admission
    int roomNumber;           // Assigned room number in the hospital
} Patient;

int addPatient(Patient patients, int patientCount);
int displayPatients(Patient patients, int patientCount);
int searchPatients(Patient patients, int patientCount, int patientID);
int updatePatients(Patient patients, int patientCount, int patientID);
int deletePatient(Patient patients, int patientCount);


int main() {
    Patient patients[50];         // Array to store patient records, maximum 50 patients
    int patientCount = 0;         // Counter to keep track of how many patients have been added
    int choice;

    while(1) {
        // Display the menu
        printf("\nHospital Management System\n");
        printf("1. Add Patient Record\n");
        printf("2. Display All Patient Records\n");
        printf("3. Search Patient Record\n");
        printf("4. Update Patient Record\n");
        printf("5. Delete Patient Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                // addPatient(patients, &patientCount);
            break;
            case 2:
                // displayPatients(patients, patientCount);
            break;
            case 3:
            {
                int patientID;
                printf("Enter Patient ID to search: ");
                scanf("%d", &patientID);
                // searchPatient(patients, patientCount, patientID);
            }
            break;
            case 4:
            {
                int patientID;
                printf("Enter Patient ID to update: ");
                scanf("%d", &patientID);
                // updatePatient(patients, patientCount, patientID);
            }
            break;
            case 5:
            {
                int patientID;
                printf("Enter Patient ID to delete: ");
                scanf("%d", &patientID);
                // deletePatient(patients, &patientCount, patientID);
            }
            break;
            case 6:
                printf("Exiting the system...\n");
            return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int addPatient(Patient patients, int patientCount)
{
    return 0;
}

int displayPatients(Patient patients, int patientCount)
{
    return 0;
}

int searchPatients(Patient patients, int patientCount, int patientID)
{
    return 0;
}

int updatePatients(Patient patients, int patientCount, int patientID)
{
    return 0;
}

int deletePatient(Patient patients, int patientCount)
{
    return 0;
}
