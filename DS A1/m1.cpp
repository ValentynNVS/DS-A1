/*
* FILE : m1.cpp
* PROJECT :  Assignment 1
* PROGRAMMER : Valentyn Novosydliuk
* FIRST VERSION : 05/29/2024
* DESCRIPTION :
* This program gets user flight infomation. There is a huge use of double linked lists as well as malloc dynamic memory allocation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)
const int kMaxStrSize = 30;

void deleteNode(struct FlightNode* node, struct FlightNode* head, struct FlightNode* tail);
void InsertNewNodeFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare);
void InsertNewNodeDest(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare);
void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date, float fare);
void printFlightInfo(struct FlightNode* head);
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date);
struct FlightNode* CreateNewNode(char* destination, char* date, float fare);
int freeAllocatedMemory(struct FlightNode* head);

struct FlightInfo {
    char* destination;
    char* date;
    float fare;
};

struct FlightNode {
    struct FlightInfo flight;
    struct FlightNode* prevElement;
    struct FlightNode* nextElement;
};

int main(void) {
    struct FlightNode* headForDestinationSorted = NULL;
    struct FlightNode* tailForDestinationSorted = NULL;
    struct FlightNode* headForFareSorted = NULL;
    struct FlightNode* tailForFareSorted = NULL;

    struct FlightInfo flights = { 0 };

    for (;;) {
        char destination[kMaxStrSize] = "";
        char dateOfTheFlight[kMaxStrSize] = "";
        float fare = 0;

        printf("Enter the name of a destination of a flight\n");
        fgets(destination, kMaxStrSize, stdin);
        destination[strcspn(destination, "\n")] = '\0';
        if (strcmp(destination, ".") == 0) {
            break;
        }

        printf("Enter date for flight : \n");
        fgets(dateOfTheFlight, kMaxStrSize, stdin);
        dateOfTheFlight[strcspn(dateOfTheFlight, "\n")] = '\0';
        if (strcmp(dateOfTheFlight, ".") == 0) {
            break;
        }

        printf("Enter the fare for flight : \n");
        if (scanf("%f", &fare) != 1) {
            printf("Invalid input for fare. Please enter a valid floating-point number.\n");
            int bufferClearer;
            while ((bufferClearer = getchar()) != '\n' && bufferClearer != EOF);
            continue;
        }

        int bufferClearer;
        while ((bufferClearer = getchar()) != '\n' && bufferClearer != EOF);

        fillFlightInfo(&flights, destination, dateOfTheFlight, fare);
        InsertNewNodeFare(&headForFareSorted, &tailForFareSorted, destination, dateOfTheFlight, fare);
        InsertNewNodeDest(&headForDestinationSorted, &tailForDestinationSorted, destination, dateOfTheFlight, fare);
    }

    printf("Fares-sorted linked list:\n");
    printFlightInfo(headForFareSorted);
    printf("\nDestination-sorted linked list:\n");
    printFlightInfo(headForDestinationSorted);

    char destination[kMaxStrSize] = "";
    char dateOfTheFlight[kMaxStrSize] = "";
    /*obtaining 1 last destination and date*/
    printf("Enter the name of a last destination of a flight\n");
    fgets(destination, kMaxStrSize, stdin);
    destination[strcspn(destination, "\n")] = '\0';
    printf("Enter date for flight : \n");
    fgets(dateOfTheFlight, kMaxStrSize, stdin);
    dateOfTheFlight[strcspn(dateOfTheFlight, "\n")] = '\0';

    struct FlightNode* sameFlight = findFlight(headForDestinationSorted, destination, dateOfTheFlight);
    if (sameFlight != NULL) {
        float fare = 0;
        printf("This is the fare for this information: %.2f\n", sameFlight->flight.fare);
        printf("Please, enter a new fare: ");
        if (scanf("%f", &fare) == 1) {
            int bufferClearer;
            while ((bufferClearer = getchar()) != '\n' && bufferClearer != EOF);

            if (fare == sameFlight->flight.fare) {
                printf("The fare is the same\n");
            }
            else {
                sameFlight->flight.fare = fare;
                struct FlightNode* flightFareList = findFlight(headForFareSorted, destination, dateOfTheFlight);
                /*everything seems to work up until this part*/
                deleteNode(flightFareList, headForFareSorted, tailForFareSorted);
                InsertNewNodeFare(&headForFareSorted, &tailForFareSorted, destination, dateOfTheFlight, fare);
                /*update detanation list and then delete node from fare list and reinsert it*/
            }

        }

        printf("Fares-sorted linked list:\n");
        printFlightInfo(headForFareSorted);
        printf("\nDestination-sorted linked list:\n");
        printFlightInfo(headForDestinationSorted);
        
    }

    else if (sameFlight == NULL) {
        printf("No matching flights found");
    }

    int errorChekingForMemoryCleanUp = 0;
    errorChekingForMemoryCleanUp = freeAllocatedMemory(headForDestinationSorted);
    if (errorChekingForMemoryCleanUp == 0) {
        printf("Memory could not be freed\n");
    }
    errorChekingForMemoryCleanUp = freeAllocatedMemory(headForFareSorted);
    if (errorChekingForMemoryCleanUp == 0) {
        printf("Memory could not be freed\n");
    }
    return 0;
}

/*
Function: CreateNewNode
Parameters: char* destination - pointer to the destination string for the flight
            char* date - pointer to the date string for the flight
            float fare - the fare for the flight
Description: This function creates a new flight node, allocates memory for the destination and date strings,
             and initializes the flight information.
Return value: struct FlightNode* - pointer to the newly created flight node
*/
struct FlightNode* CreateNewNode(char* destination, char* date, float fare) {
    struct FlightNode* newFlight = (struct FlightNode*)malloc(sizeof(struct FlightNode));

    if (newFlight == NULL) {
        printf("No more memory available!!!\n");
        exit(EXIT_FAILURE);
    }

    newFlight->flight.destination = (char*)malloc(strlen(destination) + 1);
    newFlight->flight.date = (char*)malloc(strlen(date) + 1);
    if (newFlight->flight.destination == NULL || newFlight->flight.date == NULL) {
        printf("No more memory available!!!\n");
        free(newFlight->flight.destination);
        free(newFlight->flight.date);
        free(newFlight);
        exit(EXIT_FAILURE);
    }

    strcpy(newFlight->flight.destination, destination);
    strcpy(newFlight->flight.date, date);
    newFlight->flight.fare = fare;

    newFlight->nextElement = NULL;
    newFlight->prevElement = NULL;

    return newFlight;
}

/*
Function: InsertNewNodeDest
Parameters: struct FlightNode** head - double pointer to the head of the destination-sorted list
            struct FlightNode** tail - double pointer to the tail of the destination-sorted list
            char* destination - pointer to the destination string for the flight
            char* date - pointer to the date string for the flight
            float fare - the fare for the flight
Description: This function inserts a new flight node into the destination-sorted list in the correct position.
Return value: void
*/
void InsertNewNodeDest(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare) {
    struct FlightNode* newFlight = CreateNewNode(destination, date, fare);

    if (*head == NULL) {
        *head = newFlight;
        *tail = newFlight;
        return;
    }

    int result = strcmp((*head)->flight.destination, destination);
    // Case 2: If the new node's fare is less than the head's fare, insert at the beginning
    if (result >= 0) {
        newFlight->nextElement = *head;
        (*head)->prevElement = newFlight;
        *head = newFlight;
        return;
    }

    struct FlightNode* current = *head;

    while (current->nextElement != NULL && (strcmp(current->nextElement->flight.destination , destination)) <= 0 ) {
        current = current->nextElement;
    }

    // Insert the new node
    newFlight->nextElement = current->nextElement;
    newFlight->prevElement = current;

    if (current->nextElement != NULL) {
        current->nextElement->prevElement = newFlight;
    }
    else {
        // Update the tail if we are inserting at the end
        *tail = newFlight;
    }

    current->nextElement = newFlight;
}

/*
Function: InsertNewNodeFare
Parameters: struct FlightNode** head - double pointer to the head of the fare-sorted list
            struct FlightNode** tail - double pointer to the tail of the fare-sorted list
            char* destination - pointer to the destination string for the flight
            char* date - pointer to the date string for the flight
            float fare - the fare for the flight
Description: This function inserts a new flight node into the fare-sorted list in the correct position.
Return value: void
*/
void InsertNewNodeFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare) {
    struct FlightNode* newFlight = CreateNewNode(destination, date, fare);

    if (*head == NULL) {
        *head = newFlight;
        *tail = newFlight;
        return;
    }

    // Case 2: If the new node's fare is less than the head's fare, insert at the beginning
    if ((*head)->flight.fare >= fare) {
        newFlight->nextElement = *head;
        (*head)->prevElement = newFlight;
        *head = newFlight;
        return;
    }

    struct FlightNode* current = *head;

    while (current->nextElement != NULL && current->nextElement->flight.fare <= fare) {
        if (current->nextElement->flight.fare == fare) {
            // Insert before the current node with the same fare
            newFlight->nextElement = current->nextElement;
            newFlight->prevElement = current;
            current->nextElement->prevElement = newFlight;
            current->nextElement = newFlight;
            return;
        }
        current = current->nextElement;
    }

    // Insert the new node
    newFlight->nextElement = current->nextElement;
    newFlight->prevElement = current;

    if (current->nextElement != NULL) {
        current->nextElement->prevElement = newFlight;
    }
    else {
        // Update the tail if we are inserting at the end
        *tail = newFlight;
    }

    current->nextElement = newFlight;
}

/*
Function: findFlightInfo
Parameters: struct FlightNode* head - pointer to the head of the list
            char* destination - pointer to the destination string to search for
            char* date - pointer to the date string to search for
            float fare - fare of a flight
Description: This function searches for a flight node in the list that matches the given destination and date.
Return value: struct FlightNode* - pointer to the found flight node, or NULL if not found
*/

void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date, float fare) {
    flight->destination = (char*)malloc(strlen(destination) + 1);
    if (flight->destination == NULL) {
        printf("Memory allocation failed for destination\n");
    }
    else {
        strcpy(flight->destination, destination);
    }

    flight->date = (char*)malloc(strlen(date) + 1);
    if (flight->date == NULL) {
        printf("Memory allocation failed for date\n");
    }
    else {
        strcpy(flight->date, date);
    }

    flight->fare = fare;
}



/*
Function: printFlightInfo
Parameters:
    struct FlightNode* head - a pointer to the head of the linked list containing flight nodes
Description:
This function prints information about each flight in the linked list, including destination, date, and fare.
Return value:
    void
*/
void printFlightInfo(struct FlightNode* head) {

    struct FlightNode* current = head;
    while (current != NULL) {
        printf("%-35s%-35s%-10.2f\n", current->flight.destination, current->flight.date, current->flight.fare);
        current = current->nextElement;
    }

}

/*
Function: findFlight
Parameters:
    struct FlightNode* head - a pointer to the head of the linked list containing flight nodes
    char* destination - pointer to a string representing the destination of the flight to find
    char* date - pointer to a string representing the date of the flight to find
Description:
This function searches for a flight node within a linked list based on the provided destination and date.
Return value:
    struct FlightNode* - a pointer to the found flight node if it exists, otherwise returns NULL
*/
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date) {

    struct FlightNode* current = head;

    while (current != NULL) {

        if (strcmp(destination, current->flight.destination) == 0 && (strcmp(date, current->flight.date) == 0)) {
            return current;
        }
        current = current->nextElement;
    }
    
    return NULL;
}





/*
Function: deleteNode
Parameters: struct FlightNode* node - pointer to the flight node to be deleted
            struct FlightNode* head -  pointer to the head of the list
            struct FlightNode* tail -  pointer to the tail of the list
Description: This function deletes a node from the doubly linked list and updates the head and tail pointers if necessary.
Return value: void
*/
void deleteNode(struct FlightNode* node, struct FlightNode* head, struct FlightNode* tail) {

        if (node == NULL) {
            return;
        }
        /*relink the previous node to the next node, if it exists*/
        if (node->prevElement != NULL) {
            node->prevElement->nextElement = node->nextElement;
        }
        else {
            /*if the node is the head, update the head pointer*/
            head = node->nextElement;
        }
        /*relink the next node to the previous node, if it exists*/
        if (node->nextElement != NULL) {
            node->nextElement->prevElement = node->prevElement;
        }
        else {
            /*if the node is the tail, update the tail pointer*/
            tail = node->prevElement;
        }


        if ((freeAllocatedMemory(node)) == 0) {
            printf("Memory could not be freed\n");
            return;
        }

}

/*
Function: freeAllocatedMemory
Parameters: struct FlightNode* head - pointer to the head of the list
Description: This function frees all nodes in the linked list, including the memory allocated for the destination and date strings.
             It traverses the list and frees each node's allocated memory.
Return value: int - the number of nodes that were freed
*/
int freeAllocatedMemory(struct FlightNode* head) {

    struct FlightNode* current = head;
    struct FlightNode* next;

    while (current != NULL) {
        next = current->nextElement;
        free(current->flight.destination);
        free(current->flight.date);
        free(current);
        current = next;
        return 1;
    }

    if (current == NULL) {

        return 0;
    }

}