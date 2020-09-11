#include <iostream>
#include <fstream>
#include "DataBase.h"
#include "Functionality.h"

//Mini program that keeps a list of contacts (First Name, Last Name, Phone Number)
//User can read or write the contacts information into the program

using namespace std;

int main()
{
	DataBase db;
	Functionality fanctionality;

	fanctionality.createContactsFile();	

	if (!fanctionality.loadContacts(db))
	{
		cout << "Error reding file" << endl;
		return 0;
	}

	char option;

	do
	{
		option = fanctionality.getOption();
		fanctionality.executeOption(option, db);

	} while (option != 'q');

	fanctionality.saveContacts(db);

	if (db.optrContacts != nullptr);
	{
		delete[] db.optrContacts;
		db.optrContacts = nullptr;
	}

	return 0;
}