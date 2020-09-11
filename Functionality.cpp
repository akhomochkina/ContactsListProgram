#include <iostream>
#include <cctype>
#include <fstream>
#include "DataBase.h"
#include "Functionality.h"

using namespace std;

bool Functionality::loadContacts(DataBase& data)
{
	ifstream file;
	file.open("Contacts.bin", fstream::binary);

	if (file.is_open())
	{
		file.seekg(0, file.end);
		int len = file.tellg();
		file.seekg(0, file.beg);

		int num = len / sizeof(Contacts);
		int capacity = num * 2 + 10;

		data.optrContacts = new Contacts[capacity];
		data.contactsNum = num;
		data.capacity = capacity;

		file.read((char*)data.optrContacts, len);
		file.close();

		return true;
	}

	return false;
}

char Functionality::getOption()
{
	//options to choose from: d - display, a - add, q - quit
	const char options[] = { 'd', 'a', 'r', 'q' };

	return GetCharacter("Please choose an option to proceed:\n\n(D)isplay\n(A)dd\n(Q)uit\n\n", error, options, 4, CC_LOWER_CASE);
}

void Functionality::executeOption(char opt, DataBase& data)
{
	switch (opt)
	{
	case 'a':
		addContacts(data);
		break;
	case 'd':
		displayContacts(data);
		break;
	}
}

void Functionality::addContacts(DataBase& data)
{
	if (data.contactsNum == data.capacity)
	{
		resizeContacts(data, data.capacity * 2 + 10);
	}

	GetString("Please enter the First Name: ", error, data.optrContacts[data.contactsNum].firstName, 256 - 1);
	GetString("Please enter the Last Name: ", error, data.optrContacts[data.contactsNum].lastName, 256 - 1);
	GetString("Please enter a phone number: ", error, data.optrContacts[data.contactsNum].phoneNum, 11 - 1);

	data.contactsNum++;

	saveContacts(data);
	cout << endl << "Contact Saved!" << endl << endl;
}

void Functionality::displayContacts(const DataBase& data)
{
	for (int i = 0; i < data.contactsNum; i++)
	{
		cout << "Name: " << data.optrContacts[i].firstName << " " << data.optrContacts[i].lastName << endl;
		cout << "Phone Number: " << data.optrContacts[i].phoneNum << endl << endl;
	}
}

void Functionality::resizeContacts(DataBase& data, int num)
{
	Contacts* newConstactsPtr = new Contacts[num];
	for (int i = 0; i < data.contactsNum; i++)
	{
		strcpy(newConstactsPtr[i].firstName, data.optrContacts[i].firstName);
		strcpy(newConstactsPtr[i].lastName, data.optrContacts[i].lastName);
		strcpy(newConstactsPtr[i].phoneNum, data.optrContacts[i].phoneNum);
	}

	if (data.optrContacts != nullptr)
	{
		delete[] data.optrContacts;
		data.optrContacts = nullptr;
	}

	data.optrContacts = newConstactsPtr;
	data.capacity = num;
}

void Functionality::saveContacts(const DataBase& data)
{
	ofstream file;
	file.open("Contacts.bin", fstream::binary);

	if (file.is_open())
	{
		file.write((char*)data.optrContacts, data.contactsNum * sizeof(Contacts));
		file.close();
	}
}

void Functionality::createContactsFile()
{
	ifstream file;
	file.open("Contacts.bin", fstream::binary);
	if (!file.is_open())
	{
		ofstream ofile;
		ofile.open("Contacts.bin", fstream::binary);
		ofile << flush;
		ofile.close();
	}
	else file.close();
}

char Functionality::GetCharacter(const char* prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase)
{

	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		cout << prompt;
		cin >> input;
		cout << endl;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if (isalpha(input))
			{
				if (charCase == CC_UPPER_CASE)
				{
					input = toupper(input);
				}
				else if (charCase == CC_LOWER_CASE)
				{
					input = tolower(input);
				}

				for (int i = 0; i < validInputLength; i++)
				{
					if (input == validInput[i])
					{
						return input;
					}
				}
			}

			cout << error << endl;
			failure = true;

		}

	} while (failure);

	return input;
}

int Functionality::GetString(const char* promt, const char* error, char string[], int maxLen)
{
	bool failure;
	int len;

	do
	{
		failure = false;
		cout << promt;
		cin >> ws;
		cin.get(string, maxLen, '\n');

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << error << endl;
			failure = true;
		}

		else
		{
			cin.ignore(256, '\n');
			len = strlen(string);

			if (len == 0)
			{
				cout << "Have to enter at least one character!";
				failure = true;
			}
		}

	} while (failure);

	return len;
}