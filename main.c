/**
 ******************************************************************************
 * @file    main.c
 * @author  
 * @date    02 Mar 2025
 * @brief   Main program of students data managing program
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 mhoangkma (Github)
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/****************************************************************************** 
 * INCLUDES
 ******************************************************************************/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include "linkedlist.h"
 
 /****************************************************************************** 
  * MACRO
  ******************************************************************************/
 /** @defgroup Length of name
  * @{
  */
 #define MIN_NAME_LENGTH                     (2U)
 #define MIN_ACCOUNT_LENGTH                  (6U)
 /**
  * @}
  */
 
 /** @defgroup Score range
  * @{
  */
 #define MAX_GPA_SCALE                       ((double)10U)
 #define MIN_GPA_SCALE                       (0)
 /**
  * @}
  */
 
 /** @defgroup States
  * @{
  */
 #define TRUE                                (1U)
 #define FALSE                               (0U)
 /**
  * @}
  */
 
 /** @defgroup Function-like macros
  * @{
  */
 #define IS_ALPHA(c)                         (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
 #define IS_DIGIT(c)                         ((c) >= '0' && (c) <= '9')
 /**
  * @}
  */
 
 /** @defgroup Error status
  * @{
  */
 #define ERROR_NOT_NON_NEGATIVE_INT          (3U)
 #define ERROR_NOT_REAL_NUMBER               (4U)
 #define ERROR_INVALID_NAME                  (5U)
 #define ERROR_INVALID_ACCOUNT               (6U)
 #define ERROR_EMPTY_INPUT                   (7U)
 #define ERROR_DUPLICATE_NAME                (8U)
 /**
  * @}
  */
 
 /** @defgroup String options
  * @{
  */
 #define GET_NORMAL_STRING                   (0)
 #define GET_VALID_NAME                      (1U)
 #define GET_VALID_ACCOUNT                   (2U)
 /**
  * @}
  */
 
 /****************************************************************************** 
  * DEFINITIONS
  ******************************************************************************/
 /**
  * @brief Type of errors enumeration
  */
 typedef enum {
     ERROR_NONE,                     /* No error */
     ERROR_MEMORY_ALLOCATION_FAILED, /* Memory allocation failure */
     ERROR_EMPTY_LIST_DELETION       /* Attempt to delete from empty list */
 } ErrorStatus_TypeDef;
 
 /**
  * @brief Type of main option enumeration
  */
 typedef enum {
     STUDENT_INPUT = 1,              /* Input student data */
     STUDENT_INSERT,                 /* Insert student */
     STUDENT_DELETE,                 /* Delete student */
     STUDENT_EDIT,                   /* Edit student */
     STUDENT_SORT,                   /* Sort students */
     STUDENT_OUTPUT,                 /* Output student list */
     STUDENT_SAVE_TO_FILE,           /* Save to file */
     STUDENT_EXIT_PROGRAM            /* Exit program */
 } MainOptionStatus_TypeDef;
 
 /****************************************************************************** 
  * PROTOTYPES
  ******************************************************************************/
 static void inputDataStudent(Student *pStudent);
 static void outputDataStudent(LinkedList *pList);
 static void insertMenu(void);
 static void deleteMenu(void);
 static void editMenu(void);
 static void sortMenu(void);
 static void mainMenu(void);
 static void saveToFile(LinkedList *pList, const char *filename);
 static void mainInsert(void);
 static int getInputNumber(void);
 static double getDoubleNumber(void);
 static void getInputString(char *resultString, const int option);
 static void Error_Handler(const int errorName);
 
 /****************************************************************************** 
  * VARIABLES
  ******************************************************************************/
 static int choice;                  /* User's menu choice */
 static int numberStudent;           /* Number of students to input */
 static int insertChoice;            /* Insert menu choice */
 static int deleteChoice;            /* Delete menu choice */
 static int editChoice;              /* Edit menu choice */
 static int pos;                     /* Position for insert/edit/delete */
 static char nameTarget[50];         /* Target name for insert operations */
 static char fileName[50];           /* File name for saving */
 static char nameTargetDelete[50];   /* Target name for delete operations */
 static LinkedList listStudent;      /* Linked list of students */
 static Student studentParam;        /* Temporary student data */
 
 /****************************************************************************** 
  * CODE
  ******************************************************************************/
 /**
  * @brief Main function
  * @return 0 on success
  */
 int main(void) {
     initLinkedList(&listStudent); /* Initialize the linked list */
     choice = 0;
     mainMenu(); /* Display main menu */
 
     while (choice != STUDENT_EXIT_PROGRAM) {
         if (choice < STUDENT_INPUT || choice > STUDENT_EXIT_PROGRAM) {
             printf("Invalid choice. Please enter a number between 1 and 8.\n");
             mainMenu();
             continue;
         }
         switch (choice) {
             case STUDENT_INPUT:
                 printf("\nEnter number of students: \n");
                 numberStudent = getInputNumber();
                 for (int i = 0; i < numberStudent; i++) {
                     inputDataStudent(&studentParam);
                     addTail(&listStudent, createNode(studentParam));
                 }
                 printf("\nSuccessfully added students to list.\n");
                 break;
             case STUDENT_INSERT:
                 insertMenu();
                 mainInsert();
                 break;
             case STUDENT_DELETE:
                 deleteMenu();
                 deleteChoice = getInputNumber();
                 while (deleteChoice != 7) {
                     switch (deleteChoice) {
                         case 1:
                             printf("\nDeleting student at the head of list.\n");
                             deleteHead(&listStudent);
                             printf("Successfully deleted student at the head of list.\n");
                             break;
                         case 2:
                             printf("\nDeleting student at the end of list.\n");
                             deleteLast(&listStudent);
                             printf("Successfully deleted student at the end of list.\n");
                             break;
                         case 3:
                             printf("\nEnter the name of student to delete before: ");
                             fgets(nameTargetDelete, 50, stdin);
                             nameTargetDelete[strcspn(nameTargetDelete, "\n")] = 0;
                             deleteBeforeStudent(&listStudent, nameTargetDelete);
                             printf("\nSuccessfully deleted student.\n");
                             break;
                         case 4:
                             printf("\nEnter the name of student to delete after: ");
                             fgets(nameTargetDelete, 50, stdin);
                             nameTargetDelete[strcspn(nameTargetDelete, "\n")] = 0;
                             deleteAfterStudent(&listStudent, nameTargetDelete);
                             printf("\nSuccessfully deleted student.\n");
                             break;
                         case 5:
                             printf("\nEnter position to delete: ");
                             if (scanf("%d", &pos) != 1) {
                                 printf("\nInvalid input! Please enter a number.\n");
                                 while (getchar() != '\n');
                                 break;
                             }
                             getchar();
                             int count = countNodes(&listStudent);
                             if (pos < 1 || pos > count) {
                                 printf("Invalid position!\n");
                             } else {
                                 deleteSpecificPosition(&listStudent, pos);
                                 printf("Student at position %d deleted successfully!\n", pos);
                             }
                             break;
                         case 6:
                             outputDataStudent(&listStudent);
                             break;
                         default:
                             printf("Invalid choice! Please try again.\n");
                     }
                     deleteMenu();
                     deleteChoice = getInputNumber();
                 }
                 break;
             case STUDENT_EDIT:
                 editMenu();
                 editChoice = getInputNumber();
                 while (editChoice != 5) {
                     switch (editChoice) {
                         case 1:
                             printf("\nEditing student at the head of list.\n");
                             printf("Enter new student data:\n");
                             inputDataStudent(&studentParam);
                             editHead(&listStudent, studentParam);
                             printf("Successfully edited student at the head of list.\n");
                             break;
                         case 2:
                             printf("\nEditing student at the tail of list.\n");
                             printf("Enter new student data:\n");
                             inputDataStudent(&studentParam);
                             editLast(&listStudent, studentParam);
                             printf("Successfully edited student at the tail of list.\n");
                             break;
                         case 3:
                             printf("\nEnter position to edit: ");
                             scanf("%d", &pos);
                             getchar();
                             printf("Enter student information:\n");
                             inputDataStudent(&studentParam);
                             editSpecificPosition(&listStudent, pos, studentParam);
                             printf("Successfully edited student.\n");
                             break;
                         case 4:
                             outputDataStudent(&listStudent);
                             break;
                         default:
                             printf("Invalid choice! Please try again.\n");
                     }
                     editMenu();
                     editChoice = getInputNumber();
                 }
                 break;
             case STUDENT_SORT:
                 sortMenu();
                 scanf("%d", &editChoice);
                 getchar();
                 while (editChoice != 8) {
                     switch (editChoice) {
                         case 1:
                             sortByNameAsc(&listStudent);
                             printf("Students sorted by name (A → Z) successfully!\n");
                             break;
                         case 2:
                             sortByNameDesc(&listStudent);
                             printf("Students sorted by name (Z → A) successfully!\n");
                             break;
                         case 3:
                             sortByScoreAsc(&listStudent);
                             printf("Students sorted by score (Ascending) successfully!\n");
                             break;
                         case 4:
                             sortByScoreDesc(&listStudent);
                             printf("Students sorted by score (Descending) successfully!\n");
                             break;
                         case 5:
                             sortByAgeAsc(&listStudent);
                             printf("Students sorted by age (Ascending) successfully!\n");
                             break;
                         case 6:
                             sortByAgeDesc(&listStudent);
                             printf("Students sorted by age (Descending) successfully!\n");
                             break;
                         case 7:
                             outputDataStudent(&listStudent);
                             break;
                         case 8:
                             printf("Returning to the Main Menu...\n");
                             break;
                         default:
                             printf("Invalid choice! Please try again.\n");
                     }
                     sortMenu();
                     scanf("%d", &editChoice);
                     getchar();
                 }
                 break;
             case STUDENT_OUTPUT:
                 outputDataStudent(&listStudent);
                 break;
             case STUDENT_SAVE_TO_FILE:
                 printf("Enter filename to save: ");
                 fgets(fileName, 50, stdin);
                 fileName[strcspn(fileName, "\n")] = 0;
                 saveToFile(&listStudent, fileName);
                 break;
             default:
                 printf("Invalid choice. Please enter again.\n");
         }
         mainMenu();
     }
     /* Free the linked list before exiting */
     freeLinkedList(&listStudent);
     printf("Program exited successfully. Press Enter to exit...\n");
     getchar();
     return 0;
 }
 
 /**
  * @brief Input student data from user
  * @param pStudent Pointer to student structure to store input data
  */
 static void inputDataStudent(Student *pStudent) {
     printf("\nEnter name of student: ");
     getInputString(pStudent->nameStudent, GET_VALID_NAME);
     printf("Enter age of student: ");
     pStudent->ageStudent = getInputNumber();
     printf("Enter GPA of student: ");
     pStudent->GPA = getDoubleNumber();
     while (pStudent->GPA > MAX_GPA_SCALE || pStudent->GPA < MIN_GPA_SCALE) {
         printf("Invalid GPA. Enter again!\n-----------------------------------------------------\n");
         pStudent->GPA = getDoubleNumber();
     }
     printf("\n");
 }
 
 /**
  * @brief Output all student data in the linked list
  * @param pList Pointer to the linked list
  */
 static void outputDataStudent(LinkedList *pList) {
     int countStudent = 1;
     printf("\n======================List of students=======================\n");
     printf("No.\t%-30s\t%-10s\t%-10s\n", "Name", "Age", "GPA");
     printf("=============================================================\n");
     for (Node *pTemp = pList->pHead; pTemp != NULL; pTemp = pTemp->pNextNode) {
         printf("%d\t%-30s\t%-10d\t%-10.2f\n", countStudent++,
                pTemp->dataStudent.nameStudent,
                pTemp->dataStudent.ageStudent,
                pTemp->dataStudent.GPA);
     }
 }
 
 /**
  * @brief Display insert menu
  */
 static void insertMenu(void) {
     printf("\n===== INSERT MENU =====\n"
            "1. Insert student to head of list.\n"
            "2. Insert student to tail of list.\n"
            "3. Insert new student before student.\n"
            "4. Insert new student after student.\n"
            "5. Insert new student at specific position.\n"
            "6. Output list of students\n"
            "7. Back to Main Menu\n"
            "Enter your choice: ");
 }
 
 /**
  * @brief Display delete menu
  */
 static void deleteMenu(void) {
     printf("\n===== DELETE MENU =====\n"
            "1. Delete student at head of list.\n"
            "2. Delete student at tail of list.\n"
            "3. Delete student before another student.\n"
            "4. Delete student after another student.\n"
            "5. Delete student at specific position.\n"
            "6. Output list of students\n"
            "7. Back to Main Menu\n"
            "Enter your choice: ");
 }
 
 /**
  * @brief Display edit menu
  */
 static void editMenu(void) {
     printf("\n===== EDIT MENU =====\n"
            "1. Edit student at head of list.\n"
            "2. Edit student at tail of list.\n"
            "3. Edit student at specific position.\n"
            "4. Output list of students\n"
            "5. Back to Main Menu\n"
            "Enter your choice: ");
 }
 
 /**
  * @brief Display sort menu
  */
 static void sortMenu(void) {
     printf("\n===== SORT MENU =====\n"
            "1. Sort students by name (A -> Z)\n"
            "2. Sort students by name (Z -> A)\n"
            "3. Sort students by score (Ascending)\n"
            "4. Sort students by score (Descending)\n"
            "5. Sort students by age (Ascending)\n"
            "6. Sort students by age (Descending)\n"
            "7. Output list of students\n"
            "8. Back to Main Menu\n"
            "Enter your choice: ");
 }
 
 /**
  * @brief Display main menu and get user choice
  */
 static void mainMenu(void) {
     printf("\n=================== MAIN MENU ==========================\n"
            "1. Input information of student.\n"
            "2. Insert student into list.\n"
            "3. Delete student from list.\n"
            "4. Edit student in list.\n"
            "5. Sort students in list.\n"
            "6. Output list of students.\n"
            "7. Save list to a file.\n"
            "8. Exit.\n"
            "==========================================================\n"
            "Enter your choice: ");
     choice = getInputNumber();
 }
 
 /**
  * @brief Save student data to a text file with GPA distribution
  * @param pList Pointer to the linked list
  * @param filename Name of the file to save
  */
 static void saveToFile(LinkedList *pList, const char *filename) {
     int countStudent = 1;
     int excellent = 0, good = 0, average = 0, weak = 0;
     FILE *file = fopen(filename, "w");
     if (file == NULL) {
         printf("Error opening file for writing.\n");
         return;
     }
     fprintf(file, "========================================================\n");
     fprintf(file, "| %-3s | %-50s | %-5s | %-7s |\n", "No.", "Name", "Age", "GPA");
     fprintf(file, "========================================================\n");
     for (Node *pTemp = pList->pHead; pTemp != NULL; pTemp = pTemp->pNextNode) {
         fprintf(file, "| %-3d | %-50s | %-5d | %-7.2f |\n", countStudent++,
                 pTemp->dataStudent.nameStudent,
                 pTemp->dataStudent.ageStudent,
                 pTemp->dataStudent.GPA);
         if (pTemp->dataStudent.GPA >= 3.5) excellent++;
         else if (pTemp->dataStudent.GPA >= 3.0) good++;
         else if (pTemp->dataStudent.GPA >= 2.0) average++;
         else weak++;
     }
     fprintf(file, "============================================\n\n");
     fprintf(file, "                   GPA DISTRIBUTION\n");
     fprintf(file, "========================================================\n");
     fprintf(file, "| %-54s | %-5d |\n", "Excellent (3.5 - 4.0)", excellent);
     fprintf(file, "| %-54s | %-5d |\n", "Good (3.0 - 3.49)", good);
     fprintf(file, "| %-54s | %-5d |\n", "Average (2.0 - 2.99)", average);
     fprintf(file, "| %-54s | %-5d |\n", "Weak (< 2.0)", weak);
     fprintf(file, "========================================================\n");
     fclose(file);
     printf("Data saved to %s successfully!\n", filename);
 }
 
 /**
  * @brief Handle student insertion operations
  */
 static void mainInsert(void) {
     insertChoice = getInputNumber();
     while (insertChoice != 7) {
         switch (insertChoice) {
             case 1:
                 printf("\nEnter information of student to insert at head of list\n");
                 inputDataStudent(&studentParam);
                 addHead(&listStudent, createNode(studentParam));
                 printf("Successfully inserted student to head of list.\n");
                 break;
             case 2:
                 printf("\nEnter information of student to insert at tail of list\n");
                 inputDataStudent(&studentParam);
                 addTail(&listStudent, createNode(studentParam));
                 printf("Successfully inserted student to tail of list.\n");
                 break;
             case 3:
                 printf("\nEnter the name of student to insert before: ");
                 fgets(nameTarget, 50, stdin);
                 nameTarget[strcspn(nameTarget, "\n")] = 0;
                 printf("Enter information of new student:\n");
                 inputDataStudent(&studentParam);
                 insertBeforeStudent(&listStudent, studentParam, nameTarget);
                 printf("Successfully inserted student.\n");
                 break;
             case 4:
                 printf("\nEnter the name of student to insert after: ");
                 fgets(nameTarget, 50, stdin);
                 nameTarget[strcspn(nameTarget, "\n")] = 0;
                 printf("Enter information of new student:\n");
                 inputDataStudent(&studentParam);
                 insertAfterStudent(&listStudent, studentParam, nameTarget);
                 printf("Successfully inserted student.\n");
                 break;
             case 5:
                 printf("\nEnter position to insert: ");
                 pos = getInputNumber();
                 printf("Enter student information:\n");
                 inputDataStudent(&studentParam);
                 int count = countNodes(&listStudent);
                 if (pos < 0) {
                     printf("Invalid position! Please enter a value from 1 to %d.\n", count);
                 } else {
                     insertSpecificPosition(&listStudent, studentParam, pos);
                     printf("Successfully inserted student.\n");
                 }
                 break;
             case 6:
                 outputDataStudent(&listStudent);
                 break;
             default:
                 printf("Invalid choice! Please try again.\n");
         }
         insertMenu();
         insertChoice = getInputNumber();
     }
 }
 
 /**
 * @brief Get an integer input from user
 * @return The input number
 */
 static int getInputNumber(void) {
    char inputString[50];
    unsigned int returnNum = 0;
    int isPositiveInt = FALSE;

    while (!isPositiveInt) {
        if (scanf("%49s", inputString) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        isPositiveInt = TRUE;
        for (int i = 0; inputString[i] != '\0'; i++) {
            if (!IS_DIGIT(inputString[i])) {
                printf("Invalid! Non-negative integers only\n-----------------------------------------------------\n");
                isPositiveInt = FALSE;
                break;
            }
        }
    }
    sscanf(inputString, "%u", &returnNum);
    return (int)returnNum;
}
 
 /**
  * @brief Get a double input from user
  * @return The input double number
  */
  static double getDoubleNumber(void) {
    char inputString[50];
    double returnNum = 0;
    int isDouble = FALSE;

    while (!isDouble) {
        getInputString(inputString, GET_NORMAL_STRING);
        isDouble = TRUE;
        int exponentFound = FALSE;
        int decimalFound = FALSE;
        int digitFound = FALSE;
        int signFound = (inputString[0] == '+' || inputString[0] == '-') ? 1 : 0;

        for (int i = signFound; inputString[i] != '\0' && isDouble && i < 49; i++) {
            if (IS_DIGIT(inputString[i])) {
                digitFound = TRUE;
            } else if (inputString[i] == '.') {
                if (decimalFound || exponentFound) isDouble = FALSE;
                else decimalFound = TRUE;
            } else if (inputString[i] == 'e' || inputString[i] == 'E') {
                if (exponentFound || !digitFound || i + 1 >= 49) isDouble = FALSE;
                else {
                    exponentFound = TRUE;
                    if (i + 1 < 49 && (inputString[i + 1] == '+' || inputString[i + 1] == '-')) {
                        i++;
                        if (i + 1 >= 49 || !IS_DIGIT(inputString[i + 1])) isDouble = FALSE;
                    } else if (i + 1 >= 49 || !IS_DIGIT(inputString[i + 1])) {
                        isDouble = FALSE;
                    }
                }
            } else {
                isDouble = FALSE;
            }
        }
        if (!digitFound) isDouble = FALSE;
        if (!isDouble) Error_Handler(ERROR_NOT_REAL_NUMBER);
    }

    if (sscanf(inputString, "%lf", &returnNum) != 1) {
        printf("Conversion error! Defaulting to 0.\n");
        returnNum = 0;
    }
    return returnNum;
}
 
 /**
  * @brief Get a string input from user with validation
  * @param resultString Buffer to store the input string
  * @param option Validation option (GET_NORMAL_STRING, GET_VALID_NAME, GET_VALID_ACCOUNT)
  */
  static void getInputString(char *resultString, const int option) {
    int isValid = FALSE;
    while (!isValid) {
        if (scanf("%49[^\n]", resultString) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            Error_Handler(ERROR_EMPTY_INPUT);
            continue;
        }
        resultString[49] = '\0'; // Ensure null termination

        int spaceFound = FALSE;
        int alphaFound = FALSE;
        int nameLength = 0;
        isValid = TRUE;
        for (int i = 0; resultString[i] != '\0' && isValid && i < 49; i++, nameLength++) {
            if (resultString[i] == ' ') {
                if (option == GET_VALID_ACCOUNT || (spaceFound && option == GET_VALID_NAME) || i == 0) {
                    Error_Handler(ERROR_INVALID_NAME);
                    isValid = FALSE;
                }
                spaceFound = TRUE;
            } else if (IS_ALPHA(resultString[i])) {
                spaceFound = FALSE;
                alphaFound = TRUE;
            } else if (option == GET_VALID_ACCOUNT && IS_DIGIT(resultString[i])) {
                spaceFound = FALSE;
            } else {
                // Only trigger specific errors for valid options, otherwise skip validation
                if (option == GET_VALID_NAME) {
                    Error_Handler(ERROR_INVALID_NAME);
                    isValid = FALSE;
                } else if (option == GET_VALID_ACCOUNT) {
                    Error_Handler(ERROR_INVALID_ACCOUNT);
                    isValid = FALSE;
                } else {
                    // For GET_NORMAL_STRING, allow any input but warn if invalid
                    printf("Warning: Invalid character ignored for general input.\n");
                    isValid = TRUE; // Allow the input to proceed
                }
            }
        }
        if (isValid) {
            if (option == GET_VALID_NAME && nameLength < MIN_NAME_LENGTH) {
                Error_Handler(ERROR_INVALID_NAME);
                isValid = FALSE;
            } else if (option == GET_VALID_ACCOUNT && (nameLength < MIN_ACCOUNT_LENGTH || !alphaFound)) {
                Error_Handler(ERROR_INVALID_ACCOUNT);
                isValid = FALSE;
            }
        }
        if (!isValid) {
            while (getchar() != '\n'); // Clear buffer after invalid input
        }
    }
}
 
 /**
  * @brief Handle error messages
  * @param errorName Error code
  */
 static void Error_Handler(const int errorName) {
    switch (errorName) {
        case ERROR_MEMORY_ALLOCATION_FAILED:
            printf("The program failed to allocate memory\n-----------------------------------------------------\n");
            break;
        case ERROR_EMPTY_LIST_DELETION:
            printf("There are no students in the system\n-----------------------------------------------------\n");
            break;
        case ERROR_NOT_NON_NEGATIVE_INT:
            printf("Invalid! Non-negative integers only\n-----------------------------------------------------\n");
            break;
        case ERROR_NOT_REAL_NUMBER:
            printf("Incorrect format of floating-point number\n(sign)(integer)(.)(fraction)(e)(sign)(exponent)\nExample: -3.2; -5e3; 3e-4\n-----------------------------------------------------\nPlease enter a valid number: ");
            break;
        case ERROR_INVALID_NAME:
            printf("The name you entered violates our guidelines\nYour name must:\n   * Have minimum of %u characters\n   * Not have special characters (e.g !@#$)\n   * Not have any numbers, only alphabetic characters\n   * Have no repeated spaces\n-----------------------------------------------------\nEnter student's full name: ", MIN_NAME_LENGTH);
            break;
        case ERROR_INVALID_ACCOUNT:
            printf("The account name you entered violates our guidelines\nYour account must:\n   * Have at least 1 alphabetic character\n   * Have minimum of %u characters\n   * Not have special characters (e.g !@#$)\n   * Only numbers and alphabetic characters\n   * Not have any spaces\n-----------------------------------------------------\nEnter student's account: ", MIN_ACCOUNT_LENGTH);
            break;
        case ERROR_EMPTY_INPUT:
            printf("Please enter at least one character\n-----------------------------------------------------\n");
            break;
        case ERROR_DUPLICATE_NAME:
            printf("This account name already exists. Try another one\n-----------------------------------------------------\n");
            break;
        default:
            break;
    }
}