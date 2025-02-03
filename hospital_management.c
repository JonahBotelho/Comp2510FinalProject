//
// Created by Cole Campbell and Jonah Botelho
// Purpose...
//

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_CHARS_IN_NAME 100
#define MAX_CHARS_IN_DIAGNOSIS 200
#define MIN_AGE 0
#define MAX_AGE 150

// Define the structure for a Patient record
typedef struct
{
    int patientID; // Unique Patient ID
    char name[MAX_CHARS_IN_NAME]; // Full Name of the patient
    int age; // Age of the patient
    char diagnosis[MAX_CHARS_IN_DIAGNOSIS]; // Medical condition or reason for admission
    int roomNumber; // Assigned room number in the hospital
} Patient;

int addPatient(Patient patients[], int *patientCount);
int displayPatients(Patient patients[], int *patientCount);
int searchPatients(Patient patients[], int *patientCount, int patientID);
int updatePatients(Patient patients[], int *patientCount, int patientID);
int deletePatient(Patient patients[], int *patientCount);


int main()
{
    Patient patients[MAX_PATIENTS]; // Array to store patient records, maximum 50 patients
    int patientCount = 0; // Counter to keep track of how many patients have been added
    int choice;

    while (1)
    {
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

        switch (choice)
        {
            case 1:
                addPatient(patients, &patientCount);
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

int addPatient(Patient patients[], int *patientCount)
{
    if (*patientCount >= MAX_PATIENTS)
    {
        printf("\nPatient count has reached its limit. Remove a patient and try again.");
        return 0;
    }

    int patientID;
    char name[MAX_CHARS_IN_NAME];
    int age;
    char diagnosis[MAX_CHARS_IN_DIAGNOSIS];
    int roomNumber;

    // Patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);
    getchar();
    if (patientID <= 0) //TODO validate patientID is unique
    {
        printf("\nPatient ID is invalid. Please try again."); //TODO let user correct input
        return 0;
    }

    // Patient name
    printf("Enter Patient name: ");
    fgets(name, MAX_CHARS_IN_NAME, stdin);
    name[strcspn(name, "\n")] = 0;

    //Patient age
    printf("Enter Patient age: ");
    scanf("%d", &age);
    getchar();
    if (age < MIN_AGE || age > MAX_AGE)
    {
        printf("\nPatient age is invalid. Please try again.");
        return 0;
    }

    // Diagnosis
    printf("Enter Patient diagnosis: ");
    fgets(diagnosis, MAX_CHARS_IN_DIAGNOSIS, stdin);
    diagnosis[strcspn(diagnosis, "\n")] = 0;

    // Room number
    printf("Enter Patient room number: ");
    scanf("%d", &roomNumber);
    if (roomNumber <= 0)
    {
        printf("\nPatient room number is invalid. Please try again.");
        return 0;
    }

    patients[*patientCount].patientID = patientID;
    strncpy(patients[*patientCount].name, name, MAX_CHARS_IN_NAME);
    patients[*patientCount].age = age;
    strncpy(patients[*patientCount].diagnosis, diagnosis, MAX_CHARS_IN_DIAGNOSIS);
    patients[*patientCount].roomNumber = roomNumber;

    puts("\nPatient successfully added to record");

    (*patientCount)++;
    return 0;
}

int displayPatients(Patient patients[], int *patientCount)
{
    return 0;
}

int searchPatients(Patient patients[], int *patientCount, int patientID)
{
    return 0;
}

int updatePatients(Patient patients[], int *patientCount, int patientID)
{
    return 0;
}

int deletePatient(Patient patients[], int *patientCount)
{
    return 0;
}
