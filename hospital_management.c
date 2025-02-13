/**
 * @author Cole Campbell
 * @author Jonah Botelho
 */

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_CHARS_IN_NAME 100
#define MAX_CHARS_IN_DIAGNOSIS 200
#define MIN_AGE 0
#define MAX_AGE 150
#define DAYS_IN_WEEK 7
#define SHIFTS_IN_DAY 3

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
void manageDoctorSchedules(int doctorSchedule[7][3]);
void assignDoctors(int doctorSchedule[7][3]);
void displayDoctorSchedule(int doctorSchedule[7][3]);
void waitForUser();
void clearBuffer();

/**
 * Entry point for the program, displays a menu for the user, and calls support functions depending on their input.
 *
 */
int main()
{
    Patient patients[MAX_PATIENTS]; // Array to store patient records, maximum 50 patients
    int doctorSchedule[7][3];
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
                dischargePatient(patients, &patientCount, patientID);
            }
            break;
            case 5:
            {
                manageDoctorSchedules(doctorSchedule);
            }
            break;
            case 6:
                printf("Exiting the system...\n");
                return 1;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/**
 * Adds a new patient to the hospital's database of patients.
 * Prompts the user for patient's information, and validates it.
 *
 * @param patients array of paitents.
 * @param patientCount total number of current patients.
 * @return 0 if program is ran successfully
 *        -1 if expected error is encountered
 */
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
    printf("\nEnter Patient ID: ");
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

/**
 * Displays all patients currently registered in the hospital.
 *
 * @param patients array of patients
 * @param patientCount number of patients
 * @return 0 if program is ran successfully
 *        -1 if expected error is encountered
 */
int displayPatients(Patient patients[], const int *patientCount)
{
    if (*patientCount == 0)
    {
        puts("There are no patients.");
        return -1;
    }

    printf("\n%-10s%-20s%-10s%-20s%-10s\n", "ID", "Name", "Age", "Diagnosis", "Room Number");
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

/**
 * Searches for a specific patient in the database.
 *
 * @param patients array of patients
 * @param patientCount total number of patients
 * @return 0 if program is ran successfully
 *        -1 if expected error is encountered
 */
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
    waitForUser();
    return 0;
}

/**
 * Discharges a patient from the hospital, removing them from the database.
 *
 * @param patients array of patients
 * @param patientCount total number of patients
 * @param patientID ID of patient to be removed
 */
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

            printf("Patient ID %d successfully discharged.\n", patientID);
            break;
        }
    }

    if (!found)
    {
        printf("Patient with ID %d not found.\n", patientID);
    }
    waitForUser();
}

/**
 * Enters the doctor scheduling system, which allows users to add doctors to shifts,
 * and display the current shift schedule for the week.
 *
 * @param doctorSchedule the array for the doctor schedule
 */
void manageDoctorSchedules(int doctorSchedule[7][3])
{
    int choice;

    while (1)
    {
        // Display the menu
        printf("\nDoctor Scheduling\n");
        printf("1. Assign Doctors To Shift\n");
        printf("2. View Doctor Schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearBuffer();
        switch (choice)
        {
            case 1:
                assignDoctors(doctorSchedule);
                break;
            case 2:
                displayDoctorSchedule(doctorSchedule);
                break;
            case 3:
                printf("Exiting the system...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

/**
 * A helper function to assign doctors to certain days and shifts.
 *
 * @param doctorSchedule the array for the doctor schedule
 */
void assignDoctors(int doctorSchedule[7][3]) {
    int choice;

    do {
        int dayChoice, shiftChoice, doctorsToAdd;

        // Day selection with input validation
        do {
            printf("\nSelect the day to assign (1-7):\n");
            printf("(1) Monday\n(2) Tuesday\n(3) Wednesday\n(4) Thursday\n");
            printf("(5) Friday\n(6) Saturday\n(7) Sunday\n");
            printf("Enter your choice: ");
            if (scanf("%d", &dayChoice) != 1 || dayChoice < 1 || dayChoice > 7) {
                printf("Invalid input. Please enter a number between 1 and 7.\n");
                clearBuffer();
            } else {
                break;
            }
        } while (1);

        // Shift selection with input validation
        do {
            printf("\nSelect the shift to assign (1-3):\n");
            printf("(1) Morning\n(2) Afternoon\n(3) Evening\n");
            printf("Enter your choice: ");
            if (scanf("%d", &shiftChoice) != 1 || shiftChoice < 1 || shiftChoice > 3) {
                printf("Invalid input. Please enter a number between 1 and 3.\n");
                clearBuffer();
            } else {
                break;
            }
        } while (1);

        // Number of doctors input validation
        do {
            printf("\nHow many doctors would you like to assign to this shift? ");
            if (scanf("%d", &doctorsToAdd) != 1 || doctorsToAdd < 0) {
                printf("Invalid input. Please enter a valid number (0 or more).\n");
                clearBuffer();
            } else {
                break;
            }
        } while (1);

        // Assign doctors to the selected shift
        doctorSchedule[dayChoice - 1][shiftChoice - 1] = doctorsToAdd;
        printf("\nSuccessfully assigned %d doctor(s) to %s - %s shift.\n",
               doctorsToAdd,
               (dayChoice == 1) ? "Monday" : (dayChoice == 2) ? "Tuesday" :
               (dayChoice == 3) ? "Wednesday" : (dayChoice == 4) ? "Thursday" :
               (dayChoice == 5) ? "Friday" : (dayChoice == 6) ? "Saturday" : "Sunday",
               (shiftChoice == 1) ? "Morning" : (shiftChoice == 2) ? "Afternoon" : "Evening");

        // Ask if the user wants to continue assigning doctors
        printf("\nWould you like to assign another shift?\n");
        printf("(1) Yes\n(2) No\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice != 1) {
            printf("Exiting assignment process...\n");
        }

    } while (choice == 1);
}

/**
 * A helper function to display the entire 2-D array of the doctor schedule.
 *
 * @param doctorSchedule the array for the doctor schedule
 */
void displayDoctorSchedule(int doctorSchedule[7][3])
{
    printf("\t\t\t%-10s%-10s%-10s%-10s%-10s%-10s%-10s", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday");

    for (int i = 0; i < SHIFTS_IN_DAY; i++)
    {
        i == 0 ? printf("\nMorning\t\t") : i == 1 ? printf("\nAfternoon\t") : printf("\nEvening\t\t");

        for (int j = 0; j < DAYS_IN_WEEK; j++)
        {
            printf("%-10d", doctorSchedule[j][i]);
        }
        printf("\n");
    }
}

/**
 * Pauses the program until the user enters an input.
 * Used to indicate that an action has been completed, and let the user view the result.
 */
void waitForUser()
{
    printf("\nPress enter to continue.");
    clearBuffer();
}

/**
 * Clears the input buffer using getchar() several times.
 */
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

