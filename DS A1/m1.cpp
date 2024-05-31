#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)
const int kMaxStrSize = 30;
const int kNumberOfFlights = 10;

void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date, float fare);
void printFlightInfo(struct FlightNode* flights);
struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date);
void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail);
void InsertNewNodeFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare);
void InsertNewNodeDest(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare);
struct FlightNode* CreateNewNode(char* destination, char* date, float fare);

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
        InsertNewNodeDest();
    }

    struct FlightNode* current = headForFareSorted;
    while (current != NULL) {
        printf("Destination: %s, Date: %s, Fare: %.2f\n", current->flight.destination, current->flight.date, current->flight.fare);
        current = current->nextElement;
    }

    return 0;
}

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
void InsertNewNodeDest(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare) {
    struct FlightNode* newFlight = CreateNewNode(destination, date, fare);

    if (*head == NULL) {
        *head = newFlight;
        *tail = newFlight;
        return;
    }

    int result = strcmp((*head)->flight.destination, destination));
    // Case 2: If the new node's fare is less than the head's fare, insert at the beginning
    if (result == 0) {
        newFlight->nextElement = *head;
        (*head)->prevElement = newFlight;
        *head = newFlight;
        return;
    }

    struct FlightNode* current = *head;

    while (current->nextElement != NULL && current->nextElement->flight.fare < fare) {
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

void InsertNewNodeFare(struct FlightNode** head, struct FlightNode** tail, char* destination, char* date, float fare) {
    struct FlightNode* newFlight = CreateNewNode(destination, date, fare);

    if (*head == NULL) {
        *head = newFlight;
        *tail = newFlight;
        return;
    }

    // Case 2: If the new node's fare is less than the head's fare, insert at the beginning
    if ((*head)->flight.fare > fare) {
        newFlight->nextElement = *head;
        (*head)->prevElement = newFlight;
        *head = newFlight;
        return;
    }

    struct FlightNode* current = *head;

    while (current->nextElement != NULL && current->nextElement->flight.fare < fare) {
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


void printFlightInfo(struct FlightNode* flights) {


}

struct FlightNode* findFlight(struct FlightNode* head, char* destination, char* date) {


    return NULL;
}

void deleteNode(struct FlightNode* node, struct FlightNode** head, struct FlightNode** tail) {


}