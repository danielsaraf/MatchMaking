/******************************************
*Student name:  Daniel Saraf
*Student ID:    311312045
*Exercise name: ex6
******************************************/


// Library includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define declaring
#define MAX_BUFFER 212
#define MIN_UN 3
#define MAX_UN 10
#define MAX_PASS 15
#define MIN_PASS 3
#define MAX_N 15
#define ID_LEN 9
#define MIN_AGE	18	
#define MAX_AGE 100
// enums declaring
enum hobbies { BASEBALL = 1, BASKETBALL, BICYCLE, BOOKS, DRAWING, GYM, MOVIES, POETRY };
enum bool{ TRUE = 0,FALSE };
typedef enum bool bool;
typedef struct FemaleItem FemaleItem;
// Structs declaring
typedef struct
{
	char  ID[ID_LEN];
	char* firstName;
	char* lastName;
	int   age;
	char  gender;
	char* userName;
	unsigned char  hobbies;
	char* password;
	char* about;
}Member;
struct FemaleItem
{
	FemaleItem*	next;
	Member* data;
};
typedef struct
{
	int maleCounter;
	Member** mptr;
	FemaleItem *head;
}Gender;
// Functions declaring
Gender* memoryInt();
void enterMenu(Gender* gptr);
void readData(Gender* gptr);
void exportData(Gender* gptr);
void logIn(Gender* gptr);
void newMember(Gender* gptr);
bool checkValid(char str[]);
void mainMenu(Member* mptr, Gender* gptr);
Member* searchUser(char userName[], Gender* gptr);
void findLove(Member* mptr, Gender* gptr);
void deleteUser(Member* mptr, Gender* gptr);
bool checkID(char buffer[], Gender* gptr);
bool checkMatch(unsigned char hobbiesMatch);
void freeAll(Gender* gptr);
void connectProfile(Member* mptr, Gender* gptr);
void findPlace(Gender* gptr, FemaleItem* fiptr);
void resetStruct(Member* mptr);
void printMatch(Member* curr);
void freeMember(Member* mptr);
void allocateFailed(Gender* gptr);
char* conToSmall(char str[]);
void hobbiesWriter(FILE* writePtr, unsigned char hobbies);
/***********************************************************************************************************
* function name: main
* The Input: -
* The output: -
* The Function operation: main is responsible for opening and closing the program in the right way.
	first it call to memoryInt function to make the database fundamental and read the data from the text
	than it pass the database pointer to enterMenu. at the end of the program it calls functions to export
	the Database for future use,free all the allocated memory and than exit safely
***********************************************************************************************************/
void main()
{
	//make the database and read from the input.txt
	Gender* gptr = memoryInt();
	//call enterMenu with the DB pointer
	enterMenu(gptr);
	//write all the data to output.txt
	exportData(gptr);
	//free all the allocated memory
	freeAll(gptr);
	exit(0);
}
/**********************************************************************************************************
* function name: memoryInt
* The Input: -
* The output: a address to the main structure
* The Function operation: the function allocate 3 structures, 1 for the Male dynamic array, one for
	the Female connected List and one general struck that will connect all the data
**********************************************************************************************************/
Gender* memoryInt()
{
	// Declaring a pointers
	Gender* gptr = NULL;
	Member** mptr = NULL;
	FemaleItem* fptr = NULL;
	// Allocate memory and check if fail
	if ((gptr = (Gender*)malloc(sizeof(Gender))) == NULL)
		allocateFailed(gptr);
	if ((mptr = (Member**)malloc(sizeof(Member*))) == NULL)
		allocateFailed(gptr);
	if ((fptr = (FemaleItem*)malloc(sizeof(FemaleItem))) == NULL)
		allocateFailed(gptr);
	// Connect the memories
	gptr->mptr = mptr;
	gptr->head = fptr;
	// Reset the pointer of femaleItem to NULL
	gptr->head->data = NULL;
	gptr->head->next = NULL;
	// Reset the counter of number of males
	gptr->maleCounter = 0;
	// Call readData to scan all the data from input.txt to the database
	readData(gptr);
	return (gptr);
}
/***********************************************************************************************************
* function name: readData
* The Input: an address to database
* The output: -
* The Function operation: the function read all the information from "input.txt" to the database
***********************************************************************************************************/
void readData(Gender* gptr)
{
	FILE *readPtr=NULL;
	Member* mptr=NULL;
	char buffer[MAX_BUFFER];
	int ch, i;
	unsigned char hobbies;
	// Opening input file and check if fail
	if ((readPtr = fopen("input.txt", "r")) == NULL)
	{
		printf("Failed opening file");
		freeAll(gptr);
		exit(1);
	}
	// Check if file is empty
	if ((ch = fgetc(readPtr)) == EOF)
		return;
	// Go back to the beginning of the file 
	rewind(readPtr);
	ch = fgetc(readPtr);
	// Do until the end of the file
	while(ch!=EOF)
	{
		hobbies = 0;
		//allocate a memory for a new member
		if ((mptr = (Member*)malloc(sizeof(Member))) == NULL)
			allocateFailed(gptr);
		//read the ID (until it find ";")
		for (i = 0; ch != 59 && ch != EOF; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		buffer[i] = 0;
		strcpy(mptr->ID, buffer);
		ch = fgetc(readPtr);
		//read the first name (until it find ";")
		for (i = 0; ch != 59 && ch != EOF; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		buffer[i] = 0;
		if ((mptr->firstName = (char*)malloc(strlen(buffer) + 1)) == NULL)
			allocateFailed(gptr);
		strcpy(mptr->firstName, buffer);
		ch = fgetc(readPtr);
		//read the last name (until it find ";")
		for (i = 0; ch != 59 && ch != EOF; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		buffer[i] = 0;
		if ((mptr->lastName = (char*)malloc(strlen(buffer) + 1)) == NULL)
			allocateFailed(gptr);
		strcpy(mptr->lastName, buffer);
		ch = fgetc(readPtr);
		//read the age (until it find ";")
		for (i = 0; ch != 59 && ch != EOF; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		mptr->age = atoi(buffer);
		//read the gender (until it find ";")
		mptr->gender = fgetc(readPtr);
		ch = fgetc(readPtr);
		ch = fgetc(readPtr);
		//read the user name (until it find ";")
		for (i = 0; ch != 59 && ch != EOF; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		buffer[i] = 0;
		if ((mptr->userName = (char*)malloc(strlen(buffer) + 1)) == NULL)
			allocateFailed(gptr);
		strcpy(mptr->userName, buffer);
		ch = fgetc(readPtr);
		//read the password (until it find ";")
		for (i = 0; ch != 59 && ch != EOF; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		buffer[i] = 0;
		if ((mptr->password = (char*)malloc(strlen(buffer) + 1)) == NULL)
			allocateFailed(gptr);
		strcpy(mptr->password, buffer);

		buffer[1] = 0;
		buffer[0] = fgetc(readPtr);
		//read the hobbies with bitewise operations on the char "hobbies"
		for (i = 0; i < 4; i++)
		{
			//convert buffer to a int number;
			ch = atoi(buffer);
			switch (ch)
			{
			case BASEBALL:
				hobbies |= 1;
				break;
			case BASKETBALL:
				hobbies |= 2;
				break;
			case BICYCLE:
				hobbies |= 4;
				break;
			case BOOKS:
				hobbies |= 8;
				break;
			case DRAWING:
				hobbies |= 16;
				break;
			case GYM:
				hobbies |= 32;
				break;
			case MOVIES:
				hobbies |= 64;
				break;
			case POETRY:
				hobbies |= 128;
				break;
			default:
				break;
			}//end of switch
			buffer[0] = fgetc(readPtr);
			buffer[0] = fgetc(readPtr);
		}//end of for
		//connect hobbies to the user
		mptr->hobbies = hobbies;
		ch = buffer[0];
		//read the description (until it find new line )
		for (i = 0; ch != 59 && ch != EOF && ch != '\n'; i++)
		{
			buffer[i] = ch;
			ch = fgetc(readPtr);
		}
		buffer[i] = 0;
		if ((mptr->about = (char*)malloc(strlen(buffer) + 1)) == NULL)
			allocateFailed(gptr);
		strcpy(mptr->about, buffer);
		//connect the new profile to the DB
		connectProfile(mptr, gptr);
		ch = fgetc(readPtr);
	}
	//close the file
	fclose(readPtr);
	return;
}
/***********************************************************************************************************
* function name: exportData
* The Input: an address to database
* The output: -
* The Function operation: the function export all the information from the database to "output.txt"
***********************************************************************************************************/
void exportData(Gender* gptr)
{
	int i,j;
	char buffer[3];
	FemaleItem* curr=gptr->head->next;
	FILE* writePtr=NULL;
	//open the file and check failure
	if ((writePtr = fopen("output.txt", "w")) == NULL)
	{
		printf("Failed opening file");
		freeAll(gptr);
		exit(1);
	}
	//write all males database to file
	for (i = 0; i < gptr->maleCounter; i++)
	{
		//write the ID to the file
		for(j=0;gptr->mptr[i]->ID[j]!=0;j++)
		fputc(gptr->mptr[i]->ID[j], writePtr);
		fputc(59, writePtr);
		//write the first name to the file
		for (j = 0; gptr->mptr[i]->firstName[j] != 0; j++)
			fputc(gptr->mptr[i]->firstName[j], writePtr);
		fputc(59, writePtr);
		//write the last name to the file
		for (j = 0; gptr->mptr[i]->lastName[j] != 0; j++)
			fputc(gptr->mptr[i]->lastName[j], writePtr);
		fputc(59, writePtr);
		//write the age to the file, convert the int number to a string
		sprintf(buffer,"%d", gptr->mptr[i]->age);
		for (j = 0; buffer[j] != 0; j++)
			fputc(buffer[j], writePtr);
		fputc(59, writePtr);
		//write the gender to the file
		fputc(gptr->mptr[i]->gender, writePtr);
		fputc(59, writePtr);
		//write the user name to the file
		for (j = 0; gptr->mptr[i]->userName[j] != 0; j++)
			fputc(gptr->mptr[i]->userName[j], writePtr);
		fputc(59, writePtr);
		//write the password to the file
		for (j = 0; gptr->mptr[i]->password[j] != 0; j++)
			fputc(gptr->mptr[i]->password[j], writePtr);
		fputc(59, writePtr);
		//write the hobbies to the file
		hobbiesWriter(writePtr, gptr->mptr[i]->hobbies);
		fputc(59, writePtr);
		//write the description to the file
		for (j = 0; gptr->mptr[i]->about[j] != 0; j++)
			fputc(gptr->mptr[i]->about[j], writePtr);
		//write new line to the file
		fputc(10, writePtr);
	}
	//write all Females database to file	
	while (curr != NULL)
	{
		//write the ID to the file
		for (j = 0; curr->data->ID[j] != 0; j++)
			fputc(curr->data->ID[j], writePtr);
		fputc(59, writePtr);
		//write the first name to the file
		for (j = 0; curr->data->firstName[j] != 0; j++)
			fputc(curr->data->firstName[j], writePtr);
		fputc(59, writePtr);
		//write the last name to the file
		for (j = 0; curr->data->lastName[j] != 0; j++)
			fputc(curr->data->lastName[j], writePtr);
		fputc(59, writePtr);
		//write the age to the file, convert it to a string
		sprintf(buffer, "%d", curr->data->age);
		for (j = 0; buffer[j] != 0; j++)
			fputc(buffer[j], writePtr);
		fputc(59, writePtr);
		//write the gender to the file
		fputc(curr->data->gender, writePtr);
		fputc(59, writePtr);
		//write the user name to the file
		for (j = 0; curr->data->userName[j] != 0; j++)
			fputc(curr->data->userName[j], writePtr);
		fputc(59, writePtr);
		//write the password to the file
		for (j = 0;curr->data->password[j] != 0; j++)
			fputc(curr->data->password[j], writePtr);
		fputc(59, writePtr);
		//write the hobbies to the file
		hobbiesWriter(writePtr, curr->data->hobbies);
		fputc(59, writePtr);
		//write the description to the file
		for (j = 0; curr->data->about[j] != 0; j++)
			fputc(curr->data->about[j], writePtr);
		//write new line to the file
		fputc(10, writePtr);
		//move to the next women
		curr = curr->next;
	}
	//close the file
	fclose(writePtr);
}
/***********************************************************************************************************
* function name: hobbiesWriter
* The Input: an address to a file and a char that represent the hobbies
* The output: -
* The Function operation: the function write to "output.txt" witch hobbies the user like
	it does it by using the file pointer and by checking the bits of the char "hobbies"
***********************************************************************************************************/
void hobbiesWriter(FILE* writePtr, unsigned char hobbies)
{
	int i,j;
	unsigned char temp;
	//do it 8 times, to scan all the 8 hobbies
	for (i = 0; i < 8; i++)
	{
		temp = 1;
		for (j = 0; j < i; j++)	
			temp = temp * 2;
		//keep only 1 bit up each time and check it with switch case
		temp = temp & hobbies;
		switch (temp)
		{
		//write the appropriate hobby to the file
		case 1:
			fputc(49, writePtr);
			fputc(44, writePtr);
			break;
		case 2:
			fputc(50, writePtr);
			fputc(44, writePtr);
			break;
		case 4:
			fputc(51, writePtr);
			fputc(44, writePtr);
			break;
		case 8:
			fputc(52, writePtr);
			fputc(44, writePtr);
			break;
		case 16:
			fputc(53, writePtr);
			fputc(44, writePtr);
			break;
		case 32:
			fputc(54, writePtr);
			fputc(44, writePtr);
			break;
		case 64:
			fputc(55, writePtr);
			fputc(44, writePtr);
			break;
		case 128:
			fputc(56, writePtr);
			fputc(44, writePtr);
			break;
		default:
			break;
		}//end of switch
	}//end of for
	//move one step back (to delete the last "," was wrote)
	fseek(writePtr, -1, SEEK_CUR);
}
/***********************************************************************************************************
* function name: allocateFailed
* The Input: an address to the Database
* The output: -
* The Function operation: the function print appropriate message for allocate fail and call functions to
	export the data and free all the allocated memory and than exit
***********************************************************************************************************/
void allocateFailed(Gender* gptr)
{
	//in case of allocate fail, print appropriate message, export all the data, free all the memory and exit
	printf("Not enough memory - allocate failed.\n");
	exportData(gptr);
	freeAll(gptr);
	exit(1);
}
/***********************************************************************************************************
* function name: enterMenu
* The Input: an address to the Database
* The output: -
* The Function operation: the function ask for the user to chose an option and move to the selected path
***********************************************************************************************************/
void enterMenu(Gender* gptr)
{
	int key;
	while (1)
	{
		printf("Welcome! please choose an option\n1 - Log in\n2 - New member\n3 - Exit\n");
		scanf("%d", &key);
		//move to the chosen path
		switch (key)
		{
		case 1:
			logIn(gptr);
			break;
		case 2:
			newMember(gptr);
			break;
		case 3:
			return;
			break;
		default:
			printf("Bad choice, please try again\n");
			break;
		}
	}
	return;
}
/***********************************************************************************************************
* function name: logIn
* The Input: an address to the Database
* The output: -
* The Function operation: the function ask for a user name from the user and check if its exist in the system
	if it is, the program use a password and compare it with the password of the user name before.
	if it not match it prints a message and return to enterMenu, if its a match the program calls mainMenu
***********************************************************************************************************/
void logIn(Gender* gptr)
{
	int failCounter = 0;
	Member*	userAddress=NULL;
	char password[MAX_PASS+1], userName[MAX_UN+1], dummy;
	scanf("%c", &dummy);
	while (1)
	{
		printf("Please enter your username:\n");
		//get a user name
		fgets(userName, MAX_UN +1 ,stdin);
		userName[strlen(userName)-1] = 0;
		//check if it exists in the system
		userAddress = searchUser(userName,gptr);
		if (userAddress !=NULL)
		{
			printf("Please enter your password:\n");
			fgets(password, MAX_PASS +1, stdin);
			password[strlen(password)-1] = 0;
			//compare the given password with the real user password
			if (strcmp(userAddress->password,password)==0)
			{
				//success! enter mainMenu
				printf("Hello %s!\n", userAddress->firstName);
				mainMenu(userAddress,gptr);
				return;
			}
			else
			{
				//fail, return
				printf("Wrong password\n");
				return;
			}
		}
		//to give the user only 1 time to be wrong about the user name, increase count and check its value
		failCounter++;
		if (failCounter != 2)
			printf("User do not exist in the system, please try again\n");
		else
			//wrong for the second time, return
			return;
	}
	return;
}
/***********************************************************************************************************
* function name: newMember
* The Input: an address to the Database
* The output: -
* The Function operation: the function gets a full new profile from the user and in the end connect it to the
	database
***********************************************************************************************************/
void newMember(Gender* gptr)
{
	int i;
	Member* mptr = NULL;
	int key;
	char buffer[MAX_BUFFER], dummy;
	unsigned char hobbies = 0;
	printf("Please enter your ID:\n");
	scanf("%c", &dummy);
	fgets(buffer,MAX_BUFFER,stdin);
	buffer[strlen(buffer)-1] = 0;
	//check the size of ID
	if (strlen(buffer) != ID_LEN)
		return;
	//check if ID exist
	if (checkID(buffer, gptr)==FALSE)
	{
		printf("Error: User already exists\n");
		return;
	}
	//Allocate new profile
	if ((mptr = (Member*)malloc(sizeof(Member))) == NULL)
		allocateFailed(gptr);
	//reset the new struct
	resetStruct(mptr);
	//copy the given ID to the profile
	strcpy(mptr->ID, buffer);
	printf("Please enter your first name:\n");
	fgets(buffer, MAX_BUFFER, stdin);
	buffer[strlen(buffer) - 1] = 0;
	//check valid of the name
	if (checkValid(buffer))
	{
		freeMember(mptr);
		return;
	}
	//allocate memory for the name
	if ((mptr->firstName = (char*)malloc(strlen(buffer)+1)) == NULL)
		allocateFailed(gptr);
	//copy the given name to the profile
	strcpy(mptr->firstName, buffer);
	printf("Please enter your last name:\n");
	fgets(buffer, MAX_BUFFER, stdin);
	buffer[strlen(buffer) - 1] = 0;
	if (checkValid(buffer))
	{
		freeMember(mptr);
		return;
	}
	if ((mptr->lastName = (char*)malloc(strlen(buffer) + 1)) == NULL)
		allocateFailed(gptr);
	//copy the given last name to the profile
	strcpy(mptr->lastName, buffer);
	printf("Please enter your age (18 to 100):\n");
	scanf("%d", &(mptr->age));
	//check age range
	if (mptr->age<MIN_AGE || mptr->age>MAX_AGE)
	{
		freeMember(mptr);
		return;
	}
	printf("Please enter your gender (F-female, M-male):\n");
	scanf("%c %c", &dummy,&mptr->gender);
	//check the gender valid
	if (mptr->gender != 'M' && mptr->gender != 'F')
	{
		freeMember(mptr);
		return;
	}
	printf("Choose a username (3-10 characters):\n");
	scanf("%c", &dummy);
	fgets(buffer, MAX_BUFFER, stdin);
	buffer[strlen(buffer) - 1] = 0;
	//check the user name valid
	if (strlen(buffer)<MIN_UN || strlen(buffer) > MAX_UN 
		|| (buffer[0] < 'a' || buffer[0] < 'z') && (buffer[0] < 'A' && buffer[0] < 'Z'))
	{
		freeMember(mptr);
		return;
	}
	//allocate memory for the user name
	if ((mptr->userName = (char*)malloc(strlen(buffer) + 1)) == NULL)
		allocateFailed(gptr);
	strcpy(mptr->userName, buffer);
	printf("please choose 4 hobbies: Baseball=1, Basketball=2, Bicycle=3, Books=4, ");
	printf("Drawing=5, Gym=6, Movies=7, Poetry=8\n");
	//gets the 4 hobbies of the new member into a hobbies char
	for (i = 0; i < 4; i++)
	{
		scanf("%d", &key);
		switch (key)
		{
		case BASEBALL:
			hobbies |= 1;
			break;
		case BASKETBALL:
			hobbies |= 2;
			break;
		case BICYCLE:
			hobbies |= 4;
			break;
		case BOOKS:
			hobbies |= 8;
			break;
		case DRAWING:
			hobbies |= 16;
			break;
		case GYM:
			hobbies |= 32;
			break;
		case MOVIES:
			hobbies |= 64;
			break;
		case POETRY:
			hobbies |= 128;
			break;
		default:
			break;
		}//end of switch
	}//end of for
	//put it in the member hobbies
	mptr->hobbies = hobbies;
	printf("Choose a password (attention-minimum 6 characters):\n");
	scanf("%c",&dummy);
	fgets(buffer, MAX_BUFFER, stdin);
	buffer[strlen(buffer) - 1] = 0;
	//check the password valid
	if (strlen(buffer) < MIN_PASS || strlen(buffer) > MAX_PASS)
	{
		freeMember(mptr);
		return;
	}
	if ((mptr->password = (char*)malloc(strlen(buffer) + 1)) == NULL)
		allocateFailed(gptr);
	strcpy(mptr->password, buffer);
	printf("Some words about yourself:\n");
	fgets(buffer, MAX_BUFFER, stdin);
	buffer[strlen(buffer) - 1] = 0;
	//check the description valid
	if (strlen(buffer) >= MAX_BUFFER)
	{
		freeMember(mptr);
		return;
	}
	if ((mptr->about = (char*)malloc(strlen(buffer) + 1)) == NULL)
		allocateFailed(gptr);
	strcpy(mptr->about, buffer);
	//connect the new profile to the database
	connectProfile(mptr,gptr);
	printf("Hi %s, lets find love!\n",mptr->firstName);
	//go to the main menu
	mainMenu(mptr,gptr);
	return;
}
/***********************************************************************************************************
* function name: freeMember
* The Input: an address to a single profile
* The output: -
* The Function operation: the function free all the allocated memory of a single member
***********************************************************************************************************/
void freeMember(Member* mptr)
{
	//free all the memory allocated to a member
	if (mptr->firstName != NULL)
		free(mptr->firstName);
	if (mptr->lastName != NULL)
		free(mptr->lastName);
	if (mptr->userName != NULL)
		free(mptr->userName);
	if (mptr->password != NULL)
		free(mptr->password);
	if (mptr->about != NULL)
		free(mptr->about);
	free(mptr);
	return;
}
/***********************************************************************************************************
* function name: connectProfile
* The Input: an address to the Database and an address to a single profile
* The output: -
* The Function operation: the function connect a new member profile to the database, if its a male it connect 
	it to the dynamic array and if its a female it connect it to the connected list
***********************************************************************************************************/
void connectProfile(Member* mptr, Gender* gptr)
{
	FemaleItem *fiptr=NULL;
	//if its a Male member
	if (mptr->gender == 'M')
	{
		//increase the male counter
		gptr->maleCounter++;
		//change the size of the dynamic array and connect the new member to the last new cell
		if ((gptr->mptr = (Member**)realloc(gptr->mptr,gptr->maleCounter*(sizeof(Member*)))) == NULL)
			allocateFailed(gptr);
		gptr->mptr[gptr->maleCounter-1] = mptr;
	}
	else
	{
		//allocate a new FemaleItem struct and connect the member data to it
		if ((fiptr = (FemaleItem*)malloc(sizeof(FemaleItem))) == NULL)
			allocateFailed(gptr);
		fiptr->data = mptr;
		//reset the next pointer to avoid unwanted access
		fiptr->next = NULL;
		//send the new FemaleItem to findPlace to connect it in the right place (alphabetic order)
		findPlace(gptr,fiptr);
	}
	return;
}
/***********************************************************************************************************
* function name: resetStruct
* The Input: an address to a single member
* The output: -
* The Function operation: the function sets all the member pointers to NULL
***********************************************************************************************************/
void resetStruct(Member* mptr)
{
	//reset all the pointers of member to avoid unwanted access 
	mptr->about		= NULL;
	mptr->firstName = NULL;
	mptr->lastName  = NULL;
	mptr->password  = NULL;
	mptr->userName	= NULL;
}
/***********************************************************************************************************
* function name: findPlace
* The Input: an address to the Database and to a new female member
* The output: -
* The Function operation:the function connect the new profile to the connected list in an alphabet order
	it doing it by checking the last name of the new member and put it in the right place in the list
***********************************************************************************************************/
void findPlace(Gender* gptr, FemaleItem* fiptr)
{
	FemaleItem *prev = gptr->head;
	FemaleItem *current = gptr->head->next;
	char tempStr1[MAX_N + 1] = { 0 }, tempStr2[MAX_N + 1] = { 0 };
	//if its the first member
	if (gptr->head->next == NULL)
	{
		gptr->head->next = fiptr;
		return;
	}
	//worst case the new female ends the last in the list 
	while (current != NULL) 
	{
		/*
		
		compare between the two strings, if the first is smaller then the second, position the new
		member in the preview place,else keep to the next member. use conToSmall to compare the 
		small letters value to avoid mistakes of order (like B<a)
		
		*/
		strcpy(tempStr1,fiptr->data->lastName);
		strcpy(tempStr2,current->data->lastName);
		if (strcmp(conToSmall(tempStr1), conToSmall(tempStr2)) < 0)
		{
			fiptr->next = prev->next;
			prev->next = fiptr;
			return;
		}
		prev = current;
		current = current->next;
	}
	//position at the last place of the list
	prev->next = fiptr;
	return;
}
/***********************************************************************************************************
* function name: conToSmall
* The Input: a string with small and capital letters mixed
* The output: a string with only small letters
* The Function operation: check if there is any big letters in the array and any time it found one, it replace
	it with the same letter in a small form
***********************************************************************************************************/
char* conToSmall(char str[])
{
	int i;
	//scan the string, each time you find a capital letter, convert it to a small letter
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] > 'A' && str[i] < 'Z')
		{
			str[i] = str[i] + 32;
		}
	}
	return str;
}
/***********************************************************************************************************
* function name: checkValid
* The Input: a string 
* The output: a string with only small letters
* The Function operation: check if the size of the array is not bigger than the max size and contains only letters
***********************************************************************************************************/
bool checkValid(char str[])
{
	int i;
	//if the string length is more than 15 chars or contain a not letter char, return FALSE
	if (strlen(str) > MAX_N)
		return FALSE;
	for (i = 0; i < strlen(str); i++)
	{
		if ((str[i]<'a' || str[i] < 'z') && (str[i] < 'A' && str[i] < 'Z'))
			return FALSE;
	}
	return TRUE;
}
/***********************************************************************************************************
* function name: mainMenu
* The Input: an address to a specific user and an address to the database
* The output: - 
* The Function operation: the function ask from the user to a next move : find a match, delete him or log out
	and operate this way
***********************************************************************************************************/
void mainMenu(Member* mptr,Gender* gptr)
{
	int key;
	while (1)
	{
		//ask for an option from user and go to the right path
		printf("Please choose an option:\n");
		printf("1. Find a match\n2. I found love, DELETE me\n3. Log out\n");
		scanf("%d", &key);
		switch (key)
		{
		case 1:
			findLove(mptr,gptr);
			break;
		case 2:
			deleteUser(mptr,gptr);
			return;
			break;
		case 3:
			return;
			break;
		default:
			printf("Bad choice, please try again\n");
			return;
			break;
		}
	}
}
/***********************************************************************************************************
* function name: searchUser
* The Input: a string and an address to the database
* The output: an address to a the member profile or NULL if cant find it
* The Function operation: the function scans all the database, male dynamic list and female connected list
	and if it find a compared user name it return the address of this profile
***********************************************************************************************************/
Member* searchUser(char userName[],Gender* gptr)
{
	FemaleItem* curr=gptr->head->next;
	int i;
	//search on all the male dynamic array, if there is a matching user name, return his member address
	for (i = 0; i < gptr->maleCounter; i++)
		if (strcmp(gptr->mptr[i]->userName, userName) == 0)
			return gptr->mptr[i];
	//search on all the female connected list, if there is a matching user name, return her member address
	while (curr != NULL)
	{
		if (strcmp(curr->data->userName, userName) == 0)
			return curr->data;
		curr = curr->next;
	}
	//cant find it
	return NULL;
}
/***********************************************************************************************************
* function name: findLove
* The Input: an address to a member profile and an address to the database
* The output: -
* The Function operation: the function scans the database - Males or Females, in order to find a match
	that answer all the limits - other gender, right age and at least 2 similar hobbies, if it find a match
	it call the printing function to print it.
***********************************************************************************************************/
void findLove(Member* mptr,Gender* gptr)
{
	int minAge, maxAge,i;
	FemaleItem* curr=gptr->head->next;
	//ask for a age range
	printf("Please choose ages range:\n");
	scanf("%d %d",&minAge,&maxAge);
	switch (mptr->gender)
	{
	//if its male, scan female database
	case 'M':
		while (curr != NULL)
		{
			//check age range
			if (curr->data->age >= minAge && curr->data->age <= maxAge)
			{
				//check hobbies match
				if (checkMatch(curr->data->hobbies & mptr->hobbies) == TRUE)
					//print match
					printMatch(curr->data);
			}
			//try the next woman
			curr = curr->next;
		}
		break;
	//if its a male,scan female database
	case'F':
		for (i = 0; i < gptr->maleCounter; i++)
		{
			//check the age range and the hobbies, if there is a match print it
			if (gptr->mptr[i]->age >=minAge && gptr->mptr[i]->age <= maxAge)
				if (checkMatch(gptr->mptr[i]->hobbies & mptr->hobbies) == TRUE)
					printMatch(gptr->mptr[i]);
		}
		break;
	default: break;
	}
	return;
}
/***********************************************************************************************************
* function name: checkMatch 
* The Input: a char that represent the common hobbies of the 2 members
* The output: a bool type that represent TRUE - for match and FALSE - for no match
* The Function operation: the function check how much "1" contain the char hobbies in his binary form
	and count it, if the counter ends with 2 or more points, its a match
***********************************************************************************************************/
bool checkMatch(unsigned char hobbiesMatch)
{
	int i, counter = 0;
	for (i = 0; i < 8; i++)
	{
		//count how much "1" there is in the binary form of hobbies
		if (hobbiesMatch % 2 == 1)
			counter++;
		hobbiesMatch = hobbiesMatch >> 1;
	}
	//if there is more than 2,its a match return TRUE, if not return FALSE
	if (counter < 2)
		return FALSE;
	else
		return TRUE;
}
/***********************************************************************************************************
* function name: printMatch
* The Input: an address of a the matching member
* The output: -
* The Function operation: the function print all the information about the member
***********************************************************************************************************/
void printMatch(Member* mptr)
{
	char hobbieStr[8][11]={"Baseball","Basketball","Bicycle","Books","Drawing","Gym","Movies","Poetry"};
	unsigned char hobbies = mptr->hobbies;
	int i,counter=0;
	//print all the data about the matching user
	printf("Name: %s %s Age: %d ",mptr->firstName,mptr->lastName,mptr->age);
	printf("Hobbies: ");
	//for the hobbies, check witch bits are "1" on hobbies with bitwise and print the appropriate hobby
	for (i = 0; i < 8; i++)
	{
		if (hobbies % 2 == 1)
		{
			counter++;
			//I use an array to make i represent the name of the hobby
			printf("%s", hobbieStr[i]);
			if (counter == 4)
				break;
			printf(", ");
		}

		hobbies = hobbies >> 1;
	}
	printf(" Description: %s\n\n", mptr->about);

}
/***********************************************************************************************************
* function name: deleteUser
* The Input: an address of a the member that want to be deleted and an address to the database
* The output: -
* The Function operation: the function disconnect the member from the database that he exist in, and reorder 
	the database with one less member in it
***********************************************************************************************************/
void deleteUser(Member* mptr,Gender* gptr)
{
	int i;
	FemaleItem *curr = gptr->head, *prev = NULL;
	switch (mptr->gender)
	{
	case 'M':
		//find the member position
		for (i = 0; i < (gptr->maleCounter); i++)
			if (mptr == gptr->mptr[i])
				break;
		//free the allocate memory of the member
		freeMember(mptr);
		//shift the array to close the gap
		for (;i<(gptr->maleCounter-1); i++)
		{
			gptr->mptr[i] = gptr->mptr[i + 1];
		}
		//free the last cell of the array
		gptr->maleCounter--;
		//if there is no more men on the list dont realloc because it will return NULL
		if (gptr->maleCounter!=0)
		if ((gptr->mptr = (Member**)realloc(gptr->mptr, gptr->maleCounter*(sizeof(Member*)))) == NULL)
			allocateFailed(gptr);
		break;
	case 'F':
		//scan all the list until the last member
		while (curr != NULL)
		{
			//search for the member want to be deleted
			if (curr->data == mptr)
			{
				//if you find it let preview member point to the next member after him
				prev->next = curr->next;
				//reset his pointer
				curr->next = NULL;
				//free all the member data
				freeMember(curr->data);
				//free the member allocated memory
				free(curr);
				break;
			}
			//keep looking
			prev = curr;
			curr = curr->next;
		}
		break;
	default:
		break;
	}
	return;
}
/***********************************************************************************************************
* function name: checkID
* The Input: a string of ID and an address to the database
* The output: a bool type - TRUE represent that the ID is free to use, FALSE represent that the ID exist in the system
* The Function operation: the function scans the male dynamic array and the female connected list
	and check if the ID is already exists in it, and return an appropriate value.
***********************************************************************************************************/
bool checkID(char ID[], Gender* gptr)
{
	int i;
	FemaleItem* curr = gptr->head->next;
	//scan the women list to check if the ID already exists
	while (curr != NULL)
	{
		if (strcmp(ID, curr->data->ID) == 0)
			return FALSE;
		curr = curr->next;
	}
	//scan the male array to check if the ID already exists
	for (i = 0; i < gptr->maleCounter; i++)
	{
		if (strcmp(gptr->mptr[i]->ID, ID) == 0)
			return FALSE;
	}
	//not exists
	return TRUE;
}
/***********************************************************************************************************
* function name: freeAll
* The Input: an address to the database
* The output: -
* The Function operation: the function scans the male dynamic array and the female connected list
	free all the allocated memory in it, at the end it also free the main database struct (gptr)
***********************************************************************************************************/
void freeAll(Gender* gptr)
{
	FemaleItem* currMember=gptr->head,*nextMember;
	int i;
	if (gptr != NULL)
	{
		//free all female list
		while (currMember != NULL)
		{
			nextMember = currMember->next;
			if (currMember->data != NULL)
			{
				freeMember(currMember->data);
			}
				free(currMember);
			currMember = nextMember;
		}
		//free all male list
		if (gptr->mptr != NULL)
		{
			for (i = 0; i < gptr->maleCounter; i++)
			{
				if (gptr->mptr[i] != NULL)
				{
					freeMember(gptr->mptr[i]);
				}
			}
			free(gptr->mptr);
		}
		//free main database struct
		free(gptr);
	}
	return;
}
