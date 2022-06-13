


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//


int stringlength(char* d)
{
	int f = 0;
	while (*d != '\0')//using conditional statement
	{
		f++;
		d++;
	}
	return f;
}

int inputInt() //return an integer value and receives no arguments
{
	char newline = 'x';
	int value;
	scanf("%d%c", &value, &newline);
	while (newline != '\n')//using conditional statement
	{
		clearInputBuffer();
		printf("Error! Input a whole number: ");
		scanf("%d%c", &value, &newline);
	}
	return value;
}

int inputIntPositive() //return an integer value and receives no arguments
{
	char newline = 'x';
	int valueofnum;
	scanf("%d%c", &valueofnum, &newline);
	while (newline == 'x' || newline != '\n')//using conditional statement
	{
		clearInputBuffer();
		printf("Error! Input a whole number: ");//printing appropriate error message
		scanf("%d%c", &valueofnum, &newline);
	}
	while (valueofnum <= 0)//using conditional statement
	{
		printf("ERROR! Value must be > 0: ");//printing appropriate error message
		scanf("%d%c", &valueofnum, &newline);
	}
	return valueofnum;
}

int inputIntRange(int lowlimit, int uplimit) //performs the same operations as getInteger but validates the value entered is between the two arguments received by the function (inclusive).
{
	char newline = 'x';
	int valueofnum;
	scanf("%d%c", &valueofnum, &newline);
	while (newline == 'x') //using conditional statement
	{
		clearInputBuffer();
		printf("Error! Input a whole number: ");
		scanf("%d%c", &valueofnum, &newline);
	}
	while (valueofnum < lowlimit || valueofnum > uplimit)//using conditional statement
	{
		printf("ERROR! Value must be between %d and %d inclusive: ", lowlimit, uplimit);
		scanf("%d%c", &valueofnum, &newline);
	}
	return valueofnum;
}

char inputCharOption(char* w) //validate the entered character matches any of the characters in the received C string argument.
{
	int i, j = 0;
	char char2, newline = 'x';
	scanf("%c%c", &char2, &newline);
	while (newline != '\n')//using conditional statement
	{
		clearInputBuffer();
		printf("ERROR: Character must be one of [%s]: ", w);
		scanf("%c%c", &char2, &newline);
	}
	for (i = 0; (w[i] != '\0' && j == 0); i++)
	{
		while (newline != '\n' || j == 0)
		{
			for (i = 0; i <= stringlength(w) && j == 0; i++)
			{
				if (w[i] == char2)
				{
					j = 1;
				}
			}
			if (j != 1 || newline != '\n')
			{
				printf("ERROR: Character must be one of [%s]: ", w);
				scanf("%c%c", &char2, &newline);
			}
		}
	}
	return char2;
}

void inputCString(char* p, int minimumno, int maximumno) // does not return a value, but does return a C string via the 1st argument parameter pointer.
{
	int i = 0, j = 0;
	char ch[41];
	scanf("%40[^\n]", ch);
	for (i = 0; ch[i] != '\0'; i++)
	{
	}

	while (i < minimumno || i > maximumno)//using conditional statement
	{
		clearInputBuffer();
		if (minimumno == maximumno)
		{
			printf("ERROR: String length must be exactly %d chars: ", minimumno);//printing appropriate error message
			scanf("%40[^\n]", ch);
		}
		if (minimumno != maximumno)
		{
			if (i < minimumno)
			{
				printf("ERROR: String length must be between %d and %d chars: ", minimumno, maximumno);//printing appropriate error message
				scanf("%40[^\n]", ch);
			}
			else if (i > maximumno)
			{
				printf("ERROR: String length must be no more than %d chars: ", maximumno);//printing appropriate error message
				scanf("%40[^\n]", ch);
			}
		}
		for (i = 0; ch[i] != '\0'; i++)
		{
		}
	}
	for (j = 0; ch[j] != '\0'; j++)
	{
		p[j] = ch[j];
	}
	p[j] = '\0';
	getchar();
}

void displayFormattedPhone(const char* phone)
{
	char c = *phone;
	if (phone == NULL || c < '0' || c > '9')
	{
		printf("(___)___-____"); return;
	}
	int i = 0;

	printf("(");
	while (*phone)
	{
		printf("%c", *phone);
		i++;
		if (i == 3)
			printf(")");
		else if (i == 6)
			printf("-");
		phone++;
	}
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

