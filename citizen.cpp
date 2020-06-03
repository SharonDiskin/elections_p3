#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "citizen.h"

//Default c'tor
Citizen::Citizen() : Citizen("Israel", Date(1, 1, 2000), 100000000, 1, 0) {};

//C'tor
Citizen::Citizen(const char* name, const Date& birthday, int id, int ballotNum, bool isIsolated) : birthday(std::move(birthday))
{
	setName(name);
	setId(id);
	setBallotNum(ballotNum);
	setIsIsolated(isIsolated);
}

Citizen::Citizen(const Citizen& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	birthday = other.birthday;
	id = other.id;
	ballotNum = other.ballotNum;
	isIsolated = other.isIsolated;
}

Citizen::Citizen(Citizen&& other)//Move c'tor
{
	name = other.name;
	other.name = nullptr;
	birthday = other.birthday;
	id = other.id;
	ballotNum = other.ballotNum;
	isIsolated = other.isIsolated;
}

const char* Citizen::getName() const
{
	return name;
}

const Date& Citizen::getBirth() const
{
	return birthday;
}

const int Citizen::getId() const
{
	return id;
}

int Citizen::getBallotNum() const
{
	return ballotNum;
}

bool Citizen::getIsIsolated() const
{
	return isIsolated;
}

bool nameChar(char c)
//This function check is a given charcter is a letter (big or small) or a space.
//if yes, the function return true, else return false.
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c < 'Z') || (c == ' '));
}

bool validNameCheck(const char* str)
//This function returns true if a given string is made of letters and spaces,
//else the function return false.
{
	int i, len = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (!nameChar(str[i]))
		{
			return false;
		}
	}

	return true;
}

bool Citizen::setName(const char* citizenName)
{
	if (!(validNameCheck(citizenName)))
	{
		cout << "Invalid citizen name\n";
		return false;
	}
	else
	{
		name = new char[strlen(citizenName) + 1];
		strcpy(name, citizenName);
		return true;
	}
}

bool Citizen::setBirth(Date citizenBirth)
{
	birthday = citizenBirth;
	return true;
}

/*This function is a helper funtion for "set id".*/
bool checkID(int idNum)
{
	return (idNum > 100000000 && idNum <= 999999999);
}

bool Citizen::setId(int citizenId)
{
	if (checkID(citizenId))
	{
		id = citizenId;
		return true;
	}
	else
	{
		cout << "The id you enterd is not valid. Id have to be according to the real Israel Id method. Id unchanged.\n";
		return false;
	}
}

bool Citizen::setBallotNum(int bn)
{
	if (bn <= 0)
	{
		cout << "Ballot num must be a positive number. Number unchanged.\n";
		return false;
	}
	else
	{
		ballotNum = bn;
		return true;
	}

}

bool Citizen::setIsIsolated(bool ans)
{
	if (ans != 1 || ans != 0)
	{
		this->isIsolated = ans;
		return true;
	}
	else
		return false;
}

void Citizen::show() const
{
	cout << "Name: " << name << ".\n" << "Date of birth: " << birthday <<
		"." << endl << "ID: " << id << ".\n";
	if (isIsolated)
		cout << "In isolation.\n";
	else
		cout << "Not in isolation.\n";
}

Citizen:: ~Citizen()
{
	if (name != nullptr)
	{
		delete[] name;
	}
}