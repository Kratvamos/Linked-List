/**
 ******************************************************************************
 * @file    linkedlist.h
 * @author  
 * @date    08 Mar 2025
 * @brief   Header file for linked list management
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

 #ifndef LINKEDLIST_H
 #define LINKEDLIST_H
 
 /****************************************************************************** 
  * INCLUDES
  ******************************************************************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 /****************************************************************************** 
  * DEFINITIONS
  ******************************************************************************/
 /**
  * @brief Student data structure
  */
 typedef struct Student {
     char nameStudent[50];  /* Student's full name */
     int ageStudent;        /* Student's age */
     float GPA;             /* Student's grade point average */
 } Student;
 
 /**
  * @brief Linked list node structure
  */
 typedef struct Node {
     Student dataStudent;   /* Student data stored in the node */
     struct Node *pNextNode; /* Pointer to the next node */
 } Node;
 
 /**
  * @brief Linked list structure
  */
 typedef struct LinkedList {
     Node *pHead;           /* Pointer to the head of the list */
     Node *pTail;           /* Pointer to the tail of the list */
 } LinkedList;
 
 /****************************************************************************** 
  * API
  ******************************************************************************/
 /**
  * @brief Initialize the linked list
  * @param pList Pointer to the linked list
  */
 void initLinkedList(LinkedList *pList);
 
 /**
  * @brief Create a new node with the given student data
  * @param student Student data to be stored in the node
  * @return Pointer to the newly created node
  */
 Node* createNode(Student student);
 
 /**
  * @brief Add a node to the head of the linked list
  * @param pList Pointer to the linked list
  * @param pNewNode Pointer to the new node
  */
 void addHead(LinkedList *pList, Node *pNewNode);
 
 /**
  * @brief Add a node to the tail of the linked list
  * @param pList Pointer to the linked list
  * @param pNewNode Pointer to the new node
  */
 void addTail(LinkedList *pList, Node *pNewNode);
 
 /**
  * @brief Insert a new student before a student with a specific name
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  * @param nameTarget Name of the student to insert before
  */
 void insertBeforeStudent(LinkedList *pList, Student newStudent, const char *nameTarget);
 
 /**
  * @brief Insert a new student after a student with a specific name
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  * @param nameTarget Name of the student to insert after
  */
 void insertAfterStudent(LinkedList *pList, Student newStudent, const char *nameTarget);
 
 /**
  * @brief Insert a new student at a specific position
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  * @param position Position to insert the student (1-based index)
  */
 void insertSpecificPosition(LinkedList *pList, Student newStudent, int position);
 
 /**
  * @brief Delete the head of the linked list
  * @param pList Pointer to the linked list
  */
 void deleteHead(LinkedList *pList);
 
 /**
  * @brief Delete the tail of the linked list
  * @param pList Pointer to the linked list
  */
 void deleteLast(LinkedList *pList);
 
 /**
  * @brief Delete the node before a student with a specific name
  * @param pList Pointer to the linked list
  * @param nameTarget Name of the target student
  */
 void deleteBeforeStudent(LinkedList *pList, const char *nameTarget);
 
 /**
  * @brief Delete the node after a student with a specific name
  * @param pList Pointer to the linked list
  * @param nameTarget Name of the target student
  */
 void deleteAfterStudent(LinkedList *pList, const char *nameTarget);
 
 /**
  * @brief Delete a student at a specific position
  * @param pList Pointer to the linked list
  * @param position Position of the student to delete (1-based index)
  */
 void deleteSpecificPosition(LinkedList *pList, int position);
 
 /**
  * @brief Edit the student at the head of the linked list
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  */
 void editHead(LinkedList *pList, Student newStudent);
 
 /**
  * @brief Edit the student at the tail of the linked list
  * @param pList Pointer to the linked list
  * @param newStudent New student data
  */
 void editLast(LinkedList *pList, Student newStudent);
 
 /**
  * @brief Edit a student at a specific position
  * @param pList Pointer to the linked list
  * @param position Position of the student to edit (1-based index)
  * @param newStudent New student data
  */
 void editSpecificPosition(LinkedList *pList, int position, Student newStudent);
 
/**
 * @brief Free all nodes in the linked list
 * @param pList Pointer to the linked list
 */
void freeLinkedList(LinkedList *pList);

 /**
  * @brief Sort the linked list by name in ascending order
  * @param pList Pointer to the linked list
  */
 void sortByNameAsc(LinkedList *pList);
 
 /**
  * @brief Sort the linked list by name in descending order
  * @param pList Pointer to the linked list
  */
 void sortByNameDesc(LinkedList *pList);
 
 /**
  * @brief Sort the linked list by GPA in ascending order
  * @param pList Pointer to the linked list
  */
 void sortByScoreAsc(LinkedList *pList);
 
 /**
  * @brief Sort the linked list by GPA in descending order
  * @param pList Pointer to the linked list
  */
 void sortByScoreDesc(LinkedList *pList);
 
 /**
  * @brief Sort the linked list by age in ascending order
  * @param pList Pointer to the linked list
  */
 void sortByAgeAsc(LinkedList *pList);
 
 /**
  * @brief Sort the linked list by age in descending order
  * @param pList Pointer to the linked list
  */
 void sortByAgeDesc(LinkedList *pList);
 
 /**
  * @brief Count the number of nodes in the linked list
  * @param pList Pointer to the linked list
  * @return Number of nodes in the list
  */
 int countNodes(LinkedList *pList);
 
 #endif /* LINKEDLIST_H */