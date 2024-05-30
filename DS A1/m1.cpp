/*
* FILE : m1.cpp
* PROJECT : Assignment 1
* PROGRAMMER : Valentyn Novosydliuk
* FIRST VERSION : 05/22/2024
* DESCRIPTION :
* This program works with a double sorted linked list and malloc dynamic memory allocation
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)
const int kMaxStrSize = 30;
const int kNumberOfFlights = 10;

void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date, float* fare);
void printFlightInfo(struct FlightInfo* flights);
struct Node* findFlight(struct FlightNode* head, char* destination, char* date);
void deleteNode(struct FLightNode* node, struct FlightNode** head, struct FlightNode** tail);
struct Node* InsertNewNode(struct Student* head, struct Student* tail, char* destination, char* date, float* age);
struct Node* CreateNewNode(char* destination, char* date, float* fare);


struct FlightInfo {

	char* destination;
	char* date;
	float* fare;

};

struct Node {

	struct FlightInfo flight;
	struct FlightNode* prevElement;
	struct FlightNide* nextElement;

};



int main(void) {

	struct Node* headForDestinationSorted = NULL;
	struct Node* tailForDestinationSorted = NULL;
	struct Node* headForFareSorted = NULL;
	struct Node* tailForFareSorted = NULL;


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
			
			float bufferClearer;
			while ((bufferClearer = getchar()) != '\n' && bufferClearer != EOF);
			continue;
		}

		float bufferClearer;
		while ((bufferClearer = getchar()) != '\n' && bufferClearer != EOF);

		fillFlightInfo(&flights, destination, dateOfTheFlight, &fare);
		InsertNewNode(headForFareSorted, )
		/*so now i need to create a sorting fucntion or comparing fucntion for
		destination as well as fare
		
		so the inserntode will check if there is a node first, then if yes
		it will go over the other nodes and check if the fare > previousNode && fare <= NextNode
		or smth like that*/

	}

	return 0;
}


struct Node* CreateNewNode(char* destination, char* date, float* fare) {



}

struct Node* InsertNewNode(struct Student* head, struct Student* tail, char* destination, char* date, float* age) {

	

}
/*
Function: fillFlightInfo
Parameters: struct FlightInfo* flight - a pointer to a struct FlightInfo (which is a
										pointer to an element of the array)
			const char* destination - constant pointer to flight information string
			const char* date - constant pointer to flight information string
Description: Thhis fucntion fills in the struct field and allocates memory blocks
Return value: void
*/
void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date, float* fare) {

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

	flight->fare = (float*)malloc(sizeof + 1);
	if (flight->fare == NULL) {
		printf("Memory allcoation failed for fare\n");
	}
	else {
		flight->fare = fare;
	}
}


/*
Function: printfFlightInfo
Parameters: struct FlightInfo* flight - a pointer to a struct FlightInfo
Description: This functions prints the formatted output after the fillFlightInfo
Return value: void
*/
void printFlightInfo(struct FlightInfo* flights) {

	printf("%-35s%-35s\n", "Destination", "Date");

	for (int i = 0; i < 10; ++i) {
		printf("%-35s%-35s\n", flights[i].destination, flights[i].date);
	}
}


/*
Function: printfFlightInfo
Parameters: struct FlightInfo* flight - a pointer to a struct FlightInfo
Description: This functions prints the formatted output after the fillFlightInfo
Return value: void
*/
struct Node* findFlight(struct FlightNode* head, char* destination, char* date) {

	return NULL;

}



/*
Function: printfFlightInfo
Parameters: struct FlightInfo* flight - a pointer to a struct FlightInfo
Description: This functions prints the formatted output after the fillFlightInfo
Return value: void
*/
void deleteNode(struct FLightNode* node, struct FlightNode** head, struct FlightNode** tail) {

	if (node == NULL) {

		return ;

	}

}

/*i should have 2 sourted double linkes lists
1 for flight destination
1 for flight fare

after the user enter DOT - .
i need to get his destination and on other line date
if there is a match, then display the fare and prompt for a new fare
If the fare is changed, update the destination-sorted linked list with the
new fare. Then delete the flight from the fare-sorted linked list and
reinsert it.
▪ If the fare is unchanged, print a message indicating that and do nothing.
▪ Again, the fare will always be valid.
If there is not an exact match (on the destination and date fields), display a
message saying so and continue with the next step

After that, diplay both linked lists as before

At the end, I must free up all allocated memory
*/