/**
 * @author Cole Campbell
 * @author Jonah Botelho
 * Phase 2 Enhancements:
 * - Dynamic memory allocation
 * - File handling for persistence
 * - Linked list implementation
 * - Reporting features
 * - Enhanced error handling
 * Phase 3 (User Request):
 * - Added dateDischarged field
 * - Integrated dateAdmitted and dateDischarged into display, search, reports
 * - Modified dischargePatient to mark patient rather than delete node
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
#define DATE_BUFFER_SIZE 20 // Buffer for formatting time_t to string (e.g., "YYYY-MM-DD HH:MM")

// --- Struct Definitions ---
typedef struct PatientNode {
    int patientID;
    char name[MAX_CHARS_IN_NAME];
    int age;
    char diagnosis[MAX_CHARS_IN_DIAGNOSIS];
    int roomNumber;
    time_t dateAdmitted;
    time_t dateDischarged; // NEW: Added discharge date
    struct PatientNode* next;
} PatientNode;

typedef struct {
    PatientNode* head;
    int count; // Tracks total number of patient records (including discharged)
} PatientList;

typedef struct {
    int doctorSchedule[DAYS_IN_WEEK][SHIFTS_IN_DAY];
} DoctorSchedule;

// --- Function Prototypes ---
void initPatientList(PatientList* list);
int addPatient(PatientList* list);
void displayPatients(const PatientList* list);
PatientNode* searchPatient(const PatientList* list, int patientID);
void dischargePatient(PatientList* list, int patientID); // Logic changed
void manageDoctorSchedules(DoctorSchedule* schedule);
void assignDoctors(DoctorSchedule* schedule);
void displayDoctorSchedule(const DoctorSchedule* schedule);
void generateReports(const PatientList* list, const DoctorSchedule* schedule);
void saveData(const PatientList* list, const DoctorSchedule* schedule);
int loadData(PatientList* list, DoctorSchedule* schedule);
void freePatientList(PatientList* list);
void clearBuffer();
void waitForUser();
void formatTime(time_t rawTime, char* buffer, size_t bufferSize);

// --- Main Function ---
int main() {
    PatientList patients;
    DoctorSchedule schedule;
    int choice;

    initPatientList(&patients);

    // Initialize schedule if no data is loaded
    memset(&schedule, 0, sizeof(DoctorSchedule));

    // Load existing data
    if (loadData(&patients, &schedule)) {
        printf("Loaded existing data successfully.\n");
    } else {
        printf("No existing data found or error loading. Starting with empty system.\n");
    }

    while (1) {
        printf("\nHospital Management System\n");
        printf("1. Add Patient Record\n");
        printf("2. View All Patients (Active & Discharged)\n");
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
        clearBuffer(); // Clear buffer after scanf

        switch (choice) {
            case 1:
                addPatient(&patients);
                break;
            case 2:
                displayPatients(&patients);
                waitForUser(); // Moved waitForUser here for consistency
                break;
            case 3: {
                int patientID;
                printf("Enter Patient ID to search: ");
                 if (scanf("%d", &patientID) != 1) {
                    printf("Invalid ID format.\n");
                    clearBuffer();
                    break;
                 }
                clearBuffer();
                PatientNode* found = searchPatient(&patients, patientID);
                if (found) {
                    char admittedStr[DATE_BUFFER_SIZE];
                    char dischargedStr[DATE_BUFFER_SIZE];

                    formatTime(found->dateAdmitted, admittedStr, sizeof(admittedStr));
                    if (found->dateDischarged != 0) {
                         formatTime(found->dateDischarged, dischargedStr, sizeof(dischargedStr));
                    } else {
                        snprintf(dischargedStr, sizeof(dischargedStr), "N/A");
                    }

                    printf("\nPatient found:\n");
                    printf("  ID         : %d\n", found->patientID);
                    printf("  Name       : %s\n", found->name);
                    printf("  Age        : %d\n", found->age);
                    printf("  Diagnosis  : %s\n", found->diagnosis);
                    printf("  Room       : %d\n", found->roomNumber);
                    printf("  Admitted   : %s\n", admittedStr);
                    printf("  Discharged : %s\n", dischargedStr);

                } else {
                    printf("Patient with ID %d not found.\n", patientID);
                }
                waitForUser();
                break;
            }
            case 4: {
                int patientID;
                printf("Enter Patient ID to discharge: ");
                 if (scanf("%d", &patientID) != 1) {
                    printf("Invalid ID format.\n");
                    clearBuffer();
                    break;
                 }
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
                waitForUser(); // Add delay for invalid choice too
        }
    }
}

// --- Helper Functions ---

void formatTime(time_t rawTime, char* buffer, size_t bufferSize) {
    if (rawTime == 0) { // Handle cases where date might be uninitialized or explicitly zero
        snprintf(buffer, bufferSize, "N/A");
        return;
    }
    struct tm * timeinfo;
    timeinfo = localtime(&rawTime);
    if (timeinfo) {
        strftime(buffer, bufferSize, "%Y-%m-%d %H:%M", timeinfo);
    } else {
        snprintf(buffer, bufferSize, "Invalid Time");
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void waitForUser() {
    printf("\nPress Enter to continue...");
    // Read characters until a newline or EOF is encountered
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // If the buffer was already empty (e.g., after a previous clearBuffer),
    // getchar() will wait for input, achieving the desired pause.
}


// --- Patient List Functions ---

void initPatientList(PatientList* list) {
    list->head = NULL;
    list->count = 0;
}

int addPatient(PatientList* list) {
    PatientNode* newNode = (PatientNode*)malloc(sizeof(PatientNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return -1; // Indicate failure
    }

    printf("\nEnter Patient ID: ");
    // Input validation for ID
    while (scanf("%d", &newNode->patientID) != 1 || newNode->patientID <= 0) {
         printf("Invalid ID. Please enter a positive integer: ");
         clearBuffer();
    }
    clearBuffer();

    // Check if ID already exists
    if (searchPatient(list, newNode->patientID)) {
        printf("Patient ID %d already exists. Cannot add duplicate.\n", newNode->patientID);
        free(newNode);
        waitForUser();
        return -1; // Indicate failure
    }

    printf("Enter Patient name: ");
    fgets(newNode->name, MAX_CHARS_IN_NAME, stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Patient age: ");
    while (scanf("%d", &newNode->age) != 1 || newNode->age < MIN_AGE || newNode->age > MAX_AGE) {
        printf("Invalid age. Please enter a valid age (%d-%d): ", MIN_AGE, MAX_AGE);
        clearBuffer();
    }
    clearBuffer();

    printf("Enter Patient diagnosis: ");
    fgets(newNode->diagnosis, MAX_CHARS_IN_DIAGNOSIS, stdin);
    newNode->diagnosis[strcspn(newNode->diagnosis, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Patient room number: ");
    while (scanf("%d", &newNode->roomNumber) != 1 || newNode->roomNumber <= 0) {
        printf("Invalid room number. Please enter a positive number: ");
        clearBuffer();
    }
    clearBuffer();

    newNode->dateAdmitted = time(NULL); // Set admission time to now
    newNode->dateDischarged = 0; // Initialize discharge time to 0 (meaning not discharged)

    // Add to front of list
    newNode->next = list->head;
    list->head = newNode;
    list->count++; // Increment total count

    printf("Patient added successfully.\n");
    waitForUser();
    return 0; // Indicate success
}

void displayPatients(const PatientList* list) {
     if (list->head == NULL) { // Check head directly, count might be non-zero if loaded then all discharged/removed previously incorrectly
        printf("\nNo patient records in the system.\n");
        return;
    }

    printf("\n--- Patient List ---\n");
    printf("%-8s %-20s %-5s %-25s %-8s %-17s %-17s\n",
           "ID", "Name", "Age", "Diagnosis", "Room", "Admitted", "Discharged");
    printf("----------------------------------------------------------------------------------------------------------\n");

    PatientNode* current = list->head;
    int displayedCount = 0;
    char admittedStr[DATE_BUFFER_SIZE];
    char dischargedStr[DATE_BUFFER_SIZE];

    while (current != NULL) {
        formatTime(current->dateAdmitted, admittedStr, sizeof(admittedStr));

        if (current->dateDischarged != 0) {
            formatTime(current->dateDischarged, dischargedStr, sizeof(dischargedStr));
        } else {
            snprintf(dischargedStr, sizeof(dischargedStr), "N/A");
        }

        printf("%-8d %-20.20s %-5d %-25.25s %-8d %-17s %-17s\n",
               current->patientID,
               current->name,
               current->age,
               current->diagnosis,
               current->roomNumber,
               admittedStr,
               dischargedStr);
        current = current->next;
        displayedCount++;
    }
     if (displayedCount == 0) { // Should ideally not happen if list->head wasn't NULL, but good failsafe
         printf("No patient records found to display.\n");
     }
     printf("----------------------------------------------------------------------------------------------------------\n");
     printf("Total records displayed: %d\n", displayedCount);

}

PatientNode* searchPatient(const PatientList* list, int patientID) {
    PatientNode* current = list->head;
    while (current != NULL) {
        if (current->patientID == patientID) {
            return current; // Found
        }
        current = current->next;
    }
    return NULL; // Not found
}

void dischargePatient(PatientList* list, int patientID) {
    PatientNode *patient = searchPatient(list, patientID);

    if (patient == NULL) {
        printf("Patient with ID %d not found.\n", patientID);
        return;
    }

    // Check if already discharged
    if (patient->dateDischarged != 0) {
        char dischargedStr[DATE_BUFFER_SIZE];
        formatTime(patient->dateDischarged, dischargedStr, sizeof(dischargedStr));
        printf("Patient %d (%s) is already discharged on %s.\n",
               patient->patientID, patient->name, dischargedStr);
        return;
    }

    // Mark as discharged
    patient->dateDischarged = time(NULL);
    char dischargedStr[DATE_BUFFER_SIZE];
    formatTime(patient->dateDischarged, dischargedStr, sizeof(dischargedStr));

    printf("Patient %d (%s) marked as discharged on %s.\n",
           patient->patientID, patient->name, dischargedStr);
    // We keep the node in the list to retain the record.
    // list->count remains the same as it tracks total records.
}


// --- Doctor Schedule Functions ---

void manageDoctorSchedules(DoctorSchedule* schedule) {
    int choice;
    while (1) {
        printf("\n--- Doctor Scheduling ---\n");
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
                return; // Exit this submenu
            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
        }
    }
}

void assignDoctors(DoctorSchedule* schedule) {
    int dayChoice, shiftChoice, doctorsToAdd, choice = 1; // Initialize choice to enter loop

    do {
        printf("\nSelect the day to assign (1-7):\n");
        printf(" (1) Mon (2) Tue (3) Wed (4) Thu (5) Fri (6) Sat (7) Sun\n");
        printf("Enter your choice: ");
        if (scanf("%d", &dayChoice) != 1 || dayChoice < 1 || dayChoice > DAYS_IN_WEEK) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", DAYS_IN_WEEK);
            clearBuffer();
            continue;
        }
        clearBuffer();

        printf("\nSelect the shift to assign (1-3):\n");
        printf(" (1) Morning (2) Afternoon (3) Evening\n");
        printf("Enter your choice: ");
        if (scanf("%d", &shiftChoice) != 1 || shiftChoice < 1 || shiftChoice > SHIFTS_IN_DAY) {
            printf("Invalid input. Please enter a number between 1 and %d.\n", SHIFTS_IN_DAY);
            clearBuffer();
            continue;
        }
        clearBuffer();

        printf("\nEnter number of doctors for this shift (current: %d): ",
               schedule->doctorSchedule[dayChoice - 1][shiftChoice - 1]);
        if (scanf("%d", &doctorsToAdd) != 1 || doctorsToAdd < 0) {
            printf("Invalid input. Please enter a non-negative number.\n");
            clearBuffer();
            continue; // Ask again for doctors count
        }
        clearBuffer();

        schedule->doctorSchedule[dayChoice - 1][shiftChoice - 1] = doctorsToAdd;
        printf("Successfully set %d doctor(s) for Day %d, Shift %d.\n",
               doctorsToAdd, dayChoice, shiftChoice);

        printf("\nAssign another shift? (1=Yes, 0=No): ");
        if (scanf("%d", &choice) != 1) {
            choice = 0; // Default to No on invalid input
        }
        clearBuffer();
    } while (choice == 1);
}

void displayDoctorSchedule(const DoctorSchedule* schedule) {
    const char* days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    const char* shifts[] = {"Morning", "Afternoon", "Evening"};

    printf("\n--- Weekly Doctor Schedule ---\n");
    printf("%-12s", ""); // Indent for shift names
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%-6s", days[i]);
    }
    printf("\n----------------------------------------------------\n");

    for (int j = 0; j < SHIFTS_IN_DAY; j++) {
        printf("%-12s", shifts[j]);
        for (int i = 0; i < DAYS_IN_WEEK; i++) {
            printf("%-6d", schedule->doctorSchedule[i][j]);
        }
        printf("\n");
    }
     printf("----------------------------------------------------\n");
}


// --- Reporting Function ---

void generateReports(const PatientList* list, const DoctorSchedule* schedule) {
    printf("\n--- Generating Reports ---\n");
    char admittedStr[DATE_BUFFER_SIZE];
    char dischargedStr[DATE_BUFFER_SIZE];
    int activePatientCount = 0;
    int dischargedPatientCount = 0;

    // --- Console Summary ---
    printf("\nPatient Summary:\n");
    PatientNode* counterNode = list->head;
    while(counterNode != NULL) {
        if (counterNode->dateDischarged == 0) {
            activePatientCount++;
        } else {
            dischargedPatientCount++;
        }
        counterNode = counterNode->next;
    }
    printf("  Total Patient Records: %d\n", list->count);
    printf("  Currently Admitted   : %d\n", activePatientCount);
    printf("  Discharged           : %d\n", dischargedPatientCount);


    printf("\nDoctor Schedule Summary:\n");
    int totalDoctorShifts = 0;
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        for (int j = 0; j < SHIFTS_IN_DAY; j++) {
            totalDoctorShifts += schedule->doctorSchedule[i][j];
        }
    }
    printf("  Total doctor shifts scheduled this week: %d\n", totalDoctorShifts);

    // --- File Reports ---

    // Patient Report File
    FILE* patientReportFile = fopen("patient_report.txt", "w");
    if (!patientReportFile) {
        printf("Error: Could not open patient_report.txt for writing.\n");
    } else {
        fprintf(patientReportFile, "--- Patient Report ---\n\n");
        fprintf(patientReportFile, "Total Records: %d (Active: %d, Discharged: %d)\n\n", list->count, activePatientCount, dischargedPatientCount);
        fprintf(patientReportFile, "%-8s %-20s %-5s %-25s %-8s %-17s %-17s\n",
               "ID", "Name", "Age", "Diagnosis", "Room", "Admitted", "Discharged");
        fprintf(patientReportFile, "----------------------------------------------------------------------------------------------------------\n");

        PatientNode* current = list->head;
        while (current != NULL) {
            formatTime(current->dateAdmitted, admittedStr, sizeof(admittedStr));
            if (current->dateDischarged != 0) {
                 formatTime(current->dateDischarged, dischargedStr, sizeof(dischargedStr));
            } else {
                snprintf(dischargedStr, sizeof(dischargedStr), "N/A");
            }

            fprintf(patientReportFile, "%-8d %-20.20s %-5d %-25.25s %-8d %-17s %-17s\n",
                   current->patientID, current->name, current->age,
                   current->diagnosis, current->roomNumber,
                   admittedStr, dischargedStr);
            current = current->next;
        }
         fprintf(patientReportFile, "----------------------------------------------------------------------------------------------------------\n");
        fclose(patientReportFile);
        printf("\nPatient report saved to patient_report.txt\n");
    }

    // Schedule Report File
    FILE* scheduleReportFile = fopen("schedule_report.txt", "w");
     if (!scheduleReportFile) {
        printf("Error: Could not open schedule_report.txt for writing.\n");
    } else {
        const char* days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        fprintf(scheduleReportFile, "--- Doctor Schedule Report ---\n\n");
        fprintf(scheduleReportFile, "Total Shifts Scheduled: %d\n\n", totalDoctorShifts);
        fprintf(scheduleReportFile, "%-12s %-6s %-6s %-6s %-6s %-6s %-6s %-6s\n",
                "Shift", days[0], days[1], days[2], days[3], days[4], days[5], days[6]);
         fprintf(scheduleReportFile, "----------------------------------------------------------------\n");

        const char* shiftNames[] = {"Morning", "Afternoon", "Evening"};
        for (int j = 0; j < SHIFTS_IN_DAY; j++) {
            fprintf(scheduleReportFile, "%-12s", shiftNames[j]);
            for (int i = 0; i < DAYS_IN_WEEK; i++) {
                fprintf(scheduleReportFile, "%-6d", schedule->doctorSchedule[i][j]);
            }
            fprintf(scheduleReportFile, "\n");
        }
         fprintf(scheduleReportFile, "----------------------------------------------------------------\n");
        fclose(scheduleReportFile);
        printf("Schedule report saved to schedule_report.txt\n");
    }
}


// --- Data Persistence Functions ---

void saveData(const PatientList* list, const DoctorSchedule* schedule) {
    // Save Patients
    FILE* patientFile = fopen(FILENAME_PATIENTS, "wb");
    if (!patientFile) {
        perror("Error opening patient data file for writing");
        return;
    }

    PatientNode* current = list->head;
    int nodesWritten = 0;
    while (current != NULL) {
        // We write the node data, the 'next' pointer written is useless on load
        if (fwrite(current, sizeof(PatientNode), 1, patientFile) != 1) {
            perror("Error writing patient node data");
            break; // Stop writing if an error occurs
        }
        nodesWritten++;
        current = current->next;
    }
    fclose(patientFile);

    // Save Schedule
    FILE* scheduleFile = fopen(FILENAME_SCHEDULE, "wb");
    if (!scheduleFile) {
        perror("Error opening schedule data file for writing");
        // We still might have successfully saved patients, so don't necessarily return error overall
    } else {
        if (fwrite(schedule, sizeof(DoctorSchedule), 1, scheduleFile) != 1) {
             perror("Error writing schedule data");
        }
        fclose(scheduleFile);
    }

    printf("\nData saving process completed. %d patient records processed.\n", nodesWritten);
}

int loadData(PatientList* list, DoctorSchedule* schedule) {
    int patientsLoaded = 0;
    int scheduleLoaded = 0;

    // Load Patients
    FILE* patientFile = fopen(FILENAME_PATIENTS, "rb");
    if (patientFile) {
        PatientNode tempNode;
        // Read nodes one by one
        while (fread(&tempNode, sizeof(PatientNode), 1, patientFile) == 1) {
            PatientNode* newNode = (PatientNode*)malloc(sizeof(PatientNode));
            if (!newNode) {
                perror("Memory allocation failed during data load");
                fclose(patientFile);
                // Clean up already loaded nodes before returning error
                freePatientList(list);
                return 0; // Indicate failure
            }
            // Copy data from temp node (read from file) to newly allocated node
            *newNode = tempNode;
            // IMPORTANT: Rebuild the linked list structure, ignore tempNode.next
            newNode->next = list->head;
            list->head = newNode;
            list->count++;
            patientsLoaded++;
        }
        fclose(patientFile);
        printf("Loaded %d patient records.\n", patientsLoaded);
    } else {
         printf("Patient data file (%s) not found or could not be opened. Starting fresh.\n", FILENAME_PATIENTS);
    }


    // Load Schedule
    FILE* scheduleFile = fopen(FILENAME_SCHEDULE, "rb");
    if (scheduleFile) {
        if (fread(schedule, sizeof(DoctorSchedule), 1, scheduleFile) == 1) {
            scheduleLoaded = 1;
            printf("Loaded doctor schedule.\n");
        } else {
            perror("Error reading schedule data. Using default schedule.");
            memset(schedule, 0, sizeof(DoctorSchedule)); // Reset to default if read fails
        }
        fclose(scheduleFile);
    } else {
        printf("Schedule data file (%s) not found or could not be opened. Using default schedule.\n", FILENAME_SCHEDULE);
        memset(schedule, 0, sizeof(DoctorSchedule)); // Initialize if file doesn't exist
    }

    // Return success if either patients or schedule (or both) were found/loaded successfully
    return (patientsLoaded > 0 || scheduleLoaded);
}

// --- Memory Management ---

void freePatientList(PatientList* list) {
    PatientNode* current = list->head;
    PatientNode* nextNode;
    int freedCount = 0;
    while (current != NULL) {
        nextNode = current->next; // Store next pointer before freeing current
        free(current);
        current = nextNode;
        freedCount++;
    }
    list->head = NULL; // Reset head pointer
    list->count = 0; // Reset count
    printf("Freed %d patient nodes.\n", freedCount);
}
