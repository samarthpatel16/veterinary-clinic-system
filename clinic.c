


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
	printf("Pat.# Name            Phone#\n"
		   "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
	if (fmt == FMT_FORM)
	{
		printf("Name  : %s\n"
			   "Number: %05d\n"
			   "Phone : ", patient->name, patient->patientNumber);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
	else
	{
		printf("%05d %-15s ", patient->patientNumber,
			   patient->name);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
	printf("Clinic Appointments for the Date: ");

	if (isAllRecords)
	{
		printf("<ALL>\n\n");
		printf("Date       Time  Pat.# Name            Phone#\n"
			   "---------- ----- ----- --------------- --------------------\n");
	}
	else
	{
		printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
		printf("Time  Pat.# Name            Phone#\n"
			   "----- ----- --------------- --------------------\n");
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
						 const struct Appointment* appoint,
						 int includeDateField)
{
	if (includeDateField)
	{
		printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
			   appoint->date.day);
	}
	printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
		   patient->patientNumber, patient->name);

	displayFormattedPhone(patient->phone.number);

	printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
	int selection;

	do {
		printf("Veterinary Clinic System\n"
			   "=========================\n"
			   "1) PATIENT     Management\n"
			   "2) APPOINTMENT Management\n"
			   "-------------------------\n"
			   "0) Exit System\n"
			   "-------------------------\n"
			   "Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');
		switch (selection)
		{
		case 0:
			printf("Are you sure you want to exit? (y|n): ");
			selection = !(inputCharOption("yn") == 'y');
			putchar('\n');
			if (!selection)
			{
				printf("Exiting system... Goodbye.\n\n");
			}
			break;
		case 1:
			menuPatient(data->patients, data->maxPatient);
			break;
		case 2:
			menuAppointment(data);
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
	int selection;

	do {
		printf("Patient Management\n"
			   "=========================\n"
			   "1) VIEW   Patient Data\n"
			   "2) SEARCH Patients\n"
			   "3) ADD    Patient\n"
			   "4) EDIT   Patient\n"
			   "5) REMOVE Patient\n"
			   "-------------------------\n"
			   "0) Previous menu\n"
			   "-------------------------\n"
			   "Selection: ");
		selection = inputIntRange(0, 5);
		putchar('\n');
		switch (selection)
		{
		case 1:
			displayAllPatients(patient, max, FMT_TABLE);
			suspend();
			break;
		case 2:
			searchPatientData(patient, max);
			break;
		case 3:
			addPatient(patient, max);
			suspend();
			break;
		case 4:
			editPatient(patient, max);
			break;
		case 5:
			removePatient(patient, max);
			suspend();
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
	int selection;

	do {
		printf("Edit Patient (%05d)\n"
			   "=========================\n"
			   "1) NAME : %s\n"
			   "2) PHONE: ", patient->patientNumber, patient->name);
		
		displayFormattedPhone(patient->phone.number);
		
		printf("\n"
			   "-------------------------\n"
			   "0) Previous menu\n"
			   "-------------------------\n"
			   "Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');

		if (selection == 1)
		{
			printf("Name  : ");
			inputCString(patient->name, 1, NAME_LEN);
			putchar('\n');
			printf("Patient record updated!\n\n");
		}
		else if (selection == 2)
		{
			inputPhoneData(&patient->phone);
			printf("Patient record updated!\n\n");
		}

	} while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
	int selection;

	do {
		printf("Appointment Management\n"
			   "==============================\n"
			   "1) VIEW   ALL Appointments\n"
			   "2) VIEW   Appointments by DATE\n"
			   "3) ADD    Appointment\n"
			   "4) REMOVE Appointment\n"
			   "------------------------------\n"
			   "0) Previous menu\n"
			   "------------------------------\n"
			   "Selection: ");
		selection = inputIntRange(0, 4);
		putchar('\n');
		switch (selection)
		{
		case 1:
			viewAllAppointments(data);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 2:
			viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 3:
			addAppointment(data->appointments, data->maxAppointments,
						   data->patients, data->maxPatient);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 4:
			removeAppointment(data->appointments, data->maxAppointments,
							  data->patients, data->maxPatient);  // ToDo: You will need to create this function!
			suspend();
			break;
		}
	} while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


void displayAllPatients(const struct Patient patient[], int max, int fmt) {
	if (max == 0) {
		printf("*** No records found ***\n");
		return;
	}
	int i;
	displayPatientTableHeader();
	for (i = 0; i < max; i++) {
		if (patient[i].patientNumber != 0)
			displayPatientData(&patient[i], fmt);
	}
	printf("\n");
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {
	int choice;
	do {
		printf("Search Options\n");
		printf("==========================\n");
		printf("1) By patient number\n");
		printf("2) By phone number\n");
		printf("..........................\n");
		printf("0) Previous menu\n");
		printf("..........................\n");
		printf("Selection: ");

		scanf("%d", &choice);
		printf("\n");
		switch (choice) {
		case 1:
			searchPatientByPatientNumber(patient, max);
			getc(stdin);
			suspend();
			break;
		case 2:
			searchPatientByPhoneNumber(patient, max);
			getc(stdin);
			suspend();
			break;
		}
	} while (choice != 0);
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max) {
	int i;
	for (i = 0; i < max; i++) {
		if (patient[i].patientNumber == 0) {
			break;
		}
	}
	if (i == max) {
		printf("ERROR: Patient listing is FULL!\n\n");
		return;
	}

	patient[i].patientNumber = nextPatientNumber(patient, max);
	inputPatient(&patient[i]);
	printf("*** New patient record added ***\n\n");
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max) {
	int num;
	printf("Enter the patient number: ");
	scanf("%d", &num);
	printf("\n");
	int index = findPatientIndexByPatientNum(num, patient, max);

	if (index == -1) printf("ERROR: Patient record not found!\n\n");
	else {
		menuPatientEdit(&patient[index]);
	}
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {
	int num;
	printf("Enter the patient number: ");
	scanf("%d", &num);
	printf("\n");

	int index = findPatientIndexByPatientNum(num, patient, max);

	if (index == -1) {
		printf("ERROR: Patient record not found!\n");
		getc(stdin);
	}
	else {
		char c, temp;
		displayPatientData(&patient[index], FMT_FORM);
		printf("\nAre you sure you want to remove this patient record? (y/n): ");
		scanf(" %c%c", &c, &temp);
		while (temp != '\n' || (c != 'y' && c != 'n')) {
			while (temp != '\n') temp = getc(stdin);
			printf("ERROR: Character must be one of [yn]: ");
			scanf("%c%c", &c, &temp);
		}

		if (c == 'y' || c == 'Y') {
			patient[index].patientNumber = 0;
			patient[index].phone.number[0] = 0;
			patient[index].name[0] = 0;
			printf("Patient record has been removed!\n");
		}
		else
			printf("Operation aborted.\n");
	}
	printf("\n");
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:

int compare(struct Appointment a1, struct Appointment a2) {
	if (a1.date.year > a2.date.year)
		return 1;
	else if (a1.date.year == a2.date.year) {
		if (a1.date.month > a2.date.month)
			return 1;
		else if (a1.date.month == a2.date.month) {
			if (a1.date.day > a2.date.day)
				return 1;
			else if (a1.date.day == a2.date.day) {
				if (a1.time.hour > a2.time.hour)
					return 1;
				else if (a1.time.hour == a2.time.hour) {
					if (a1.time.min > a2.time.min)
						return 1;
					else if (a1.time.min == a2.time.min)
						return 0;
				}
			}
		}
	}
	return -1;
}

void sort(struct ClinicData* data) {
	int i, j;
	for (i = 0; i < data->maxAppointments - 1; i++) {
		for (j = i + 1; j < data->maxAppointments; j++) {
			if (compare(data->appointments[i], data->appointments[j]) == 1) {
				struct Appointment temp = data->appointments[i];
				data->appointments[i] = data->appointments[j];
				data->appointments[j] = temp;
			}
		}
	}
}

void viewAllAppointments(struct ClinicData* data) {
	int i, j;
	sort(data);
	const struct Date dummy;
	displayScheduleTableHeader(&dummy, 1);
	for (i = 0; i < data->maxAppointments; i++) {
		if (data->appointments[i].patientNumber != 0) {
			for (j = 0; j < data->maxPatient; j++) {
				if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {
					displayScheduleData(&data->patients[j], &data->appointments[i], 1);
					break;
				}
			}
		}
	}
	printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {
	sort(data);
	struct Date date;
	printf("Year        : ");
	scanf("%d", &date.year);
	printf("Month (1-12): ");
	scanf("%d", &date.month);
	
	int range;
	if (date.month == 2) {
		if (date.year % 4 == 0 && date.year % 100 != 0) {
			range = 29;
		}
		else range = 28;
	}
	else range = 31;

	printf("Day (1-%d)  : ", range);
	scanf("%d", &date.day);

	while (date.day < 1 || date.day > range) {
		printf("ERROR! Value must be between 1 and %d inclusive: ", range);
		scanf("%d", &date.day);
	}

	int i, j;
	printf("\n");
	displayScheduleTableHeader(&date, 0);
	for (i = 0; i < data->maxAppointments; i++) {
		if (data->appointments[i].patientNumber != 0) {
			for (j = 0; j < data->maxPatient; j++) {
				if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {
					struct Date d = data->appointments[i].date;
					if (d.day == date.day && d.month == date.month && d.year == date.year) {
						displayScheduleData(&data->patients[j], &data->appointments[i], 0);
						break;
					}
				}
			}
		}
	}

	printf("\n");
	getc(stdin);
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments,
	struct Patient* patients, int maxPatient) {
	struct Appointment a;
	printf("Patient Number: ");
	scanf("%d", &a.patientNumber);
	printf("Year        : ");
	scanf("%d", &a.date.year);
	printf("Month (1-12): ");
	scanf("%d", &a.date.month);
	int range;
	if (a.date.month == 2) {
		if (a.date.year % 4 == 0 && a.date.year % 100 != 0) {
			range = 29;
		}
		else range = 28;
	}
	else range = 31;

	printf("Day (1-%d)  : ", range);
	scanf("%d", &a.date.day);
	printf("Hour (0-23)  : ");
	scanf("%d", &a.time.hour);
	printf("Minute (0-59): ");
	scanf("%d", &a.time.min);

	int i;
	for (i = 0; i < maxAppointments; i++) {
		if (compare(a, appointments[i]) == 0) {
			printf("\nERROR: Appointment timeslot is not available!\n\n");
			printf("Year        : ");
			scanf("%d", &a.date.year);
			printf("Month (1-12): ");
			scanf("%d", &a.date.month);
			int range;
			if (a.date.month == 2) {
				if (a.date.year % 4 == 0 && a.date.year % 100 != 0) {
					range = 29;
				}
				else range = 28;
			}
			else range = 31;

			printf("Day (1-%d)  : ", range);
			scanf("%d", &a.date.day);
			printf("Hour (0-23)  : ");
			scanf("%d", &a.time.hour);
			printf("Minute (0-59): ");
			scanf("%d", &a.time.min);
			while ((a.time.min != 0 && a.time.min % 30 != 0) || a.time.hour < 10 || a.time.hour >= 14) {
				if (a.time.hour == 14 && a.time.min == 0)
					break;
				printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
				printf("Hour (0-23)  : ");
				scanf("%d", &a.time.hour);
				printf("Minute (0-59): ");
				scanf("%d", &a.time.min);
			}
			i = -1;
		}
	}

	printf("\n*** Appointment scheduled! ***\n\n");
	for (i = 0; i < maxAppointments; i++) {
		if (appointments[i].patientNumber == 0) {
			appointments[i] = a;
			break;
		}
	}
	getc(stdin);
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments,
	struct Patient* patients, int maxPatient) {

	int i, patient;
	char c;
	printf("Patient Number: ");
	scanf("%d%c", &patient, &c);
	for (i = 0; i < maxPatient; i++) {
		if (patients[i].patientNumber == patient) {
			break;
		}
	}
	if (i == maxPatient) {
		printf("ERROR: Patient record not found!\n\n");
		return;
	}

	struct Appointment a;
	a.patientNumber = patient;
	printf("Year        : ");
	scanf("%d", &a.date.year);
	printf("Month (1-12): ");
	scanf("%d", &a.date.month);
	int range;
	if (a.date.month == 2) {
		if (a.date.year % 4 == 0 && a.date.year % 100 != 0) {
			range = 29;
		}
		else range = 28;
	}
	else range = 31;

	printf("Day (1-%d)  : ", range);
	scanf("%d", &a.date.day);

	printf("\n");
	displayPatientData(&patients[i], FMT_FORM);

	char temp;
	printf("Are you sure you want to remove this appointment (y,n): ");
	scanf(" %c%c", &c, &temp);
	while (temp != '\n' || (c != 'y' && c != 'n')) {
		while (temp != '\n') temp = getc(stdin);
		printf("ERROR: Character must be one of [yn]: ");
		scanf("%c%c", &c, &temp);
	}

	if (c == 'y' || c == 'Y') {
		for (i = 0; i < maxAppointments; i++)
			if (appointments[i].patientNumber == patient && 
				appointments[i].date.year == a.date.year && appointments[i].date.month == a.date.month 
				&& appointments[i].date.day == a.date.day)
				appointments[i].patientNumber = 0;
		printf("\nAppointment record has been removed!\n\n");
	}
	else
		printf("Operation aborted.\n\n");
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
	int num;
	printf("Search by patient number: ");
	scanf("%d", &num);
	printf("\n");
	int index = findPatientIndexByPatientNum(num, patient, max);
	if (index == -1) printf("*** No records found ***\n");
	else {
		displayPatientData(&patient[index], FMT_FORM);
	}
	printf("\n");
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
	char phone[PHONE_LEN + 1];
	printf("Search by phone number: ");
	scanf("%s", phone);
	printf("\n");
	int i, found = 0;
	for (i = 0; i < max; i++) {
		if (strcmp(phone, patient[i].phone.number) == 0) {
			if (found == 0)
				displayPatientTableHeader();
			found++;
			displayPatientData(&patient[i], FMT_TABLE);
		}
	}
	if (found == 0) {
		printf("*** No records found ***\n");
	}
	printf("\n");
}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max) {
	int i, m = 0;
	for (i = 0; i < max; i++) {
		if (patient[i].patientNumber > m) {
			m = patient[i].patientNumber;
		}
	}
	return m + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
	const struct Patient patient[], int max) {
	int i;
	for (i = 0; i < max; i++) {
		if (patient[i].patientNumber == patientNumber) {
			return i;
		}
	}
	return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////


// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient) {
	printf("Patient Data Input\n");
	printf("------------------\n");
	printf("Number: %05d\n", patient->patientNumber);
	printf("Name  : ");
	fgets(patient->name, NAME_LEN + 1, stdin);
	while (patient->name[strlen(patient->name) - 1] != '\n') {
		while (getc(stdin) != '\n');
		printf("ERROR: String length must be no more than 15 chars: ");
		fgets(patient->name, NAME_LEN + 1, stdin);
	}
	patient->name[strlen(patient->name) - 1] = '\0';
	printf("\n");
	inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {
	printf("Phone Information\n");
	printf("-----------------\n");
	printf("How will the patient like to be contacted?\n");
	printf("1. Cell\n");
	printf("2. Home\n");
	printf("3. Work\n");
	printf("4. TBD\n");
	printf("Selection: ");
	int choice;
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		strcpy(phone->description, "CELL");
		break;
	case 2:
		strcpy(phone->description, "HOME");
		break;
	case 3:
		strcpy(phone->description, "WORK");
		break;
	case 4:
		strcpy(phone->description, "TBD");
		break;
	}

	printf("\nContact: %s\n", phone->description);
	printf("Number : ");
	char c, number[20];
	scanf("%s%c", number, &c);
	while (strlen(number) != 10) {
		while (c != '\n') c = getc(stdin);
		printf("Invalid 10-digit number! Number: ");
		scanf("%s%c", number, &c);
	}
	strcpy(phone->number, number);
	printf("\n");
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max) {
	FILE* ptr = fopen(datafile, "r");
	char input[100];
	int count = 0;
	while (count < max && fgets(input, sizeof(input), ptr) != NULL) {
		
		int i = 0, index;
		patients[count].patientNumber = atoi(input);
		while (input[i++] != '|');

		index = 0;
		while (input[i] != '|') {
			patients[count].name[index] = input[i];
			index++; i++;
		}
		patients[count].name[index] = '\0';
		i++;

		index = 0;
		while (input[i] != '|') {
			patients[count].phone.description[index] = input[i];
			index++; i++;
		}
		patients[count].phone.description[index] = '\0';
		i++;

		index = 0;
		while (input[i] != '\n') {
			patients[count].phone.number[index] = input[i];
			index++; i++;
		}
		patients[count].phone.number[index] = '\0';

		count++;
	}
	fclose(ptr);
	return count;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
	FILE* ptr = fopen(datafile, "r");
	struct Appointment a;
	int count = 0;
	while (count < max && fscanf(ptr, "%d,%d,%d,%d,%d,%d", &a.patientNumber, &a.date.year,
		&a.date.month, &a.date.day, &a.time.hour, &a.time.min) == 6) {
		appoints[count] = a;
		count++;
	}
	fclose(ptr);
	return count;
}
