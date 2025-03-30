/**
 ******************************************************************************
 * @file    linkedlist.c
 * @author  Richard Lin (HoangTM)
 * @date    02 Mar 2025
 * @brief   Implementation of linked list management functions
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
 #include "linkedlist.h"

 /****************************************************************************** 
  * CODE
  ******************************************************************************/
 /**
  * @brief Initialize the linked list
  * @param pList Pointer to the linked list
  */
 void initLinkedList(LinkedList *pList) {
     pList->pHead = NULL; /* Set head to NULL */
     pList->pTail = NULL; /* Set tail to NULL */
 }
 
 /**
  * @brief Create a new node with the given student data
  * @param student Student data to be stored in the node
  * @return Pointer to the newly created node
  */
 Node* createNode(Student student) {
     Node *newNode = (Node*)malloc(sizeof(Node));
     if (newNode == NULL) {
         printf("Memory allocation failed!\n");
         exit(1);
     }
     newNode->dataStudent = student; /* Assign student data */
     newNode->pNextNode = NULL;      /* Set next pointer to NULL */
     return newNode;
 }
 
 /**
  * @brief Add a node to the head of the linked list
  * @param pList Pointer to the linked list
  * @param pNewNode Pointer to the new node
  */
 void addHead(LinkedList *pList, Node *pNewNode) {
     if (pList->pHead == NULL) {
         pList->pHead = pNewNode; /* If list is empty, set head and tail */
         pList->pTail = pNewNode;
     } else {
         pNewNode->pNextNode = pList->pHead; /* Link new node to current head */
         pList->pHead = pNewNode;            /* Update head to new node */
     }
 }
 
 /**
  * @brief Add a node to the tail of the linked list
  * @param pList Pointer to the linked list
  * @param pNewNode Pointer to the new node
  */
 void addTail(LinkedList *pList, Node *pNewNode) {
     if (pList->pHead == NULL) {
         pList->pHead = pNewNode; /* If list is empty, set head and tail */
         pList->pTail = pNewNode;
     } else {
         pList->pTail->pNextNode = pNewNode; /* Link current tail to new node */
         pList->pTail = pNewNode;            /* Update tail to new node */
     }
 }
 
 /**
  * @brief Insert a new student before a student with a specific name
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  * @param nameTarget Name of the student to insert before
  */
 void insertBeforeStudent(LinkedList *pList, Student newStudent, const char *nameTarget) {
     Node *current = pList->pHead;
     Node *prev = NULL;
     while (current != NULL) {
         if (strcmp(current->dataStudent.nameStudent, nameTarget) == 0) {
             Node *newNode = createNode(newStudent);
             if (prev == NULL) {
                 addHead(pList, newNode); /* Insert at head if target is head */
             } else {
                 newNode->pNextNode = current; /* Link new node before target */
                 prev->pNextNode = newNode;
             }
             return;
         }
         prev = current;
         current = current->pNextNode;
     }
     printf("Student with name %s not found!\n", nameTarget);
 }
 
 /**
  * @brief Insert a new student after a student with a specific name
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  * @param nameTarget Name of the student to insert after
  */
 void insertAfterStudent(LinkedList *pList, Student newStudent, const char *nameTarget) {
     Node *current = pList->pHead;
     while (current != NULL) {
         if (strcmp(current->dataStudent.nameStudent, nameTarget) == 0) {
             Node *newNode = createNode(newStudent);
             newNode->pNextNode = current->pNextNode; /* Link new node after target */
             current->pNextNode = newNode;
             if (current == pList->pTail) {
                 pList->pTail = newNode; /* Update tail if inserted after last node */
             }
             return;
         }
         current = current->pNextNode;
     }
     printf("Student with name %s not found!\n", nameTarget);
 }
 
 /**
  * @brief Insert a new student at a specific position
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  * @param position Position to insert the student (1-based index)
  */
 void insertSpecificPosition(LinkedList *pList, Student newStudent, int position) {
     if (position < 1) {
         printf("Invalid position!\n");
         return;
     }
     if (position == 1) {
         Node *newNode = createNode(newStudent);
         addHead(pList, newNode); /* Insert at head if position is 1 */
         return;
     }
     Node *current = pList->pHead;
     for (int i = 1; i < position - 1 && current != NULL; i++) {
         current = current->pNextNode;
     }
     if (current == NULL) {
         printf("Position out of range!\n");
         return;
     }
     Node *newNode = createNode(newStudent);
     newNode->pNextNode = current->pNextNode; /* Link new node at position */
     current->pNextNode = newNode;
     if (newNode->pNextNode == NULL) {
         pList->pTail = newNode; /* Update tail if inserted at end */
     }
 }
 
 /**
  * @brief Delete the head of the linked list
  * @param pList Pointer to the linked list
  */
 void deleteHead(LinkedList *pList) {
     if (pList->pHead == NULL) {
         printf("List is empty!\n");
         return;
     }
     Node *temp = pList->pHead;
     pList->pHead = pList->pHead->pNextNode; /* Move head to next node */
     if (pList->pHead == NULL) {
         pList->pTail = NULL; /* Update tail if list becomes empty */
     }
     free(temp); /* Free memory of deleted node */
 }
 
 /**
  * @brief Delete the tail of the linked list
  * @param pList Pointer to the linked list
  */
 void deleteLast(LinkedList *pList) {
     if (pList->pHead == NULL) {
         printf("List is empty!\n");
         return;
     }
     if (pList->pHead == pList->pTail) {
         free(pList->pHead); /* Free single node if list has one node */
         pList->pHead = NULL;
         pList->pTail = NULL;
         return;
     }
     Node *current = pList->pHead;
     while (current->pNextNode != pList->pTail) {
         current = current->pNextNode;
     }
     free(pList->pTail); /* Free tail node */
     pList->pTail = current; /* Update tail */
     pList->pTail->pNextNode = NULL;
 }
 
 /**
  * @brief Delete the node before a student with a specific name
  * @param pList Pointer to the linked list
  * @param nameTarget Name of the target student
  */
 void deleteBeforeStudent(LinkedList *pList, const char *nameTarget) {
     if (pList->pHead == NULL || pList->pHead->pNextNode == NULL) {
         printf("Cannot delete before the first student!\n");
         return;
     }
     Node *current = pList->pHead;
     Node *prev = NULL;
     Node *prevPrev = NULL;
     while (current != NULL) {
         if (strcmp(current->dataStudent.nameStudent, nameTarget) == 0) {
             if (prev == pList->pHead) {
                 deleteHead(pList); /* Delete head if target is second node */
             } else if (prev != NULL) {
                 prevPrev->pNextNode = current; /* Skip node before target */
                 free(prev);
             }
             return;
         }
         prevPrev = prev;
         prev = current;
         current = current->pNextNode;
     }
     printf("Student with name %s not found!\n", nameTarget);
 }
 
 /**
  * @brief Delete the node after a student with a specific name
  * @param pList Pointer to the linked list
  * @param nameTarget Name of the target student
  */
 void deleteAfterStudent(LinkedList *pList, const char *nameTarget) {
     Node *current = pList->pHead;
     while (current != NULL) {
         if (strcmp(current->dataStudent.nameStudent, nameTarget) == 0) {
             if (current->pNextNode != NULL) {
                 Node *temp = current->pNextNode;
                 current->pNextNode = temp->pNextNode; /* Skip node after target */
                 if (temp == pList->pTail) {
                     pList->pTail = current; /* Update tail if deleted node was tail */
                 }
                 free(temp);
             } else {
                 printf("No student after %s!\n", nameTarget);
             }
             return;
         }
         current = current->pNextNode;
     }
     printf("Student with name %s not found!\n", nameTarget);
 }
 
 /**
  * @brief Delete a student at a specific position
  * @param pList Pointer to the linked list
  * @param position Position of the student to delete (1-based index)
  */
 void deleteSpecificPosition(LinkedList *pList, int position) {
     if (position < 1) {
         printf("Invalid position!\n");
         return;
     }
     if (position == 1) {
         deleteHead(pList); /* Delete head if position is 1 */
         return;
     }
     Node *current = pList->pHead;
     for (int i = 1; i < position - 1 && current != NULL; i++) {
         current = current->pNextNode;
     }
     if (current == NULL || current->pNextNode == NULL) {
         printf("Position out of range!\n");
         return;
     }
     Node *temp = current->pNextNode;
     current->pNextNode = temp->pNextNode; /* Skip node at position */
     if (temp == pList->pTail) {
         pList->pTail = current; /* Update tail if deleted node was tail */
     }
     free(temp);
 }
 
 /**
  * @brief Edit the student at the head of the linked list
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  */
 void editHead(LinkedList *pList, Student newStudent) {
     if (pList->pHead == NULL) {
         printf("List is empty!\n");
         return;
     }
     pList->pHead->dataStudent = newStudent; /* Update head data */
 }
 
 /**
  * @brief Edit the student at the tail of the linked list
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  */
 void editLast(LinkedList *pList, Student newStudent) {
     if (pList->pTail == NULL) {
         printf("List is empty!\n");
         return;
     }
     pList->pTail->dataStudent = newStudent; /* Update tail data */
 }
 
 /**
  * @brief Edit a student at a specific position
  * @param pList Pointer to the linked list
  * @param position Position of the student to edit (1-based index)
  * @param newStudent New student data
  */
 void editSpecificPosition(LinkedList *pList, int position, Student newStudent) {
     if (position < 1) {
         printf("Invalid position!\n");
         return;
     }
     Node *current = pList->pHead;
     for (int i = 1; i < position && current != NULL; i++) {
         current = current->pNextNode;
     }
     if (current == NULL) {
         printf("Position out of range!\n");
         return;
     }
     current->dataStudent = newStudent; /* Update data at position */
 }
 
 /**
  * @brief Sort the linked list by name in ascending order
  * @param pList Pointer to the linked list
  */
 void sortByNameAsc(LinkedList *pList) {
     if (pList->pHead == NULL) return;
     int swapped;
     do {
         swapped = 0;
         Node *current = pList->pHead;
         while (current->pNextNode != NULL) {
             if (strcmp(current->dataStudent.nameStudent, current->pNextNode->dataStudent.nameStudent) > 0) {
                 Student temp = current->dataStudent;
                 current->dataStudent = current->pNextNode->dataStudent; /* Swap data */
                 current->pNextNode->dataStudent = temp;
                 swapped = 1;
             }
             current = current->pNextNode;
         }
     } while (swapped);
 }
 
 /**
  * @brief Sort the linked list by name in descending order
  * @param pList Pointer to the linked list
  */
 void sortByNameDesc(LinkedList *pList) {
     if (pList->pHead == NULL) return;
     int swapped;
     do {
         swapped = 0;
         Node *current = pList->pHead;
         while (current->pNextNode != NULL) {
             if (strcmp(current->dataStudent.nameStudent, current->pNextNode->dataStudent.nameStudent) < 0) {
                 Student temp = current->dataStudent;
                 current->dataStudent = current->pNextNode->dataStudent; /* Swap data */
                 current->pNextNode->dataStudent = temp;
                 swapped = 1;
             }
             current = current->pNextNode;
         }
     } while (swapped);
 }
 
 /**
  * @brief Sort the linked list by GPA in ascending order
  * @param pList Pointer to the linked list
  */
 void sortByScoreAsc(LinkedList *pList) {
     if (pList->pHead == NULL) return;
     int swapped;
     do {
         swapped = 0;
         Node *current = pList->pHead;
         while (current->pNextNode != NULL) {
             if (current->dataStudent.GPA > current->pNextNode->dataStudent.GPA) {
                 Student temp = current->dataStudent;
                 current->dataStudent = current->pNextNode->dataStudent; /* Swap data */
                 current->pNextNode->dataStudent = temp;
                 swapped = 1;
             }
             current = current->pNextNode;
         }
     } while (swapped);
 }
 
 /**
  * @brief Sort the linked list by GPA in descending order
  * @param pList Pointer to the linked list
  */
 void sortByScoreDesc(LinkedList *pList) {
     if (pList->pHead == NULL) return;
     int swapped;
     do {
         swapped = 0;
         Node *current = pList->pHead;
         while (current->pNextNode != NULL) {
             if (current->dataStudent.GPA < current->pNextNode->dataStudent.GPA) {
                 Student temp = current->dataStudent;
                 current->dataStudent = current->pNextNode->dataStudent; /* Swap data */
                 current->pNextNode->dataStudent = temp;
                 swapped = 1;
             }
             current = current->pNextNode;
         }
     } while (swapped);
 }
 
 /**
  * @brief Sort the linked list by age in ascending order
  * @param pList Pointer to the linked list
  */
 void sortByAgeAsc(LinkedList *pList) {
     if (pList->pHead == NULL) return;
     int swapped;
     do {
         swapped = 0;
         Node *current = pList->pHead;
         while (current->pNextNode != NULL) {
             if (current->dataStudent.ageStudent > current->pNextNode->dataStudent.ageStudent) {
                 Student temp = current->dataStudent;
                 current->dataStudent = current->pNextNode->dataStudent; /* Swap data */
                 current->pNextNode->dataStudent = temp;
                 swapped = 1;
             }
             current = current->pNextNode;
         }
     } while (swapped);
 }
 
 /**
  * @brief Sort the linked list by age in descending order
  * @param pList Pointer to the linked list
  */
 void sortByAgeDesc(LinkedList *pList) {
     if (pList->pHead == NULL) return;
     int swapped;
     do {
         swapped = 0;
         Node *current = pList->pHead;
         while (current->pNextNode != NULL) {
             if (current->dataStudent.ageStudent < current->pNextNode->dataStudent.ageStudent) {
                 Student temp = current->dataStudent;
                 current->dataStudent = current->pNextNode->dataStudent; /* Swap data */
                 current->pNextNode->dataStudent = temp;
                 swapped = 1;
             }
             current = current->pNextNode;
         }
     } while (swapped);
 }
 
 /**
  * @brief Count the number of nodes in the linked list
  * @param pList Pointer to the linked list
  * @return Number of nodes in the list
  */
 int countNodes(LinkedList *pList) {
     int count = 0;
     Node *current = pList->pHead;
     while (current != NULL) {
         count++;
         current = current->pNextNode; /* Move to next node */
     }
     return count;
 }
 
 /**
 * @brief Free all nodes in the linked list
 * @param pList Pointer to the linked list
 */
void freeLinkedList(LinkedList *pList) {
    Node *current = pList->pHead;
    while (current != NULL) {
        Node *temp = current;
        current = current->pNextNode;
        free(temp); /* Free each node */
    }
    pList->pHead = NULL;
    pList->pTail = NULL;
}