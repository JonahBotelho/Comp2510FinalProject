// /**
//  * @author Cole Campbell
//  * @author Jonah Botelho
//  */
//
// #include <stdio.h>
// #include <string.h>
//
// #define MAX_PATIENTS 50
// #define MAX_CHARS_IN_NAME 100
// #define MAX_CHARS_IN_DIAGNOSIS 200
// #define MIN_AGE 0
// #define MAX_AGE 150
// #define DAYS_IN_WEEK 7
// #define SHIFTS_IN_DAY 3
//
// // Define the structure for a Patient record
// typedef struct
// {
//     int patientID; // Unique Patient ID
//     char name[MAX_CHARS_IN_NAME]; // Full Name of the patient
//     int age; // Age of the patient
//     char diagnosis[MAX_CHARS_IN_DIAGNOSIS]; // Medical condition or reason for admission
//     int roomNumber; // Assigned room number in the hospital
// } Patient;
//
// int addPatient(Patient patients[], int *patientCount);
//
// int displayPatients(Patient patients[], const int *patientCount);
//
// int searchPatient(Patient patients[], int patientCount, int patientID);
//
// void dischargePatient(Patient patients[], const int *patientCount, int patientID);
//
// void manageDoctorSchedules(int doctorSchedule[7][3]);
//
// void assignDoctors(int doctorSchedule[7][3]);
//
// void displayDoctorSchedule(int doctorSchedule[7][3]);
//
// void waitForUser();
//
// void clearBuffer();
//
// /**
//  * Entry point for the program, displays a menu for the user, and calls support functions depending on their input.
//  *
//  */
// int main()
// {
//     Patient patients[MAX_PATIENTS]; // Array to store patient records, maximum 50 patients
//     int doctorSchedule[7][3];
//     int patientCount = 0; // Counter to keep track of how many patients have been added
//     int choice;
//
//     while (1)
//     {
//         // Display the menu
//         printf("\nHospital Management System\n");
//         printf("1. Add Patient Record\n");
//         printf("2. View All Patients\n");
//         printf("3. Search Patient By ID\n");
//         printf("4. Discharge Patient\n");
//         printf("5. Manage Doctor Schedules\n");
//         printf("6. Exit\n");
//         printf("Enter your choice: ");
//
//         scanf("%d", &choice);
//         clearBuffer();
//         switch (choice)
//         {
//             case 1:
//                 addPatient(patients, &patientCount);
//                 break;
//             case 2:
//                 displayPatients(patients, &patientCount);
//                 break;
//             case 3:
//             {
//                 int patientID;
//                 printf("Enter Patient ID to search: ");
//                 scanf("%d", &patientID);
//                 clearBuffer();
//                 searchPatient(patients, patientCount, patientID);
//             }
//             break;
//             case 4:
//             {
//                 int patientID;
//                 printf("Enter Patient ID to discharge: ");
//                 scanf("%d", &patientID);
//                 clearBuffer();
//                 dischargePatient(patients, &patientCount, patientID);
//             }
//             break;
//             case 5:
//             {
//                 manageDoctorSchedules(doctorSchedule);
//             }
//             break;
//             case 6:
//                 printf("Exiting the system...\n");
//                 return 1;
//             default:
//                 printf("Invalid choice. Please try again.\n");
//         }
//     }
//
//     return 0;
// }
//
// /**
//  * Adds a new patient to the hospital's database of patients.
//  * Prompts the user for patient's information, and validates it.
//  *
//  * @param patients array of paitents.
//  * @param patientCount total number of current patients.
//  * @return 0 if program is ran successfully
//  *        -1 if expected error is encountered
//  */
// int addPatient(Patient patients[], int *patientCount)
// {
//     if (*patientCount >= MAX_PATIENTS)
//     {
//         printf("\nPatient count has reached its limit. Remove a patient and try again.");
//         return -1;
//     }
//
//     int patientID;
//     char name[MAX_CHARS_IN_NAME];
//     int age;
//     char diagnosis[MAX_CHARS_IN_DIAGNOSIS];
//     int roomNumber;
//
//     // Patient ID
//     printf("\nEnter Patient ID: ");
//     scanf("%d", &patientID);
//     clearBuffer();
//
//     while (patientID <= 0)
//     {
//         printf("Patient ID is invalid. Please try again.");
//         scanf("%d", &patientID);
//         clearBuffer();
//     }
//
//     // TODO ADD UNIQUE PATIENT ID CHECK
//
//     // Patient name
//     printf("Enter Patient name: ");
//     fgets(name, MAX_CHARS_IN_NAME, stdin);
//     name[strcspn(name, "\n")] = 0;
//
//     //Patient age
//     printf("Enter Patient age: ");
//     scanf("%d", &age);
//     clearBuffer();
//     while (age < MIN_AGE || age > MAX_AGE)
//     {
//         printf("Patient age is invalid. Please try again.");
//         scanf("%d", &age);
//         clearBuffer();
//     }
//
//     // Diagnosis
//     printf("Enter Patient diagnosis: ");
//     fgets(diagnosis, MAX_CHARS_IN_DIAGNOSIS, stdin);
//     diagnosis[strcspn(diagnosis, "\n")] = 0;
//
//     // Room number
//     printf("Enter Patient room number: ");
//     scanf("%d", &roomNumber);
//     clearBuffer();
//     while (roomNumber <= 0)
//     {
//         printf("Patient room number is invalid. Please try again.");
//         scanf("%d", &roomNumber);
//         clearBuffer();
//     }
//
//     patients[*patientCount].patientID = patientID;
//     strncpy(patients[*patientCount].name, name, MAX_CHARS_IN_NAME);
//     patients[*patientCount].age = age;
//     strncpy(patients[*patientCount].diagnosis, diagnosis, MAX_CHARS_IN_DIAGNOSIS);
//     patients[*patientCount].roomNumber = roomNumber;
//
//     (*patientCount)++;
//
//     puts("\nPatient added successfully.");
//     waitForUser();
//     return 0;
// }
//
// /**
//  * Displays all patients currently registered in the hospital.
//  *
//  * @param patients array of patients
//  * @param patientCount number of patients
//  * @return 0 if program is ran successfully
//  *        -1 if expected error is encountered
//  */
// int displayPatients(Patient patients[], const int *patientCount)
// {
//     if (*patientCount == 0)
//     {
//         puts("There are no patients.");
//         return -1;
//     }
//
//     printf("\n%-10s%-20s%-10s%-20s%-10s\n", "ID", "Name", "Age", "Diagnosis", "Room Number");
//     for (int i = 0; i < *patientCount; i++)
//     {
//         printf("%-10d", patients[i].patientID);
//         printf("%-20s", patients[i].name);
//         printf("%-10d", patients[i].age);
//         printf("%-20s", patients[i].diagnosis);
//         printf("%-10d", patients[i].roomNumber);
//         printf("\n");
//     }
//     waitForUser();
//     return 0;
// }
//
// /**
//  * Searches for a specific patient in the database.
//  *
//  * @param patients array of patients
//  * @param patientCount total number of patients
//  * @return 0 if program is ran successfully
//  *        -1 if expected error is encountered
//  */
// int searchPatient(Patient patients[], int patientCount, int patientID)
// {
//     if (patients == NULL)
//     {
//         puts("Patient list cannot be NULL");
//         return -1;
//     }
//
//     if (patientCount == 0)
//     {
//         puts("Patient count cannot be 0");
//         return -1;
//     }
//
//     if (patientID < 0)
//     {
//         puts("Patient ID cannot be less than 0");
//         return -1;
//     }
//
//     for (int i = 0; i < patientCount; i++)
//     {
//         if (patientID == patients[i].patientID)
//         {
//             puts("Patient found.");
//             printf("Patient ID: %d\n", patients[i].patientID);
//             printf("Patient name: %s\n", patients[i].name);
//             printf("Patient age: %d\n", patients[i].age);
//             printf("Patient diagnosis: %s\n", patients[i].diagnosis);
//             printf("Patient room number: %d\n", patients[i].roomNumber);
//             waitForUser();
//             return 0;
//         }
//     }
//
//     printf("\nPatient %d was not found in the system.", patientID);
//     waitForUser();
//     return 0;
// }
//
// /**
//  * Discharges a patient from the hospital, removing them from the database.
//  *
//  * @param patients array of patients
//  * @param patientCount total number of patients
//  * @param patientID ID of patient to be removed
//  */
// void dischargePatient(Patient patients[], const int *patientCount, int patientID)
// {
//     int found = 0;
//
//     for (int i = 0; i < *patientCount; i++)
//     {
//         if (patients[i].patientID == patientID)
//         {
//             found = 1;
//
//             printf("Discharging Patient ID: %d (%s)...\n", patients[i].patientID, patients[i].name);
//
//             // Shift records to fill the gap left by the discharged patient
//             for (int j = i; j < *patientCount - 1; j++)
//             {
//                 patients[j] = patients[j + 1];
//             }
//
//             printf("Patient ID %d successfully discharged.\n", patientID);
//             break;
//         }
//     }
//
//     if (!found)
//     {
//         printf("Patient with ID %d not found.\n", patientID);
//     }
//     waitForUser();
// }
//
// /**
//  * Enters the doctor scheduling system, which allows users to add doctors to shifts,
//  * and display the current shift schedule for the week.
//  *
//  * @param doctorSchedule the array for the doctor schedule
//  */
// void manageDoctorSchedules(int doctorSchedule[7][3])
// {
//     int choice;
//
//     while (1)
//     {
//         // Display the menu
//         printf("\nDoctor Scheduling\n");
//         printf("1. Assign Doctors To Shift\n");
//         printf("2. View Doctor Schedule\n");
//         printf("3. Exit\n");
//         printf("Enter your choice: ");
//
//         scanf("%d", &choice);
//         clearBuffer();
//         switch (choice)
//         {
//             case 1:
//                 assignDoctors(doctorSchedule);
//                 break;
//             case 2:
//                 displayDoctorSchedule(doctorSchedule);
//                 break;
//             case 3:
//                 printf("Exiting the system...\n");
//                 return;
//             default:
//                 printf("Invalid choice. Please try again.\n");
//         }
//     }
// }
//
// /**
//  * A helper function to assign doctors to certain days and shifts.
//  *
//  * @param doctorSchedule the array for the doctor schedule
//  */
// void assignDoctors(int doctorSchedule[7][3])
// {
//     int choice;
//
//     do
//     {
//         int dayChoice, shiftChoice, doctorsToAdd;
//
//         // Day selection with input validation
//         do
//         {
//             printf("\nSelect the day to assign (1-7):\n");
//             printf("(1) Monday\n(2) Tuesday\n(3) Wednesday\n(4) Thursday\n");
//             printf("(5) Friday\n(6) Saturday\n(7) Sunday\n");
//             printf("Enter your choice: ");
//             if (scanf("%d", &dayChoice) != 1 || dayChoice < 1 || dayChoice > 7)
//             {
//                 printf("Invalid input. Please enter a number between 1 and 7.\n");
//                 clearBuffer();
//             } else
//             {
//                 break;
//             }
//         } while (1);
//
//         // Shift selection with input validation
//         do
//         {
//             printf("\nSelect the shift to assign (1-3):\n");
//             printf("(1) Morning\n(2) Afternoon\n(3) Evening\n");
//             printf("Enter your choice: ");
//             if (scanf("%d", &shiftChoice) != 1 || shiftChoice < 1 || shiftChoice > 3)
//             {
//                 printf("Invalid input. Please enter a number between 1 and 3.\n");
//                 clearBuffer();
//             } else
//             {
//                 break;
//             }
//         } while (1);
//
//         // Number of doctors input validation
//         do
//         {
//             printf("\nHow many doctors would you like to assign to this shift? ");
//             if (scanf("%d", &doctorsToAdd) != 1 || doctorsToAdd < 0)
//             {
//                 printf("Invalid input. Please enter a valid number (0 or more).\n");
//                 clearBuffer();
//             } else
//             {
//                 break;
//             }
//         } while (1);
//
//         // Assign doctors to the selected shift
//         doctorSchedule[dayChoice - 1][shiftChoice - 1] = doctorsToAdd; //enum todo
//         printf("\nSuccessfully assigned %d doctor(s) to %s - %s shift.\n",
//                doctorsToAdd,
//                (dayChoice == 1)
//                    ? "Monday"
//                    : (dayChoice == 2)
//                          ? "Tuesday"
//                          : (dayChoice == 3)
//                                ? "Wednesday"
//                                : (dayChoice == 4)
//                                      ? "Thursday"
//                                      : (dayChoice == 5)
//                                            ? "Friday"
//                                            : (dayChoice == 6)
//                                                  ? "Saturday"
//                                                  : "Sunday",
//                (shiftChoice == 1) ? "Morning" : (shiftChoice == 2) ? "Afternoon" : "Evening");
//
//         // Ask if the user wants to continue assigning doctors
//         printf("\nWould you like to assign another shift?\n");
//         printf("(1) Yes\n(2) No\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);
//         clearBuffer();
//
//         if (choice != 1)
//         {
//             printf("Exiting assignment process...\n");
//         }
//     } while (choice == 1);
// }
//
// /**
//  * A helper function to display the entire 2-D array of the doctor schedule.
//  *
//  * @param doctorSchedule the array for the doctor schedule
//  */
// void displayDoctorSchedule(int doctorSchedule[7][3])
// {
//     printf("\t\t\t%-10s%-10s%-10s%-10s%-10s%-10s%-10s", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
//            "Saturday", "Sunday");
//
//     for (int i = 0; i < SHIFTS_IN_DAY; i++)
//     {
//         i == 0 ? printf("\nMorning\t\t") : i == 1 ? printf("\nAfternoon\t") : printf("\nEvening\t\t");
//
//         for (int j = 0; j < DAYS_IN_WEEK; j++)
//         {
//             printf("%-10d", doctorSchedule[j][i]);
//         }
//         printf("\n");
//     }
// }
//
// /**
//  * Pauses the program until the user enters an input.
//  * Used to indicate that an action has been completed, and let the user view the result.
//  */
// void waitForUser()
// {
//     printf("\nPress enter to continue.");
//     clearBuffer();
// }
//
// /**
//  * Clears the input buffer using getchar() several times.
//  */
// void clearBuffer()
// {
//     int c;
//
//     while (1)
//     {
//         c = getchar();
//         if (c == '\n' || c == EOF)
//         {
//             break;
//         }
//     }
// }




/**
 * @author Cole Campbell
 * @author Jonah Botelho
 * Phase 2 Enhancements:
 * - Dynamic memory allocation
 * - File handling for persistence
 * - Linked list implementation
 * - Reporting features
 * - Enhanced error handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2
#define MAX_CHARS_IN_NAME 100
#define MAX_CHARS_IN_DIAGNOSIS 200
#define MIN_AGE 0
#define MAX_AGE 150
#define DAYS_IN_WEEK 7
#define SHIFTS_IN_DAY 3
#define FILENAME_PATIENTS "patients.dat"
#define FILENAME_SCHEDULE "schedule.dat"

typedef struct PatientNode {
    int patientID;
    char name[MAX_CHARS_IN_NAME];
    int age;
    char diagnosis[MAX_CHARS_IN_DIAGNOSIS];
    int roomNumber;
    struct PatientNode* next;
} PatientNode;

typedef struct {
    PatientNode* head;
    int count;
} PatientList;

typedef struct {
    int doctorSchedule[DAYS_IN_WEEK][SHIFTS_IN_DAY];
} DoctorSchedule;

void initPatientList(PatientList* list);
int addPatient(PatientList* list);
void displayPatients(const PatientList* list);
PatientNode* searchPatient(const PatientList* list, int patientID);
void dischargePatient(PatientList* list, int patientID);
void manageDoctorSchedules(DoctorSchedule* schedule);
void assignDoctors(DoctorSchedule* schedule);
void displayDoctorSchedule(const DoctorSchedule* schedule);
void generateReports(const PatientList* list, const DoctorSchedule* schedule);
void saveData(const PatientList* list, const DoctorSchedule* schedule);
int loadData(PatientList* list, DoctorSchedule* schedule);
void freePatientList(PatientList* list);
void clearBuffer();
void waitForUser();

int main() {
    PatientList patients;
    DoctorSchedule schedule;
    int choice;

    initPatientList(&patients);

    // Load existing data
    if (loadData(&patients, &schedule)) {
        printf("Loaded existing data successfully.\n");
    } else {
        printf("No existing data found or error loading. Starting with empty system.\n");
    }

    while (1) {
        printf("\nHospital Management System\n");
        printf("1. Add Patient Record\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient By ID\n");
        printf("4. Discharge Patient\n");
        printf("5. Manage Doctor Schedules\n");
        printf("6. Generate Reports\n");
        printf("7. Save and Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addPatient(&patients);
                break;
            case 2:
                displayPatients(&patients);
                break;
            case 3: {
                int patientID;
                printf("Enter Patient ID to search: ");
                scanf("%d", &patientID);
                clearBuffer();
                PatientNode* found = searchPatient(&patients, patientID);
                if (found) {
                    printf("\nPatient found:\n");
                    printf("ID: %d\nName: %s\nAge: %d\nDiagnosis: %s\nRoom: %d\n",
                           found->patientID, found->name, found->age,
                           found->diagnosis, found->roomNumber);
                } else {
                    printf("Patient not found.\n");
                }
                waitForUser();
                break;
            }
            case 4: {
                int patientID;
                printf("Enter Patient ID to discharge: ");
                scanf("%d", &patientID);
                clearBuffer();
                dischargePatient(&patients, patientID);
                waitForUser();
                break;
            }
            case 5:
                manageDoctorSchedules(&schedule);
                break;
            case 6:
                generateReports(&patients, &schedule);
                waitForUser();
                break;
            case 7:
                saveData(&patients, &schedule);
                freePatientList(&patients);
                printf("Data saved. Exiting the system...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void initPatientList(PatientList* list) {
    list->head = NULL;
    list->count = 0;
}

int addPatient(PatientList* list) {
    PatientNode* newNode = (PatientNode*)malloc(sizeof(PatientNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d", &newNode->patientID);
    clearBuffer();

    // Check if ID already exists
    if (searchPatient(list, newNode->patientID)) {
        printf("Patient ID already exists.\n");
        free(newNode);
        return -1;
    }

    printf("Enter Patient name: ");
    fgets(newNode->name, MAX_CHARS_IN_NAME, stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0';

    printf("Enter Patient age: ");
    while (scanf("%d", &newNode->age) != 1 || newNode->age < MIN_AGE || newNode->age > MAX_AGE) {
        printf("Invalid age. Please enter a valid age (%d-%d): ", MIN_AGE, MAX_AGE);
        clearBuffer();
    }
    clearBuffer();

    printf("Enter Patient diagnosis: ");
    fgets(newNode->diagnosis, MAX_CHARS_IN_DIAGNOSIS, stdin);
    newNode->diagnosis[strcspn(newNode->diagnosis, "\n")] = '\0';

    printf("Enter Patient room number: ");
    while (scanf("%d", &newNode->roomNumber) != 1 || newNode->roomNumber <= 0) {
        printf("Invalid room number. Please enter a positive number: ");
        clearBuffer();
    }
    clearBuffer();

    // Add to front of list
    newNode->next = list->head;
    list->head = newNode;
    list->count++;

    printf("Patient added successfully.\n");
    waitForUser();
    return 0;
}

void displayPatients(const PatientList* list) {
    if (list->count == 0) {
        printf("No patients in the system.\n");
        return;
    }

    printf("\n%-10s%-20s%-10s%-20s%-10s\n", "ID", "Name", "Age", "Diagnosis", "Room");
    PatientNode* current = list->head;
    while (current != NULL) {
        printf("%-10d%-20s%-10d%-20s%-10d\n",
               current->patientID, current->name, current->age,
               current->diagnosis, current->roomNumber);
        current = current->next;
    }
}

PatientNode* searchPatient(const PatientList* list, int patientID) {
    PatientNode* current = list->head;
    while (current != NULL) {
        if (current->patientID == patientID) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void dischargePatient(PatientList* list, int patientID) {
    PatientNode *current = list->head, *prev = NULL;

    while (current != NULL && current->patientID != patientID) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Patient with ID %d not found.\n", patientID);
        return;
    }

    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    printf("Discharged patient %d: %s\n", current->patientID, current->name);
    free(current);
    list->count--;
}

void manageDoctorSchedules(DoctorSchedule* schedule) {
    int choice;
    while (1) {
        printf("\nDoctor Scheduling\n");
        printf("1. Assign Doctors To Shift\n");
        printf("2. View Doctor Schedule\n");
        printf("3. Return to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                assignDoctors(schedule);
                break;
            case 2:
                displayDoctorSchedule(schedule);
                waitForUser();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void assignDoctors(DoctorSchedule* schedule) {
    int dayChoice, shiftChoice, doctorsToAdd, choice;

    do {
        printf("\nSelect the day to assign (1-7):\n");
        printf("(1) Monday\n(2) Tuesday\n(3) Wednesday\n(4) Thursday\n");
        printf("(5) Friday\n(6) Saturday\n(7) Sunday\n");
        printf("Enter your choice: ");
        if (scanf("%d", &dayChoice) != 1 || dayChoice < 1 || dayChoice > 7) {
            printf("Invalid input. Please enter a number between 1 and 7.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        printf("\nSelect the shift to assign (1-3):\n");
        printf("(1) Morning\n(2) Afternoon\n(3) Evening\n");
        printf("Enter your choice: ");
        if (scanf("%d", &shiftChoice) != 1 || shiftChoice < 1 || shiftChoice > 3) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        printf("\nHow many doctors would you like to assign to this shift? ");
        if (scanf("%d", &doctorsToAdd) != 1 || doctorsToAdd < 0) {
            printf("Invalid input. Please enter a valid number (0 or more).\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        schedule->doctorSchedule[dayChoice - 1][shiftChoice - 1] = doctorsToAdd;
        printf("\nSuccessfully assigned %d doctor(s) to %s - %s shift.\n",
               doctorsToAdd,
               (dayChoice == 1) ? "Monday" : (dayChoice == 2) ? "Tuesday" :
               (dayChoice == 3) ? "Wednesday" : (dayChoice == 4) ? "Thursday" :
               (dayChoice == 5) ? "Friday" : (dayChoice == 6) ? "Saturday" : "Sunday",
               (shiftChoice == 1) ? "Morning" : (shiftChoice == 2) ? "Afternoon" : "Evening");

        printf("\nAssign another shift? (1=Yes, 0=No): ");
        scanf("%d", &choice);
        clearBuffer();
    } while (choice == 1);
}

void displayDoctorSchedule(const DoctorSchedule* schedule) {
    printf("\n\t\tWeekly Doctor Schedule\n");
    printf("\t\t\t%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
           "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun");

    printf("Morning\t\t");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%-10d", schedule->doctorSchedule[i][0]);
    }

    printf("\nAfternoon\t");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%-10d", schedule->doctorSchedule[i][1]);
    }

    printf("\nEvening\t\t");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%-10d", schedule->doctorSchedule[i][2]);
    }
    printf("\n");
}

void generateReports(const PatientList* list, const DoctorSchedule* schedule) {
    printf("\nGenerating Reports...\n");

    // Patient count report
    printf("\nPatient Report:\n");
    printf("Total patients: %d\n", list->count);

    // Doctor schedule summary
    printf("\nDoctor Schedule Summary:\n");
    int totalShifts = 0;
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        for (int j = 0; j < SHIFTS_IN_DAY; j++) {
            totalShifts += schedule->doctorSchedule[i][j];
        }
    }
    printf("Total doctor shifts scheduled this week: %d\n", totalShifts);

    // Save reports to files
    FILE* patientReport = fopen("patient_report.txt", "w");
    if (patientReport) {
        fprintf(patientReport, "Patient Report\n");
        fprintf(patientReport, "Total patients: %d\n", list->count);
        fprintf(patientReport, "\n%-10s%-20s%-10s%-20s%-10s\n", "ID", "Name", "Age", "Diagnosis", "Room");

        PatientNode* current = list->head;
        while (current != NULL) {
            fprintf(patientReport, "%-10d%-20s%-10d%-20s%-10d\n",
                   current->patientID, current->name, current->age,
                   current->diagnosis, current->roomNumber);
            current = current->next;
        }
        fclose(patientReport);
        printf("Patient report saved to patient_report.txt\n");
    }

    FILE* scheduleReport = fopen("schedule_report.txt", "w");
    if (scheduleReport) {
        fprintf(scheduleReport, "Doctor Schedule Report\n");
        fprintf(scheduleReport, "Total shifts scheduled: %d\n", totalShifts);
        fprintf(scheduleReport, "\nDaily Breakdown:\n");

        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            const char* day = (i == 0) ? "Monday" : (i == 1) ? "Tuesday" :
                             (i == 2) ? "Wednesday" : (i == 3) ? "Thursday" :
                             (i == 4) ? "Friday" : (i == 5) ? "Saturday" : "Sunday";
            fprintf(scheduleReport, "%s: M=%d, A=%d, E=%d\n", day,
                    schedule->doctorSchedule[i][0],
                    schedule->doctorSchedule[i][1],
                    schedule->doctorSchedule[i][2]);
        }
        fclose(scheduleReport);
        printf("Schedule report saved to schedule_report.txt\n");
    }
}

void saveData(const PatientList* list, const DoctorSchedule* schedule) {
    FILE* patientFile = fopen(FILENAME_PATIENTS, "wb");
    if (!patientFile) {
        printf("Error saving patient data.\n");
        return;
    }

    PatientNode* current = list->head;
    while (current != NULL) {
        fwrite(current, sizeof(PatientNode), 1, patientFile);
        current = current->next;
    }
    fclose(patientFile);

    FILE* scheduleFile = fopen(FILENAME_SCHEDULE, "wb");
    if (!scheduleFile) {
        printf("Error saving schedule data.\n");
        return;
    }
    fwrite(schedule, sizeof(DoctorSchedule), 1, scheduleFile);
    fclose(scheduleFile);

    printf("Data saved successfully.\n");
}

int loadData(PatientList* list, DoctorSchedule* schedule) {
    FILE* patientFile = fopen(FILENAME_PATIENTS, "rb");
    if (!patientFile) {
        return 0;
    }

    PatientNode tempNode;
    while (fread(&tempNode, sizeof(PatientNode), 1, patientFile)) {
        PatientNode* newNode = (PatientNode*)malloc(sizeof(PatientNode));
        if (!newNode) {
            fclose(patientFile);
            return 0;
        }
        *newNode = tempNode;
        newNode->next = list->head;
        list->head = newNode;
        list->count++;
    }
    fclose(patientFile);

    FILE* scheduleFile = fopen(FILENAME_SCHEDULE, "rb");
    if (!scheduleFile) {
        return list->count > 0; // Return true if at least patients were loaded
    }
    fread(schedule, sizeof(DoctorSchedule), 1, scheduleFile);
    fclose(scheduleFile);

    return 1;
}

void freePatientList(PatientList* list) {
    PatientNode* current = list->head;
    while (current != NULL) {
        PatientNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->count = 0;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void waitForUser() {
    printf("\nPress Enter to continue...");
    clearBuffer();
}
