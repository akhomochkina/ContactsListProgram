#ifndef _DATABASE_H
#define _DATABASE_H

struct Contacts
{
	char firstName[256];
	char lastName[256];
	char phoneNum[11];
};

struct DataBase
{
	//pointer to contacts 
	Contacts* optrContacts = nullptr;
	//number of contacts in data base
	int contactsNum = 0;
	//capacity of contacts array
	int capacity = 0;
};

#endif