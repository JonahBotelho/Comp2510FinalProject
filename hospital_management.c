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

int displayPatients(Patient patients[], const int *patientCount);

int searchPatient(Patient patients[], int patientCount, int patientID);

void dischargePatient(Patient patients[], const int *patientCount, int patientID);

void manageDoctorSchedules(Patient patients[], int *patientCount);

void waitForUser();

void clearBuffer();


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
        printf("2. View All Patients\n");
        printf("3. Search Patient By ID\n");
        printf("4. Discharge Patient\n");
        printf("5. Manage Doctor Schedules\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearBuffer();
        switch (choice)
        {
            case 1:
                addPatient(patients, &patientCount);
                break;
            case 2:
                displayPatients(patients, &patientCount);
                break;
            case 3:
            {
                int patientID;
                printf("Enter Patient ID to search: ");
                scanf("%d", &patientID);
                clearBuffer();
                searchPatient(patients, patientCount, patientID);
            }
            break;
            case 4:
            {
                int patientID;
                printf("Enter Patient ID to discharge: ");
                scanf("%d", &patientID);
                clearBuffer();
                dischargePatient(patients, patientCount, patientID);
            }
            break;
            case 5:
            {
                // SCHEDULING SYSTEM
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
        return -1;
    }

    int patientID;
    char name[MAX_CHARS_IN_NAME];
    int age;
    char diagnosis[MAX_CHARS_IN_DIAGNOSIS];
    int roomNumber;

    // Patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);
    clearBuffer();

    while (patientID <= 0)
    {
        printf("Patient ID is invalid. Please try again.");
        scanf("%d", &patientID);
        clearBuffer();
    }

    // Patient name
    printf("Enter Patient name: ");
    fgets(name, MAX_CHARS_IN_NAME, stdin);
    name[strcspn(name, "\n")] = 0;

    //Patient age
    printf("Enter Patient age: ");
    scanf("%d", &age);
    clearBuffer();
    while (age < MIN_AGE || age > MAX_AGE)
    {
        printf("Patient age is invalid. Please try again.");
        scanf("%d", &age);
        clearBuffer();
    }

    // Diagnosis
    printf("Enter Patient diagnosis: ");
    fgets(diagnosis, MAX_CHARS_IN_DIAGNOSIS, stdin);
    diagnosis[strcspn(diagnosis, "\n")] = 0;

    // Room number
    printf("Enter Patient room number: ");
    scanf("%d", &roomNumber);
    clearBuffer();
    while (roomNumber <= 0)
    {
        printf("Patient room number is invalid. Please try again.");
        scanf("%d", &roomNumber);
        clearBuffer();
    }

    patients[*patientCount].patientID = patientID;
    strncpy(patients[*patientCount].name, name, MAX_CHARS_IN_NAME);
    patients[*patientCount].age = age;
    strncpy(patients[*patientCount].diagnosis, diagnosis, MAX_CHARS_IN_DIAGNOSIS);
    patients[*patientCount].roomNumber = roomNumber;

    (*patientCount)++;

    puts("\nPatient added successfully.");
    waitForUser();
    return 0;
}

int displayPatients(Patient patients[], const int *patientCount)
{
    if (patients == NULL)
    {
        puts("Patient list cannot be NULL");
        return -1;
    }

    if (*patientCount == 0)
    {
        puts("Patient count cannot be 0");
        return -1;
    }

    printf("%-10s%-20s%-10s%-20s%-10s\n", "ID", "Name", "Age", "Diagnosis", "Room Number");
    for (int i = 0; i < *patientCount; i++)
    {
        printf("%-10d", patients[i].patientID);
        printf("%-20s", patients[i].name);
        printf("%-10d", patients[i].age);
        printf("%-20s", patients[i].diagnosis);
        printf("%-10d", patients[i].roomNumber);
        printf("\n");
    }
    waitForUser();
    return 0;
}

int searchPatient(Patient patients[], int patientCount, int patientID)
{
    if (patients == NULL)
    {
        puts("Patient list cannot be NULL");
        return -1;
    }

    if (patientCount == 0)
    {
        puts("Patient count cannot be 0");
        return -1;
    }

    if (patientID < 0)
    {
        puts("Patient ID cannot be less than 0");
        return -1;
    }

    for (int i = 0; i < patientCount; i++)
    {
        if (patientID == patients[i].patientID)
        {
            puts("Patient found.");
            printf("Patient ID: %d\n", patients[i].patientID);
            printf("Patient name: %s\n", patients[i].name);
            printf("Patient age: %d\n", patients[i].age);
            printf("Patient diagnosis: %s\n", patients[i].diagnosis);
            printf("Patient room number: %d\n", patients[i].roomNumber);
            waitForUser();
            return 0;
        }
    }

    printf("\nPatient %d was not found in the system.", patientID);
    return 0;
}

void dischargePatient(Patient patients[], const int *patientCount, int patientID)
{
    int found = 0;

    for (int i = 0; i < *patientCount; i++)
    {
        if (patients[i].patientID == patientID)
        {
            found = 1;

            printf("Discharging Patient ID: %d (%s)...\n", patients[i].patientID, patients[i].name);

            // Shift records to fill the gap left by the discharged patient
            for (int j = i; j < *patientCount - 1; j++)
            {
                patients[j] = patients[j + 1];
            }

            // WHAT IS THIS DOING?? I DON'T THINK IT'S A GLOBAL VARIABLE
            *patientCount--; // Reduce patient count
            printf("Patient ID %d successfully discharged.\n", patientID);
            break;
        }
    }

    if (!found)
    {
        printf("Patient with ID %d not found.\n", patientID);
    }
}

void manageDoctorSchedules(Patient patients[], int *patientCount)
{

}

void waitForUser()
{
    printf("\nPress enter to continue.");
    clearBuffer();
}

void clearBuffer()
{
    int c;

    while (1)
    {
        c = getchar();
        if (c == '\n' || c == EOF)
        {
            break;
        }
    }
}
