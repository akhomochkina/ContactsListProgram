#ifndef _FUNCTIONALITY_H
#define _FUNCTIONALITY_H

#include "DataBase.h"

struct Functionality
{
	const char* error = "Input Error! Try again!";
	//loads the list of existing contacts
	bool loadContacts(DataBase& data);
	//gets an option from the user: add contacts, view contacts, exit app
	char getOption();
	//executes the option selected by user
	void executeOption(char opt, DataBase& data);
	//adds the new contact information
	void addContacts(DataBase& data);
	//displays all the stored contacts in the file
	void displayContacts(const DataBase& data);
	//changes the size of stored contacts
	void resizeContacts(DataBase& data, int num);
	//saves contacts to the binary file
	void saveContacts(const DataBase& data);
	//function to create a binary file Contacts.bin
	void createContactsFile();

	enum CharacterCaseType
	{
		CC_UPPER_CASE = 0,
		CC_LOWER_CASE,
		CC_EITHER
	};

	char GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase);
	int GetString(const char* promt, const char* error, char string[], int maxLen);
};


#endif