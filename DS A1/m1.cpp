/*
* FILE : f1.cpp
* PROJECT : Focused 1 assignment
* PROGRAMMER : Valentyn Novosydliuk
* FIRST VERSION : 05/10/2024
* DESCRIPTION :
* This program gets user flight infomation and aims to work with active memory allocation using malloc();
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996);
const int kMaxStrSize = 30;
const int kNumberOfFlights = 10;

void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date);
void printFlightInfo(struct FlightInfo* flights);

struct FlightInfo {

	char* destination;
	char* date;

};

int main(void) {



	struct FlightInfo flight[kNumberOfFlights] = { 0 };

	for (int i = 0; i < kNumberOfFlights; i++) {

		char destination[kMaxStrSize] = "";
		char dateOfTheFlight[kMaxStrSize] = "";

		printf("Enter the name of a destination of a flight\n");
		fgets(destination, kMaxStrSize, stdin);
		destination[strcspn(destination, "\n")] = '\0';

		printf("Enter date for flight %d: ", i + 1);
		fgets(dateOfTheFlight, kMaxStrSize, stdin);
		dateOfTheFlight[strcspn(dateOfTheFlight, "\n")] = '\0';

		fillFlightInfo(&flight[i], destination, dateOfTheFlight);
	}

	printFlightInfo(flight);
	for (int i = 0; i < 10; ++i) {
		free(flight[i].destination);
		free(flight[i].date);
	}

	return 0;
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
void fillFlightInfo(struct FlightInfo* flight, const char* destination, const char* date) {

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