#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "party.h"

const char* streamStr[] = { "Left", "Right", "Center" };

Party::Party() : Party("Miflaga", (Party::eStream)1, Date(1, 1, 2000)) { }; //Defult initizializer

																			//C'tor
Party::Party(const char* name, Party::eStream stream, const Date& date) : creationDate(std::move(date))
{
	setName(name);
	setStream(stream);
	contestants = new Contestant*[phySize];
}

Party::Party(const Party& other) //Copy c'tor
{
	setName(other.getName());
	theStream = other.theStream;
	creationDate = other.creationDate;
	logSize = other.logSize;
	phySize = other.phySize;
	contestants = new Contestant*[phySize];
	for (int i = 0; i < logSize; i++)
	{
		contestants[i] = other.contestants[i];
	}
}

Party::Party(Party&& other)//Move c'tor
{
	name = other.name;
	other.name = nullptr;
	theStream = other.theStream;
	creationDate = other.creationDate;
	logSize = other.logSize;
	phySize = other.phySize;
	contestants = other.contestants;
	other.contestants = nullptr;
}

char* Party::getName() const
{
	return name;
}

Party::eStream Party::getStream() const
{
	return theStream;
}

const Date& Party::getCreationDate() const
{
	return creationDate;
}

Contestant** Party::getContestants() const
{
	return contestants;
}

bool nameCharForParty(char c)
//This function check is a given charcter is a letter (big or small) or a space.
//if yes, the function return true, else return false.
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c < 'Z') || (c == ' '));
}

bool validNameCheckForParty(const char* str)
//This function returns true if a given string is made of letters and spaces,
//else the function return false.
{
	int i, len = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (!nameCharForParty(str[i]))
		{
			cout << "Invalid name.\n";
			return false;
		}
	}

	return true;
}

bool Party::setName(const char* str)
//This function insert the name of the party.
{
	if (!(validNameCheckForParty(str)))//is the name ok?
		return false;//if not return false.
	else//if the name good, insert him, and return true.
	{
		name = new char[strlen(str) + 1];
		strcpy(name, str);
		return true;
	}
}

bool Party::setStream(Party::eStream s)
{
	if ((int)s <0 || (int)s >2)
	{
		cout << "You entered invalid stream. Stream unchanged\n";
		return false;
	}
	else
	{
		theStream = s;
		return true;
	}
}

bool Party::setCreationDate(const Date& date)
{
	creationDate = date;
	return true;
}

const Party& Party::operator=(const Party& other)
{
	if (this != &other)
	{
		delete[] name;
		name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
		theStream = other.theStream;
		creationDate = other.creationDate;
		logSize = other.logSize;
		phySize = other.phySize;
		delete[] contestants;
		contestants = other.contestants;
	}
	return *this;
}

bool Party:: operator>(const Party& other) const
{
	return this->logSize > other.logSize;
}

Contestant** realloc(Contestant** arr, int oldSize, int newSize)
//This function allocate bigger memory to the contestant array.
{
	int i;
	Contestant** newArr = new Contestant*[newSize];//allocate bigger memory.
	for (i = 0; i < oldSize; i++)
	{
		newArr[i] = arr[i];//copy data.
	}

	delete[]arr;//free old memory.
	return newArr;
}

void Party::addContestant(const Contestant& citizen)
//This function gets a pointer to a citizen and add the citizen to the contestant list.
{
	if (logSize == phySize)//the array is full?
	{
		phySize *= 2;
		contestants = realloc(contestants, logSize, phySize);//make him bigger.
	}
	contestants[logSize] = new Contestant(citizen);
	logSize++;
}

void Party::show() const
//This function prints the party information.
{
	int i;
	cout << "Party name: " << name << "." << endl;
	cout << "Party stream: " << streamStr[(int)theStream] << "." << endl;
	cout << "Party creation date: " << creationDate << "." << endl;

	if (logSize == 0)
	{
		cout << "The party doesnt have Contestants.\n";
	}
	else
	{

		cout << "Contestants: \n-------------\n";

		for (i = 0; i < logSize; i++)//print each contestant.
		{
			cout << i + 1 << ")";
			contestants[i]->show();
			cout << endl;
		}
	}
}

Party::~Party()
//This function deallocate the used memory.
{
	if (name != nullptr)
	{
		delete[] name;
	}
	if (contestants != nullptr)
	{
		delete[] contestants;
	}
}